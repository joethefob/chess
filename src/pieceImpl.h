#ifndef __PIECE_IMPL_H__
#define __PIECE_IMPL_H__

/**
 * pieceImpl.h
 * base struct to hold piece implementation
 *
 * Author: Chun Li and Weichen Zhou
 * Created: Nov 21, 2013.
 */

#include <iostream>

#include "enum.h"
#include "move.h"
#include "piece.h"
#include "board.h"

struct PieceImpl {
    public:
        color_t color; //color of piece
        Board * b; //pointer to the current board this piece is on
        
        PieceImpl(color_t color, Board * b);
        virtual ~PieceImpl();
        //returns true if move was successful, false otherwise
        virtual bool move(Move *m);
        //returns true if move is legal, false otherwise
        virtual bool isLegal(Move *m) const = 0;
        virtual void print(std::ostream &out) const = 0;
        virtual piece_t getType() const = 0;
        friend std::ostream &operator<<(std::ostream &out, const PieceImpl &pimpl);
    private:
        //applies the move to the piece and the board.
        //private because it doesn't do any checks if move is legal or not
        //if you want to make a move, use move instead.
        //in 99% of cases, this does not have to be overloaded.
        //a notable exception is castling
        //also en passent, because we have to delete a pawn
        virtual bool applyMove(Move *move);
};

#endif /* pieceImpl.h */
