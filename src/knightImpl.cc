/**
 * knightImpl.cc
 * Provides implementation for knight
 *
 * Author: Chun Li and Weichen Zhou
 * Created: Nov 21, 2013.
 */

#include <iostream>
#include <cstdlib>

#include "knightImpl.h"

using namespace std;

bool KnightImpl::isLegal(Move *m) const {
    int rowDiff = abs(m->getOldRow() - m->getNewRow());
    int colDiff = abs(m->getOldCol() - m->getNewCol());
    return (rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2);
}

KnightImpl::KnightImpl(color_t color, Board * b) : 
    PieceImpl(color, b) {}

piece_t KnightImpl::getType() const {
    return knight;
}

void KnightImpl::print(ostream &out) const {
    if (color == black) {
        out << "n";
    } else { //white
        out << "N";
    }
}
