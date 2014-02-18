/**
 * pawnImpl.cc
 * Provides implementation for pawn
 *
 * Author: Chun Li and Weichen Zhou
 * Created: Nov 21, 2013.
 */

#include <iostream>

#include "pawnImpl.h"

using namespace std;

/*** PRIVATE FUNCTIONS ***/
bool PawnImpl::applyMove(Move *m) {
    int oldRow = m->getOldRow(), oldCol = m->getOldCol(),
        newRow = m->getNewRow(), newCol = m->getNewCol();
    Piece *** current = b->getCurrent();
    color_t player = current[oldRow][oldCol]->getColor();
    Piece * piece = current[newRow][newCol];

    // en passant
    if (en_passant(m)) {
        current[oldRow][newCol] = NULL; //"passed" pawn
        current[newRow][newCol] = current[oldRow][oldCol];
        current[oldRow][oldCol] = NULL;
        //update drawing
        b->draw(oldRow, newCol);
        b->draw(newRow, newCol);
        b->draw(oldRow, oldCol);
        return true;
    }

    // move forward or capturing
    else {
        current[newRow][newCol] = current[oldRow][oldCol];
        current[oldRow][oldCol] = NULL;
    }
    if (b->inCheck(player)) { //reverse the change (note not possible for enpassent)
        current[oldRow][oldCol] = current[newRow][newCol];
        current[newRow][newCol] = piece;
        return false;
    } else {
        //otherwise, update
        b->draw(oldRow, oldCol);
        b->draw(newRow, newCol);
        return true;
    }
}

// PRE: the piece that is moving is a pawn
// PRE: the piece is moving diagonally to the left or right, by one step up
// POST: returns true if m is a legal en passant, false otherwise 
bool PawnImpl::en_passant(Move *m) const {
    int oldRow = m->getOldRow(), oldCol = m->getOldCol(),
        newRow = m->getNewRow(), newCol = m->getNewCol();
    Piece ***current = b->getCurrent();
    int step = 0;
    vector<Move *> moves = b->getMoves();
    color_t opponent;

    if (color == white) {
        step = -1;
        opponent = black;
    } else {
        step = 1;
        opponent = white;
    }

    // check if the captured pawn of the right colour is on the correct square
    if (current[oldRow][newCol] == NULL 
        || current[oldRow][newCol]->getType() != pawn
        || current[oldRow][newCol]->getColor() != opponent) {
        return false;
    } 

    // check if the last move was a double-step by the captured pawn
    Move *last = moves.back();
    
    if (current[last->getNewRow()][last->getNewCol()] == NULL
        || current[last->getNewRow()][last->getNewCol()]->getType() != pawn
        || current[last->getNewRow()][last->getNewCol()]->getColor() != opponent) {
        // check if the last piece to move was a pawn
        return false;
    } else if (last->getOldCol() != newCol && last->getNewCol() != newCol) {
        // check if the captured pawn is on the correct file 
        return false;
    } else if (last->getOldRow() - last->getNewRow() != 2 * step) {
        // check if the cpatured pawn made a double step
        return false;
    }
    
    // check if the move will result in a check (rare) 
    Piece *captured = current[oldRow][newCol];
    current[oldRow][newCol] = NULL;
    current[newRow][newCol] = current[oldRow][oldCol];
    current[oldRow][oldCol] = NULL;
    if (b->inCheck(color)) {
        current[oldRow][oldCol] = current[newRow][newCol];
        current[oldRow][newCol] = captured;
        current[newRow][newCol] = NULL;
        return false;
    }
    current[oldRow][oldCol] = current[newRow][newCol];
    current[oldRow][newCol] = captured;
    current[newRow][newCol] = NULL;
    return true;
}
 
/*** PUBLIC FUNCTIONS ***/
// PRE: piece exists, i.e. current[oldRow][oldCol] != NULL
//      piece is not moving to the same spot, i.e. oldRow != newRol && oldCol != newCol
//      the destination does not contain a piece of the same colour
// POST: return true if m is a legal move for a pawn, false otherwise
bool PawnImpl::isLegal(Move *m) const {
    int oldRow = m->getOldRow(), oldCol = m->getOldCol(),
        newRow = m->getNewRow(), newCol = m->getNewCol();
    Piece ***current = b->getCurrent();
    int horizontal = newCol - oldCol;
    int vertical = newRow - oldRow;
    int step = 0, pawnRow = 0, lastRow = 0;

    if (color == white) {
        step = -1;
        pawnRow = 6;
        lastRow = 0;
    } else {
        step = 1;
        pawnRow = 1;
        lastRow = 7;
    }

    if (horizontal == 0 && vertical == step && current[newRow][newCol] == NULL) { 
        // pawn moves one step forward
        return true;
    } else if (horizontal == 0 && vertical == 2 * step && oldRow == pawnRow && current[newRow][newCol] == NULL) { 
        // pawn moves two steps forward from initial
        return true;
    } else if (abs(horizontal) == 1 && vertical == step && current[newRow][newCol] != NULL) { 
        // pawn captures
        return true;
    } else if (abs(horizontal) == 1 && vertical == step && current[newRow][newCol] == NULL) {
        // en passant
        return en_passant(m);
    } 
    else { 
        return false;
    }
}

PawnImpl::PawnImpl(color_t color, Board * b) : 
    PieceImpl(color, b) {}

piece_t PawnImpl::getType() const {
    return pawn;
}

void PawnImpl::print(ostream &out) const {
    if (color == black) {
        out << "p";
    } else { //white
        out << "P";
    }
}
