/**
 * Represents a chess board
 *
 * Author: Chun Li, Weichen Zhou
 * Created: Nov 17, 2013.
 */

#include <iostream>
#include <cstdlib>
#include <sstream>

#include "move.h"
#include "board.h"
#include "piece.h"
#include "helper.h"
#include "window.h"

using namespace std;

Board::Board(Xwindow *xwin) : xwin(xwin), initial(NULL), current(NULL), rows(8), columns(8) {
    init(8, 8); //standard board is 8x8

    //add all the pieces
    //the standard chess arrangement isn't going to change anytime soon,
    //so this is just hardcoded in.

    //pawns
    for (int i = 0; i < 8; i++) {
        //black
        initial[1][i] = new Piece(pawn, black, this);
        //white
        initial[6][i] = new Piece(pawn, white, this);
    }

    //rooks
    //black
    initial[0][0] = new Piece(rook, black, this);
    initial[0][7] = new Piece(rook, black, this);
    //white
    initial[7][0] = new Piece(rook, white, this);
    initial[7][7] = new Piece(rook, white, this);

    //knights
    //black
    initial[0][1] = new Piece(knight, black, this);
    initial[0][6] = new Piece(knight, black, this);
    //white
    initial[7][1] = new Piece(knight, white, this);
    initial[7][6] = new Piece(knight, white, this);

    //bishops
    //black
    initial[0][2] = new Piece(bishop, black, this);
    initial[0][5] = new Piece(bishop, black, this);
    //white
    initial[7][2] = new Piece(bishop, white, this);
    initial[7][5] = new Piece(bishop, white, this);

    //queen
    //black
    initial[0][3] = new Piece(queen, black, this);
    //white
    initial[7][3] = new Piece(queen, white, this);

    //king
    //black
    initial[0][4] = new Piece(king, black, this);
    //white
    initial[7][4] = new Piece(king, white, this);

    //then copy over current to reflect initial (since we are setting up)
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            current[i][j] = initial[i][j];
        }
    }
    draw();
}

Board::Board(Xwindow *xwin, int rows, int columns) : xwin(xwin), initial(NULL), current(NULL), rows(rows), columns(columns) {
    init(rows, columns);
    draw();
}

/**
 * Private method
 * initializes an empty board with size specified
 */
void Board::init(int rows, int columns) {
    if (initial != NULL || current != NULL) {
        cerr << "ERROR: Board::init() should only be called in the constructor! ";
        cerr << "Potential memory leak here!" << endl;
    }
    initial = new Piece **[rows];
    current = new Piece **[rows];
    for (int i = 0; i < rows; i++) {
        initial[i] = new Piece *[columns];
        current[i] = new Piece *[columns];
        for (int j = 0; j < columns; j++) {
            initial[i][j] = NULL;
            current[i][j] = NULL;
        }
    }
}

Board::~Board() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            delete initial[i][j];
        }
        delete[] initial[i];
    }
    delete[] initial;
    while (!moves.empty()) {
        Move *m = moves.back();
        moves.pop_back();
        delete m;
    }
}

/**
 * Sets up board via commands from cin.
 * ONLY CALLED WHILE GAME IS IN SETUP STATE
 * Assumes there have been no moves!
 */
