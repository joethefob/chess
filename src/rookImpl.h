#ifndef __ROOK_IMPL_H__
#define __ROOK_IMPL_H__
/**
 * rookImpl.h
 * Provides implementation for a rook's functions
 *
 * Author: Chun Li and Weichen Zhou
 * Created: Nov. 21, 2013.
 */

#include <iostream>

#include "pieceImpl.h"

struct RookImpl : public PieceImpl {
    public:
        RookImpl(color_t color, Board * b);
        //returns true if move was successful, false otherwise
        void print(std::ostream &out) const;
        piece_t getType() const;
        bool isLegal(Move *m) const;
};

#endif /* rookImpl.h */
