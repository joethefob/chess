#ifndef __KNIGHT_IMPL_H__
#define __KNIGHT_IMPL_H__
/**
 * pawnImpl.h
 * Provides implementation for a pawn's functions
 *
 * Author: Chun Li and Weichen Zhou
 * Created: Nov. 21, 2013.
 */

#include <iostream>

#include "pieceImpl.h"

struct KnightImpl : public PieceImpl {
    public:
        KnightImpl(color_t color, Board * b);
        //returns true if move was successful, false otherwise
        void print(std::ostream &out) const;
        piece_t getType() const;
        bool isLegal(Move *m) const;
};

#endif /* knightImpl.h */