color_t Board::setup() {
    color_t turn = white; //by default

    bool keepGoing = true;
    string command;
    command = help::getCommand(keepGoing);
    while (keepGoing) {
        if (command == "+") {
            string piece = help::getCommand(keepGoing);
            string coords = help::getCommand(keepGoing);
            if (!help::isPiece(piece)) {
                cout << "ERROR processing piece. ";
                cout << piece << " is not a valid chess piece." << endl;
            }
            else if (!help::isCoords(coords)) {
                cout << "ERROR processing rank and file. ";
                cout << coords << " is not a coordinate on the chess board." << endl;
            } else {
                int row = rows - (coords[1] - '1') - 1;
                int column = coords[0] - 'a';
                if (initial[row][column] != NULL) {
                    delete initial[row][column];
                }
                initial[row][column] = new Piece(piece[0], this);
                current[row][column] = initial[row][column];
                this->draw(row, column);
            }
        } else if (command == "-") {
            string coords;
            coords = help::getCommand(keepGoing);
            if (help::isCoords(coords)) {
                int row = rows - (coords[1] - '1') - 1;
                int column = coords[0] - 'a';
                delete initial[row][column];
                initial[row][column] = NULL;
                current[row][column] = NULL;
                this->draw(row, column);
            } else {
                cout << "ERROR processing rank and file. ";
                cout << coords << " is not a coordinate on the chess board." << endl;
            }
        } else if (command == "=") {
            command = help::getCommand(keepGoing);
            if (command == "white") {
                turn = white;
            } else if (command == "black") {
                turn = black;
            } else {
                cout << "ERROR processing color: " << command << endl;
            }
        } else if (command == "print") {
            cout << (*this) << endl;
        } else if (command == "done") {
            //do the checks
            if (isProperlySetup()) {
                keepGoing = false;
            }
        } else if (command == "help") {
            cout << "Avaliable commands: " << endl;
            cout << "+ piece coords" << endl;
            cout << "- coords" << endl;
            cout << "= color" << endl;
            cout << "done" << endl << endl;
        } else {
            cout << "Sorry, the command " << command << " is not recognized" << endl;
        }
        if (keepGoing == true) {
            command = help::getCommand(keepGoing);
        }
    }

    return turn;
}

/**
 * Private method
 * checks if this is an acceptable setup (as according to pdf doc specifications)
 * i.e.
 * exactly one white and black king, no pawns on last or first row and neither king is in check
 */
bool Board::isProperlySetup() {
    //exactly one white and black king
    int whiteKingCount = 0, blackKingCount = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (current[i][j] != NULL) {
                if (current[i][j]->getType() == king && current[i][j]->getColor() == white) {
                    whiteKingCount++;
                }
                if (current[i][j]->getType() == king && current[i][j]->getColor() == black) {
                    blackKingCount++;
                }
            }
        }
    }
    if (whiteKingCount != 1) {
        cout << "Board is not properly setup." << endl;
        cout << "There are " << whiteKingCount << " white kings." << endl;
        return false;
    }
    if (blackKingCount != 1) {
        cout << "Board is not properly setup." << endl;
        cout << "There are " << blackKingCount << " black kings." << endl;
        return false;
    }

    //no pawns in first or last row
    for (int i = 0; i < columns; i++) {
        if (current[0][i] != NULL && current[0][i]->getType() == pawn) {
            cout << "Board is not properly setup." << endl;
            cout << "There is a pawn on the first row." << endl;
            return false;
        }
        else if (current[rows - 1][i] != NULL && current[rows - 1][i]->getType() == pawn) {
            cout << "Board is not properly setup." << endl;
            cout << "There is a pawn on the last row." << endl;
            return false;
        }
    }
    
    //checks if neither white nor black in check
    if (inCheck(white)) {
        cout << "Board is not properly setup." << endl;
        cout << "White is in check." << endl;
        return false;
    }
    if (inCheck(black)) {
        cout << "Board is not properly setup." << endl;
        cout << "Black is in check." << endl;
        return false;
    }

    return true;
}

/**
 * loops through the board to search for location of king 
 * assumes that there is only one king
 */
