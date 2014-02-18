#ifndef __PAWN_IMPL_H__
#define __PAWN_IMPL_H__
/**
 * pawnImpl.h
 * Provides implementation for a pawn's functions
 *
 * Author: Chun Li and Weichen Zhou
 * Created: Nov. 21, 2013.
 */

#include <cstdlib>
#include <vector>
#include <iostream>
 
#include "pieceImpl.h"

struct PawnImpl : public PieceImpl {
    public:
        PawnImpl(color_t color, Board * b);
        //returns true if move was successful, false otherwise
        bool isLegal(Move *m) const;
        void print(std::ostream &out) const;
        piece_t getType() const;
    private:
        //have to overload to take into account for
        //en passant and pawn promotion
        bool applyMove(Move *m);
        //returns true if m is a legal en passant move 
        bool en_passant(Move *m) const;
};

#endif /* pawnImpl.h */
