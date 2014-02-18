/**
 * helper.cc
 * helper function implementations
 *
 * Author: Chun Li and Weichen Zhou
 * Created: Nov. 21, 2013.
 */

#include <iostream>
#include <string>

#include "helper.h"
#include "game.h"

using namespace std;

/**
 * Reads in one string (with checks)
 */
string help::getCommand(bool &keepRunning) {
    string command;
    cin >> command;
    if (cin.eof()) {
        keepRunning = false;
        Game::printScore();
    } else if (cin.fail()) {
        cerr << "Input could not be recieved" << endl;
        keepRunning = false;
    }
    return command;
}

/**
 * Checks if the string is a proper rank and file (for standard chess board)
 */
bool help::isCoords(string str) {
    return str.length() == 2 && str[0] >= 'a' && str[0] <= 'h' && str[1] >= '1' && str[1] <= '8';
}

/**
 * Checks if the string is a proper chess piece representation (for standard chess board)
 */
bool help::isPiece(string str) {
    string validPieces = "pnbrqkPNBRQK";
    return str.length() == 1 && validPieces.find(str[0]) != string::npos;
}

void help::deleteVector(vector<Move *> moves) {
    while (!moves.empty()) {
        Move *move = moves[0];
        moves.erase(moves.begin());
        delete move;
    }
}