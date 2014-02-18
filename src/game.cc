/**
 * game.cc
 * Interface for a single game of chess
 *
 * Author: Chun Li, Weichen Zhou
 * Created: Nov 17, 2013.
 */

#include <iostream>
#include <string>

#include "game.h"
#include "board.h"
#include "window.h"
#include "enum.h"
#include "helper.h"

using namespace std;

int Game::whiteScore = 0;
int Game::blackScore = 0;

Game::Game(Xwindow *xwin) {
    b = new Board(xwin); //creates a new standard board
    state = settingup;
    level = 1; //level one just for now (no AI implementation)
    turn = white;
}

Game::Game(Xwindow *xwin, int rows, int columns) {
    b = new Board(xwin, rows, columns);
    state = settingup;
    level = 1;
    turn = white;
}

Game::~Game() {
    delete b;
}

game_state_t Game::getState() const {
    return state;
}

color_t Game::getTurn() const {
    return turn;
}

void Game::resign() {
    state = finished;
    if (turn == white) {
        cout << "White has resigned. Black won!";
        ++blackScore;
    } else {
        cout << "Black has resigned. White won!";
        ++whiteScore;
    }
}

void Game::start(string white_player, string black_player) {
    if (state == playing) { //if we're already playing there's a problem.
        cerr << "ERROR: cannot start a game that's already started." << endl;
    }
    //TODO
    //implement feature
    state = playing;
}

void Game::setup(Xwindow *xwin) {
    delete b;
    b = new Board(xwin, 8, 8);
    turn = b->setup();
}

int Game::move(Move *m) {
    bool success = b->move(m, turn);
    color_t opponent;
    if (turn == white) {
        opponent = black;
    } else {
        opponent = white;
    }

    if (success) {
        if (b->checkmate(opponent)) {
            state = finished;
        } else if (b->stalemate(opponent)) {
            state = finished;
        }
        else {
            if (turn == white) {
                turn = black;
            } else {
                turn = white;
            }
        }
    } else {
        cout << "Error moving piece." << endl;
    }
    cout << *this;
    return 0;
}

void Game::printScore() {
    cout << "Final Score: " << endl;
    cout << "White: " << whiteScore << endl;
    cout << "Black: " << blackScore << endl;
}

ostream &operator<<(ostream &out, const Game &g) {
    out << *(g.b);
    if (g.getState() == playing) {
        if (g.b->inCheck(white)) {
            cout << "White is in check." << endl;
        } else if (g.b->inCheck(black)) {
            cout << "Black is in check." << endl;
        }
    } else if (g.getState() == finished) {
        if (g.b->checkmate(white)) {
            cout << "Checkmate! White wins!" << endl;
        } else if (g.b->checkmate(black)) {
            cout << "Checkmate! Black wins!" << endl;
        } else if (g.b->stalemate(g.getTurn())) {
            cout << "Stalemate!" << endl;
        }
    }
    return out;
}
