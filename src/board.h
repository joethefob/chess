/**
 * Represents a chess board
 *
 * Author: Chun Li, Weichen Zhou
 * Created: Nov 16, 2013.
 */
#ifndef __BOARD_H__
#define __BOARD_H__

#include <iostream>
#include <cstdlib>
#include <vector>

#include "enum.h"
#include "helper.h"

class Piece;
struct Move;
class Xwindow;

class Board {
    //private:
        //unfortunately, there is no way to call a constructor from a constructor in C99
        //this init method reduces repeated code
        //it should never be called outside of the constructor
        Xwindow *xwin;
        Piece *** initial;
        Piece *** current;
        int rows, columns; //dimensions
        static int whiteScore; 
        static int blackScore;
        std::vector<Move *> moves;
        std::vector<Move *> generateMoves(int oldRow, int oldCol); //generate list of legal moves from position
        void init(int rows, int columns);
        bool isProperlySetup();
    public:
        Board(Xwindow *xwin); //create a new standard board
        ~Board(); 
        Board(Xwindow *xwin, int rows, int columns); //creates a new empty board of specified row length and column length
        color_t setup(); //returns whose turn it is to go next
        bool isLegalOnBoard(Move *m, color_t player) const; //check if move is legal WRT current board
        bool inCheck(color_t player); //returns true if player is in check
        bool stalemate(color_t turn); //returns true if the game is a stalemate
        bool checkmate(color_t player); //returns true if player is in checkmate
        bool move(Move *m, color_t player); //applies move
        Piece *** getCurrent();
        std::vector<Move *> getMoves(); //returns the list of moves played
        std::vector<Move *> generateWhiteMoves(); //generate the list of all possible legal moves for white
        std::vector<Move *> generateBlackMoves(); //generate the list of all possible legal moves for black
        //redraw the entire screen
        void draw();
        //redraw a single row/col
        void draw(int row, int col);
        friend std::ostream &operator<<(std::ostream &out, const Board &b);	  
};

#endif /* board.h */
