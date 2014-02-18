#ifndef __HELPER_H__
#define __HELPER_H__

/**
 * helper.h
 * defines some useful general helper functions, minimizing code repetition
 *
 * Author: Chun Li and Weichen Zhou
 * Created: Nov. 21, 2013.
 */
#include <string>
#include <vector>

#include "move.h"

namespace help { //this is for people to know where the function came from
    std::string getCommand(bool &keepRunning);
    bool isCoords(std::string str);
    bool isPiece(std::string str);
    void deleteVector(std::vector<Move*> moves);
}

#endif /* helper.h */