bool Board::inCheck(color_t player) {
    int kingRow = -1;
    int kingCol = -1;
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (current[i][j] != NULL 
            && current[i][j]->getType() == king 
            && current[i][j]->getColor() == player) {
                kingRow = i;
                kingCol = j;
            }
        }
    }
    if (kingRow == -1 || kingCol == -1) {
        cout << "ERROR: We could not find a king on this board." << endl;
    }

    //switch to the opposite colour
    if (player == white) {
        player = black;
    } else {
        player = white;
    }

    //loops through the enemy pieces to determine whether king is in check
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (current[i][j] != NULL && current[i][j]->getColor() == player) { //enemy piece
                Move *m = new Move(i, j, kingRow, kingCol);
                if (isLegalOnBoard(m, player) && current[i][j]->isLegal(m)) {
                    delete m;
                    return true;
                }
                delete m;
            }       
        }
    }
    return false;
}

bool Board::stalemate(color_t turn) {
    vector<Move *> legalMoves;
    if (turn == white) {
        legalMoves = generateWhiteMoves();
    } else {
        legalMoves = generateBlackMoves();
    }

    if (legalMoves.empty()) {
        return true;
    } else {
        while (!legalMoves.empty()) {
            Move *m = legalMoves[0];
            legalMoves.erase(legalMoves.begin());
            int oldRow = m->getOldRow(), oldCol = m->getOldCol(),
                newRow = m->getNewRow(), newCol = m->getNewCol();
            Piece *temp = current[newRow][newCol];
            current[newRow][newCol] = current[oldRow][oldCol]; 
            current[oldRow][oldCol] = NULL;
            if (!inCheck(turn)) {
                current[oldRow][oldCol] = current[newRow][newCol];
                current[newRow][newCol] = temp;
                delete m;
                help::deleteVector(legalMoves);
                return false;
            }
            current[oldRow][oldCol] = current[newRow][newCol];
            current[newRow][newCol] = temp;
            delete m;
        }
        help::deleteVector(legalMoves);
    }
    return true;
}

// POST: returns true if player is checkmated
bool Board::checkmate(color_t player) {
    color_t opponent;
    int kingRow = -1, kingCol = -1;
    vector<Move *> kingMoves;
    vector<Move *> checkMoves;

    if (player == white) {
        opponent = black;
    } else {
        opponent = white;
    }

    // find out the square that the King is on
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (current[i][j] != NULL 
            && current[i][j]->getType() == king 
            && current[i][j]->getColor() == player) {
                kingRow = i;
                kingCol = j;
            }
        }
    }

    // find out which pieces are currently checking the King  
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (current[i][j] != NULL && current[i][j]->getColor() == opponent) {
                Move *m = new Move(i, j, kingRow, kingCol); 
                if (isLegalOnBoard(m, opponent) && current[i][j]->isLegal(m)) {
                    checkMoves.push_back(m);   
                }
            }
        }
    }

    // if there are no pieces that are currently checking the King, then the player is not checkmated
    if (checkMoves.empty()) {
        return false;
    }

    // if there is only one piece, then there are two options
    if (checkMoves.size() == 1) {
        // can one of the player's pieces capture the checking piece
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                if (current[i][j] != NULL && current[i][j]->getColor() == player) {
                    Move *m = new Move(i, j, kingRow, kingCol);
                    if (isLegalOnBoard(m, opponent) && current[i][j]->isLegal(m)) {
                        delete m;
                        return false;
                    }
                    delete m;
                }
            }
        }

        // can one of the player's pieces block the checking piece
        int oldRow = checkMoves[0]->getOldRow(), oldCol = checkMoves[0]->getOldCol(),
            newRow = checkMoves[0]->getNewRow(), newCol = checkMoves[0]->getNewCol();
        int rowDiff = abs(oldRow - newRow);
        int colDiff = abs(oldCol - newCol);
        if (oldRow == newRow || oldCol == newCol || rowDiff == colDiff) {
            int rowInc = 0;
            int colInc = 0;
            if (oldRow < newRow) { 
                    rowInc = 1;
            } else if (oldRow > newRow) { 
                    rowInc = -1;
            }
            
            if (oldCol < newCol) {
                    colInc = 1;
            } else if (oldCol > newCol) {
                    colInc = -1;
            }

            oldRow += rowInc;
            oldCol += colInc;
            while (oldRow != newRow || oldCol != newCol) {
                for (int i = 0; i < rows; ++i) {
                    for (int j = 0; j < columns; ++j) {
                        if (current[i][j] != NULL && current[i][j]->getColor() == player) {
                            Move *m = new Move(i, j, checkMoves[0]->getOldRow(), checkMoves[0]->getOldCol());
                            if (isLegalOnBoard(m, player) && current[i][j]->isLegal(m)) {
                                return false;
                            }
                        } 
                    }
                }
                oldRow += rowInc;
                oldCol += colInc;
            }
        }
    }

    // can the King move away or capture the pieces?
    kingMoves = generateMoves(kingRow, kingCol);
    if (!kingMoves.empty()) {
        for (int i = 0; i < kingMoves.size(); ++i) {
            int oldRow = kingMoves[i]->getOldRow(), oldCol = kingMoves[i]->getOldCol(),
                newRow = kingMoves[i]->getNewRow(), newCol = kingMoves[i]->getNewCol();
            Piece *temp = current[newRow][newCol];
            current[newRow][newCol] = current[oldRow][oldCol]; 
            current[oldRow][oldCol] = NULL;   
            if (!inCheck(player)) {
                cout << newRow << " " << newCol << endl;
                current[oldRow][oldCol] = current[newRow][newCol];
                current[newRow][newCol] = temp;
                help::deleteVector(kingMoves);
                return false;
            } 
            current[oldRow][oldCol] = current[newRow][newCol];
            current[newRow][newCol] = temp;
        }
        help::deleteVector(kingMoves);
    } 

    // if there is nothing else that the player can do, they lose
    return true;
}

