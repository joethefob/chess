/**
 * bishopImpl.cc
 * Provides implementation for bishop
 *
 * Author: Chun Li and Weichen Zhou
 * Created: Nov 21, 2013.
 */

#include <iostream>
#include <cstdlib>

#include "bishopImpl.h"
#include "piece.h"
#include "board.h"

using namespace std;

bool BishopImpl::isLegal(Move *m) const {
    int oldRow = m->getOldRow(), oldCol = m->getOldCol(),
        newRow = m->getNewRow(), newCol = m->getNewCol();
    int rowDiff = abs(oldRow - newRow);
    int colDiff = abs(oldCol - newCol);
    if (rowDiff == colDiff) {
        //check if there is a piece in between
        //go from old pos. to new pos.
        int rowInc = 1; //are we going up or down
        int colInc = 1; //are we going left or right
        if (oldRow > newRow) {
            rowInc = -1; //go up
        }
        if (oldCol > newCol) {
            colInc = -1; //go left
        }
        oldRow += rowInc;
        oldCol += colInc;
        Piece *** current = b->getCurrent();
        while (oldRow != newRow || oldCol != newCol) { //don't check newRow and newCol
            if (current[oldRow][oldCol] != NULL) { //if there is a piece in between
                return false;
            }
            oldRow += rowInc;
            oldCol += colInc;
        }
        return true;
    } else {
        return false;
    }
}

BishopImpl::BishopImpl(color_t color, Board * b) : 
    PieceImpl(color, b) {}

piece_t BishopImpl::getType() const {
    return bishop;
}

void BishopImpl::print(ostream &out) const {
    if (color == black) {
        out << "b";
    } else { //white
        out << "B";
    }
}
