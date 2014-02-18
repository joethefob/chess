/**
 * game.h
 * Interface for a single game of chess
 *
 * Author: Chun Li, Weichen Zhou
 * Created: Nov 16, 2013.
 */
#ifndef __GAME_H__
#define __GAME_H__

#include "enum.h"

class Board;
class Xwindow;
struct Move;

class Game {
    //private:
        Board *b;
        //game has three states: setup -> playing -> finished
        game_state_t state;
        color_t turn; //who's current turn it is
        int level;
        static int whiteScore;
        static int blackScore;
    public:
        Game(Xwindow *xwin);
        Game(Xwindow *xwin, int rows, int columns);
        ~Game();
        game_state_t getState() const;
        color_t getTurn() const;
        void start(std::string white_player, std::string black_player);
        static void printScore(); //returns score
        void setup(Xwindow *xwin);
        int move(Move *m);
        void resign();
        friend std::ostream &operator<<(std::ostream &out, const Game &g);
};

#endif /* game.h */