/** 
 * checks if the move is legal WRT to the board
 * This method checks for basic legal conditions
 * It doesn't know anything about the piece's themselves
 * returns true if the move was successful, false otherwise
 */
bool Board::isLegalOnBoard(Move *m, color_t player) const {
    int oldRow = m->getOldRow(), oldCol = m->getOldCol(),
        newRow = m->getNewRow(), newCol = m->getNewCol();
    // cout << oldRow << " " << oldCol << "  " << newRow << " " << newCol << endl;
    if ((newRow > rows && newRow < 0) || (newCol > columns && newCol < 0)) {
        //Out of bounds.
        return false;
    }
    else if (oldRow == newRow && oldCol == newCol) {
        //cout << "You can't move to the same spot."
        return false;
    } else if (current[oldRow][oldCol] == NULL) {
        //There is no piece to move there.
        return false;
    } else if (current[oldRow][oldCol]->getColor() != player) {
        //You can't move the opponent's piece.
        return false;
    } else if (current[newRow][newCol] != NULL && current[newRow][newCol]->getColor() == player) {
        //You can't move onto your own piece.
        return false;
    } else {
        return true;
    }
}

/**
 * returns true if the move was successful, false otherwise
 */
bool Board::move(Move *m, color_t player) {
    if (isLegalOnBoard(m, player)) {
        int newRow = m->getNewRow(), newCol = m->getNewCol();
        if (current[m->getOldRow()][m->getOldCol()]->move(m)) {
            // move checks if the move is legal first and applies the move to the piece and board
            // add move to stack.
            moves.push_back(m);
            // promotion
            if (current[newRow][newCol]->getType() == pawn && (newRow == 7 || newRow == 0)) {
                char piece;
                cin >> piece;
                if (piece == 'Q' || piece == 'q') {
                    current[newRow][newCol]->setPimpl(queen);
                } else if (piece == 'R' || piece == 'r') {
                    current[newRow][newCol]->setPimpl(rook);
                } else if (piece == 'N' || piece == 'n') {
                    current[newRow][newCol]->setPimpl(knight);
                } else if (piece == 'B' || piece == 'b') {
                    current[newRow][newCol]->setPimpl(bishop);
                }
            }
            return true;
        }
    } 
    delete m;
    return false;
}

