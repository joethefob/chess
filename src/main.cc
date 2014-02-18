/**
 * ASSIGNMENT 5, CS 246
 *
 * main.cc
 * Main runtime loop of chess game
 *
 * Author: Chun Li, Weichen Zhou
 * Created: Nov. 16, 2013.
 */

#include <iostream>
#include <string>

#include "game.h"
#include "helper.h"
#include "move.h"
#include "window.h"

using namespace std;

/**
 * Prints a help message with all the commands
 */
void printHelp() {
    cout << "Avaliable commands: " << endl << endl;
    cout << "game white-player black-player" << endl;
    cout << "This starts a new game. The parameters white-player and black-player can be either human or computer[1-4]" << endl << endl;
    cout << "resign" << endl;
    cout << "Concedes the game to your opponent. This is the only way, outside of winning or drawing the game, to end a game." << endl << endl;
    cout << "move coords coords" << endl;
    cout << "A move consists of the command move, followed by the starting and ending coordinates of the piece to be moved. For example: move e2 e4. Castling would specified by the two- square move for the king: move e1 g1 or move e1 c1 for white. Pawn promotion would additionally specify the piece type to which the pawn is promoted: move e7 e8 Q. In the case of a computer player, the command move (without arguments) makes the computer player make a move." << endl << endl;
    cout << "setup" << endl;
    cout << "setup enters setup mode, within which you can set up your own initial board configurations. This can only be done when a game is not currently running." << endl << endl;
}

int main() {
    Xwindow *xwin = new Xwindow(); //create new GUI
    //don't delete this until main is done!
    Game *game = new Game(xwin); //current chess game is neither started or finished
    string command; //current command
    bool keepRunning = true; //false when program terminates
    
    command = help::getCommand(keepRunning);
    while (keepRunning) {
        if (command == "game") { //starts a game (doesn't work if already playing a game)
            if (game->getState() == playing) { //if we're currently playing
                cout << "The game's already started!" << endl;
            } else {
                if (game->getState() == finished) { //in the case the previous game has finished
                    delete game; //erase it
                    game = new Game(xwin); //new default game
                }
                string white_player, black_player;
                cin >> white_player >> black_player;
                game->start(white_player, black_player); //starts a new game
            }
        } else if (command == "resign") { //if we're playing a game, resigns
            if (!game->getState() == playing) { //if we're not playing a game (i.e. setting up or done)
                cout << "We aren't currently playing a game." << endl;
            } else {
                game->resign();
            }
        } else if (command == "move") { //if we're playing a game, makes a move
            if (!game->getState() == playing) { //if we're not playing a game
                cout << "We aren't currently playing a game." << endl;
            } else {
                string coord1 = help::getCommand(keepRunning);
                string coord2 = help::getCommand(keepRunning);
                if (!help::isCoords(coord1)) {
                    cout << "ERROR processing rank and file. ";
                    cout << coord1 << " is not a coordinate on the chess board." << endl;
                } else if (!help::isCoords(coord2)) {
                    cout << "ERROR processing rank and file. ";
                    cout << coord2 << " is not a coordinate on the chess board." << endl;
                } else {
                    Move *m = new Move(coord1[0], coord1[1] - '0', coord2[0], coord2[1] - '0');
                    game->move(m);
                }
            }
        } else if (command == "setup") { //if we're not playing, sets up the board
            if (game->getState() == playing) { //if we're currently playing
                cout << "The game's already started!" << endl;
            } else {
                if (game->getState() == finished) { //if it's finished
                    //delete it
                    delete game;
                    game = new Game(xwin, 8, 8); //empty 8x8 chess board
                }
                game->setup(xwin);
            }
        } else if (command == "print") {
            //prints out the current board setup, 
            //or the last configuration of the last board
            cout << *game << endl;
        } else if (command == "help") {
            printHelp();
        } else {
            cout << "Sorry, the command " << command << " is not recognized" << endl;
        }

        command = help::getCommand(keepRunning);
    }

    delete xwin;
    delete game;
    return 0;
}
