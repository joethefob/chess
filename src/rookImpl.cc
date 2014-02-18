/**
 * rookImpl.cc
 * Provides implementation for rook
 *
 * Author: Chun Li and Weichen Zhou
 * Created: Nov 21, 2013.
 */

#include <iostream>

#include "rookImpl.h"
#include "piece.h"
#include "board.h"

using namespace std;

bool RookImpl::isLegal(Move *m) const {
    int oldRow = m->getOldRow(), oldCol = m->getOldCol(),
        newRow = m->getNewRow(), newCol = m->getNewCol();
    if (oldRow == newRow || oldCol == newCol) {
        //check if there is a piece in between
        int rowInc = 0;
        int colInc = 0;
        if (oldRow < newRow) { //go down
            rowInc = 1;
        } else if (oldRow > newRow) { //go up
            rowInc = -1;
        }
        if (oldCol < newCol) {
            colInc = 1;
        } else if (oldCol > newCol) {
            colInc = -1;
        }

        oldRow += rowInc;
        oldCol += colInc;
        Piece *** current = b->getCurrent();
        while (oldRow != newRow || oldCol != newCol) {
            if (current[oldRow][oldCol] != NULL) { //theres a piece
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

RookImpl::RookImpl(color_t color, Board * b) : 
    PieceImpl(color, b) {}

piece_t RookImpl::getType() const {
    return rook;
}

void RookImpl::print(ostream &out) const {
    if (color == black) {
        out << "r";
    } else { //white
        out << "R";
    }
}