Piece *** Board::getCurrent() {
    return current;
}

vector<Move *> Board::getMoves() {
    return moves;
}

// PRE: current[oldRow][oldCol] != NULL
// POST: return a list of all the legal moves from the square
vector<Move *> Board::generateMoves(int oldRow, int oldCol) {
    vector<Move *> legalMoves;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            Move *m = new Move(oldRow, oldCol, i, j);
            if (isLegalOnBoard(m, current[oldRow][oldCol]->getColor()) && current[oldRow][oldCol]->isLegal(m)) {
                legalMoves.push_back(m);
            }
        }
    }
    return legalMoves;
}

vector<Move *> Board::generateWhiteMoves() {
    vector<Move *> legalMoves;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (current[i][j] != NULL && current[i][j]->getColor() == white) {
                vector<Move *> pieceMoves = generateMoves(i, j); 
                legalMoves.insert(legalMoves.end(), pieceMoves.begin(), pieceMoves.end());
            }
        }
    }
    return legalMoves;
}

vector<Move *> Board::generateBlackMoves() {
    vector<Move *> legalMoves;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (current[i][j] != NULL && current[i][j]->getColor() == black) {
                vector<Move *> pieceMoves = generateMoves(i, j); 
                legalMoves.insert(legalMoves.end(), pieceMoves.begin(), pieceMoves.end());
            }
        }
    }
    return legalMoves;    
}

/**
 * Redraw entire screen
 */
void Board::draw() {
    int cellWidth = 500/(columns+1);
    int cellHeight = 500/(rows+1);
    for (int i = 0; i < rows; i++) { //draw 8 - 1
        xwin->fillRectangle(0, (i*cellHeight) + 1, cellWidth, cellHeight, Xwindow::Yellow);
        string word(1, '8' - i);
        xwin->drawString(cellWidth/2, (i*cellHeight) + 1 + (cellHeight/2), word);
    }
    for (int j = 0; j < columns; j++) { //draw a - h
        xwin->fillRectangle(((j+1)*cellWidth) + 1, 499 - cellHeight, cellWidth, cellHeight, Xwindow::Yellow);
        string word(1, 'a' + j);
        xwin->drawString(cellWidth + (j*cellWidth) + 1 + (cellWidth/2), 500-(cellHeight/2), word);
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            this->draw(i, j); //call function draw below
        }
    }
}

void Board::draw(int row, int col) {
    int cellWidth = 500/(columns+1);
    int cellHeight = 500/(rows+1);
    int color;
    if ((row + col) % 2 == 0) { //white
        color = Xwindow::White;
    } else { //black
        color = Xwindow::Black;
    }
    xwin->fillRectangle((col+1)*cellWidth+1, row*cellHeight+1, cellWidth, cellHeight, color);
    if (current[row][col] != NULL) {
        stringstream ss;
        ss << *(current[row][col]);
        string word = ss.str();
        if ((row + col) % 2 == 0) { //opposite color, or black
            color = Xwindow::Black;
        } else { //black
            color = Xwindow::White;
        }
        xwin->drawString(((col+1)*cellWidth) + 1 + (cellWidth/2), //need offset to put in middle of square
                         (row*cellHeight) + 1 + (cellHeight/2), word, color);
    }
}

/**
 * prints out current
 */
ostream &operator<<(ostream &out, const Board &b) {
    for (int i = 0; i < b.rows; i++) {
        out << b.rows - i << " ";
        for (int j = 0; j < b.columns; j++) {
            if (b.current[i][j] == NULL) {
                if ((i + j) % 2 == 0) { //white
                    out << " ";
                } else { //black
                    out << "_";
                }
            } else {
                out << *(b.current[i][j]);
            }
        }
        out << endl;
    }
    out << endl << "  ";
    for (int i = 0; i < b.columns; i++) {
        out << (char) (i + 'a');
    }
    out << endl;
    return out;
}
