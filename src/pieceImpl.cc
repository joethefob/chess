/**
 * pieceImpl.cc
 * Partial implementation for pieceImpl
 *
 * Author: Chun Li
 * Created: Nov. 21, 2013.
 */

#include <iostream>
#include <cstdlib>

#include "pieceImpl.h"

using namespace std;

/*** PRIVATE METHODS ***/

/**
 * Applies the move to the board. If it returns false, the move was illegal and
 * the board is unchanged.
 * 99% of the time, this method doesn't need to be overloaded.
 * Notable exceptions are castling, and en passent (need to delete)
 * Note that this method also never deletes any pieces from memory - we simply
 * lose the pointer in current. We do memory cleanup at the end.
 */
bool PieceImpl::applyMove(Move *m) {
    //update current
    int oldRow = m->getOldRow(), oldCol = m->getOldCol(),
        newRow = m->getNewRow(), newCol = m->getNewCol();
    //save player color and potential killed piece
    Piece *** current = b->getCurrent();
    color_t player = current[oldRow][oldCol]->getColor();
    Piece *piece = current[newRow][newCol];

    current[newRow][newCol] = current[oldRow][oldCol];
    current[oldRow][oldCol] = NULL;

    if (b->inCheck(player)) { //reverse the change
        current[oldRow][oldCol] = current[newRow][newCol];
        current[newRow][newCol] = piece;
        return false;
    } else {
        b->draw(oldRow, oldCol);
        b->draw(newRow, newCol);
        return true;
    }
}

/*** PUBLIC METHODS ***/

PieceImpl::PieceImpl(color_t color, Board * b) :
    color(color), b(b) {}

PieceImpl::~PieceImpl() {}

/**
 * Checks if the move is legal for this piece. If it is, it applies the move to
 * the piece and the board.
 * This method is called assuming the move doesn't move off the board, and
 * it is moving the player's piece to a space not occupied already by one of 
 * his own pieces.
 *
 * Returns true if the move was sucessful (legal). False otherwise.
 */
bool PieceImpl::move(Move *m) {
    if (isLegal(m)) {
        return applyMove(m);
    }
    return false;
}

ostream &operator<<(ostream &out, const PieceImpl &pimpl) {
    pimpl.print(out);
    return out;
}
