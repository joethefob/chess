#ifndef __QUEEN_IMPL_H__
#define __QUEEN_IMPL_H__
/**
 * queenImpl.h
 * Provides implementation for a queen's functions
 *
 * Author: Chun Li and Weichen Zhou
 * Created: Nov. 21, 2013.
 */

#include <iostream>

#include "pieceImpl.h"

struct QueenImpl : public PieceImpl {
    public:
        QueenImpl(color_t color, Board * b);
        piece_t getType() const;
        //returns true if move was successful, false otherwise
        void print(std::ostream &out) const;
        bool isLegal(Move *m) const;
};

#endif /* queenImpl.h */
