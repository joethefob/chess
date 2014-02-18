/**
 * move.cc
 * Implementation of move class.
 *
 * Author: Chun Li, Weichen Zhou
 * Created: Nov 16, 2013.
 */

#include "move.h"
using namespace std;

Move::Move(int oldRow, int oldCol, int newRow, int newCol) {
    oldRank = 8 - oldRow;
    oldFile = 'a' + oldCol;
    newRank = 8 - newRow;
    newFile = 'a' + newCol;
}

Move::Move(char oldFile, int oldRank, char newFile, int newRank) :
    oldFile(oldFile), oldRank(oldRank), newFile(newFile), newRank(newRank) {}

int Move::getOldRow() {
    return 8 - oldRank;
}

int Move::getOldCol() {
    return oldFile - 'a';
}

int Move::getNewRow() {
    return 8 - newRank;
}

int Move::getNewCol() {
    return newFile - 'a';
}

void Move::print() {
	cout << oldFile << oldRank << " " << newFile << newRank << endl;
}
