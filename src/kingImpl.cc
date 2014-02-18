/**
 * kingImpl.cc
 * Provides implementation for king
 *
 * Author: Chun Li and Weichen Zhou
 * Created: Nov 21, 2013.
 */

#include <iostream>
#include <cstdlib>

#include "kingImpl.h"

using namespace std;

/*** PRIVATE METHODS ***/

// PRE: King's final position has no piece occupied on it
// POST: return true if the Rook can castle
bool KingImpl::isRookCastle(Move *move) const { 
    int kingOldRow = move->getOldRow(), kingOldCol = move->getOldCol(),
        kingNewCol = move->getNewCol();
    int rookOldRow = kingOldRow;
    int rookOldCol, rookNewCol;
    if (kingNewCol == 6) { // Kingside castling
        rookOldCol = kingNewCol + 1;
        rookNewCol = kingNewCol - 1;
    } else if (kingNewCol == 2) { // Queenside castling
        rookOldCol = kingNewCol - 2;
        rookNewCol = kingNewCol + 1;
    }
    else {
        return false;
    }
    
    // Rook's move
    Piece *** current = b->getCurrent();
    vector<Move *> moves = b->getMoves();
    Piece *piece = current[rookOldRow][rookOldCol];
    // check if the piece is the right rook of the right colour
    if (piece == NULL || piece->getType() != rook || piece->getColor() != color) {
        return false;
    }

    // check if there are pieces between the King and the Rook
    int lower = rookOldCol;
    int higher = kingOldCol;
    if (lower > higher) {
        int temp = lower;
        lower = higher;
        higher = temp;
    }
    for (int i = lower + 1; i < higher; ++i) {
        if (current[kingOldRow][i] != NULL) {
            return false;
        }
    }

    // check if Rook has been moved before
    for (int i = 0; i < moves.size(); ++i) {
        if (moves[i]->getOldRow() == rookOldRow && moves[i]->getOldCol() == rookOldCol) {
            return false;
        }
    }
    // if all of these conditions are satisfied, the rook can castle
    return true;
}

// PRE: King's final position has no piece of the same colour occupying it
//      King is of the right colour
// POST: true if castling is legal, false otherwise
bool KingImpl::isCastle(Move *m) const {
    int oldRow = m->getOldRow(), oldCol = m->getOldCol(),
        newRow = m->getNewRow(), newCol = m->getNewCol();
    int step = oldCol + (newCol - oldCol) / 2;
    vector<Move *> moves = b->getMoves();
    Piece ***current = b->getCurrent();
    // check if King is in the correct starting position
    if (oldCol != 4 || (oldRow != 7 && oldRow != 0)) {
        return false;
    }

    // check if King is going to the correct final position
    // i.e. if it's moving two steps
    if (newRow != oldRow || abs(newCol - oldCol) != 2) {
        return false;
    }

    // check if King has been moved before
    for (int i = 0; i < moves.size(); ++i) {
        if (moves[i]->getOldRow() == oldRow && moves[i]->getOldCol() == oldCol) {
            return false;
        }
    }

    // check if there is a piece in the way 
    if (current[newRow][step] != NULL || current[newRow][newCol] != NULL) {
        return false;
    }

    // check if moving will result in the King being checked 
    // one step
    current[newRow][step] = current[oldRow][oldCol];
    current[oldRow][oldCol] = NULL;
    if (b->inCheck(color)) {
        current[oldRow][oldCol] = current[newRow][step];
        current[newRow][step] = NULL;
        return false;
    }
    current[oldRow][oldCol] = current[newRow][step];
    current[newRow][step] = NULL;

    // two steps
    current[newRow][newCol] = current[oldRow][oldCol];
    current[oldRow][oldCol] = NULL;
    if (b->inCheck(color)) {
        current[oldRow][oldCol] = current[newRow][newCol];
        current[newRow][newCol] = NULL;
        return false;
    }
    current[oldRow][oldCol] = current[newRow][newCol];
    current[newRow][newCol] = NULL;

    if (oldRow == 7) { // white King castling 
        if (newRow == oldRow && newCol == 6) { // white Kingside castling
            return isRookCastle(m);
        } else if (newRow == oldRow && newCol == 2) { // white Queenside castling
            return isRookCastle(m);
        } else {
            return false;
        }
    } else if (oldRow == 0) { // black King castling
        if (newRow == oldRow && newCol == 6) { // black Kingside castling
            return isRookCastle(m);
        } else if (newRow == oldRow && newCol == 2) {
            return isRookCastle(m);
        } else {
            return false;
        }
    } else {
        return false;
    }
}

// PRE: move is valid
// POST: void
// Applies the move on current
bool KingImpl::applyMove(Move *move) {
    int oldRow = move->getOldRow(), oldCol = move->getOldCol(),
        newRow = move->getNewRow(), newCol = move->getNewCol();
    Piece *** current = b->getCurrent();
    color_t player = current[oldRow][oldCol]->getColor();
    Piece * piece = current[newRow][newCol];

    if (isCastle(move)) {
        if (newCol == 6) { // Kingside castling
            current[oldRow][newCol - 1] = current[oldRow][newCol + 1];
            current[oldRow][newCol + 1] = NULL;
            current[newRow][newCol] = current[oldRow][oldCol];
            current[oldRow][oldCol] = NULL;
            b->draw(oldRow, newCol - 1);
            b->draw(oldRow, newCol + 1);
            b->draw(newRow, newCol);
            b->draw(oldRow, oldCol);
        } else { // Queenside castling
            current[oldRow][newCol + 1] = current[oldRow][newCol - 2];
            current[oldRow][newCol - 2] = NULL;
            current[newRow][newCol] = current[oldRow][oldCol];
            current[oldRow][oldCol] = NULL;
            b->draw(oldRow, newCol + 1);
            b->draw(oldRow, newCol - 2);
            b->draw(newRow, newCol);
            b->draw(oldRow, oldCol);
        }
        return true;
    } 
    current[newRow][newCol] = current[oldRow][oldCol];
    current[oldRow][oldCol] = NULL;

    if (b->inCheck(player)) { //reverse the change
        current[oldRow][oldCol] = current[newRow][newCol];
        current[newRow][newCol] = piece;
        return false;
    } else {
        //update drawing
        b->draw(oldRow, oldCol);
        b->draw(newRow, newCol);
        return true;
    }
}

/*** PUBLIC METHODS ***/

bool KingImpl::isLegal(Move *m) const {
    int oldRow = m->getOldRow(), oldCol = m->getOldCol(),
        newRow = m->getNewRow(), newCol = m->getNewCol();
    int rowDiff = abs(oldRow - newRow);
    int colDiff = abs(oldCol - newCol);
    if (rowDiff == 1 && colDiff == 0) { //horizontal one step move
        return true;
    } else if (rowDiff == 0 && colDiff == 1) { //vertical one step move
        return true;
    } else if (rowDiff == 1 && colDiff == 1) { //diagonal one step move
        return true;
    } else {
        if (isCastle(m)) { //castling
            return true;
        }
        return false;
    }
}

KingImpl::KingImpl(color_t color, Board * b) : 
    PieceImpl(color, b) {}

piece_t KingImpl::getType() const {
    return king;
}

void KingImpl::print(ostream &out) const {
    if (color == black) {
        out << "k";
    } else { //white
        out << "K";
    }
}
