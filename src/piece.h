/**
 * Piece.h
 * Abstract piece class
 *
 * Author: Chun Li, Weichen Zhou
 * Created: Nov 16, 2013.
 */

#ifndef __PIECE_H__
#define __PIECE_H__

#include <iostream>

#include "enum.h"

struct PieceImpl;
class Board;
struct Move;

/**
 * Defines an abstraction for all chess pieces
 */
class Piece {
    //private:
        PieceImpl *pimpl;
        PieceImpl *getPimpl(piece_t piece, color_t color, Board * b);
    public:
        Piece(piece_t piece, color_t color, Board * b);
        Piece(char piece, Board * b);
        ~Piece();
        //returns true if the move is legal WRT to the piece, false otherwise
        bool isLegal(Move *m);
        //returns true if move was successful, false otherwise
        bool move(Move *m);
        //sets pimpl to new piece Implementation
        //for pawn promotion
        void setPimpl(piece_t piece);
        //returns the piece type
        piece_t getType();
        //returns the piece color
        color_t getColor();
        friend std::ostream &operator<<(std::ostream &out, const Piece &p);	    
};

#endif /* piece.h */
