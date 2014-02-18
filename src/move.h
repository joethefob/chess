#ifndef __MOVE_H__
#define __MOVE_H__

/**
 * move.h
 * Class that represents a chess move
 *
 * Author: Chun Li, Weichen Zhou
 * Created: Nov 16, 2013.
 */
#include <iostream>

struct Move {
    // old and new positions
    // note that none of the values are guarenteed to be consistent with the 
    // current state of p
    // File accepts [a, h]
    // Rank accepts [1, 8]
    char oldFile;
    int oldRank;
    char newFile;
    int newRank;
    Move(char oldFile, int oldRank, char newFile, int newRank);
    //constructor that uses row, col format for convience.
    Move(int oldRow, int oldCol, int newRow, int newCol);
    // getters for convience to get row and col [0-7], [0-7]
    // assuming a standard chess board.
    int getOldRow();
    int getOldCol();
    int getNewRow();
    int getNewCol();
    void print();
};

#endif /* move.h */
