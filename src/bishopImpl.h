#ifndef __BISHOP_IMPL_H__
#define __BISHOP_IMPL_H__
/**
 * bishopImpl.h
 * Provides implementation for a bishop's functions
 *
 * Author: Chun Li and Weichen Zhou
 * Created: Nov. 21, 2013.
 */

#include <iostream>

#include "pieceImpl.h"

struct BishopImpl : public PieceImpl {
    public:
        BishopImpl(color_t color, Board * b);
        //returns true if move was successful, false otherwise
        void print(std::ostream &out) const;
        piece_t getType() const;
        bool isLegal(Move *m) const;
};

#endif /* bishopImpl.h */
