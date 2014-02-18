#ifndef __KING_IMPL_H__
#define __KING_IMPL_H__
/**
 * kingImpl.h
 * Provides implementation for a king's functions
 *
 * Author: Chun Li and Weichen Zhou
 * Created: Nov. 21, 2013.
 */

#include <iostream>
#include <vector>

#include "pieceImpl.h"

struct KingImpl : public PieceImpl {
    public:
        KingImpl(color_t color, Board * b);
        //returns true if move was successful, false otherwise
        void print(std::ostream &out) const;
        piece_t getType() const;
        bool isLegal(Move *m) const;
    private:
        // returns true if Rook can castle, false otherwise
        bool isRookCastle(Move *move) const;
        //returns true if m is a castle, false otherwise
        bool isCastle(Move *m) const;
        //override for castle
        bool applyMove(Move *move);
};

#endif /* kingImpl.h */
