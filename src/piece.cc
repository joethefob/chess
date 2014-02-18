/**
 * Piece.cc
 * Implementation of piece class
 *
 * Author: Chun Li, Weichen Zhou
 * Created: Nov 16, 2013.
 */

#include "piece.h"
#include "move.h"
#include "pieceImpl.h"
#include "pawnImpl.h"
#include "knightImpl.h"
#include "bishopImpl.h"
#include "rookImpl.h"
#include "queenImpl.h"
#include "kingImpl.h"

using namespace std;

/*** PRIVATE METHODS ***/
PieceImpl * Piece::getPimpl(piece_t piece, color_t color, Board * b) {
    switch(piece) {
    case pawn:
        return new PawnImpl(color, b);
    case knight:
        return new KnightImpl(color, b);
    case bishop:
        return new BishopImpl(color, b);
    case rook:
        return new RookImpl(color, b);
    case queen:
        return new QueenImpl(color, b);
    case king:
        return new KingImpl(color, b);
    }
}

/*** PUBLIC METHODS ***/
Piece::Piece(piece_t piece, color_t color, Board * b) {
    pimpl = getPimpl(piece, color, b);
}

/**
 * Builds a new piece, where the char piece represents its color and piece type
 */
Piece::Piece(char piece, Board * b) {
    color_t color;
    if (piece >= 'A' && piece <= 'Z') {
        color = white;
    } else if (piece >= 'a' && piece <= 'z') {
        color = black;
        piece -= 32; //make uppercase
    } else {
        cerr << piece << " is not a valid piece!" << endl;
    }
    switch(piece) {
    case 'P':
        pimpl = getPimpl(pawn, color, b);
        break;
    case 'N':
        pimpl = getPimpl(knight, color, b);
        break;
    case 'B':
        pimpl = getPimpl(bishop, color, b);
        break;
    case 'R':
        pimpl = getPimpl(rook, color, b);
        break;
    case 'Q':
        pimpl = getPimpl(queen, color, b);
        break;
    case 'K':
        pimpl = getPimpl(king, color, b);
        break;
    }
}

Piece::~Piece() {
    delete pimpl;
}

bool Piece::isLegal(Move *m) {
    return pimpl->isLegal(m);
}

bool Piece::move(Move *m) {
    return pimpl->move(m);
}

/**
 * Only changes the implementation of methods, copies all fields
 */
void Piece::setPimpl(piece_t piece) {
    PieceImpl * tmp_pimpl = getPimpl(piece, pimpl->color, pimpl->b);
    delete pimpl;
    pimpl = tmp_pimpl;
}

piece_t Piece::getType() {
    return pimpl->getType();
}

color_t Piece::getColor() {
    return pimpl->color;
}

ostream &operator<<(std::ostream &out, const Piece &p) {
    out << *(p.pimpl);
    return out;
}
