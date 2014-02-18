#ifndef __ENUM_H__
#define __ENUM_H__

/**
 * enum.h
 * Defines enumerations used
 *
 * Author: Chun Li and Weichen Zhou
 * Created: Nov. 20, 2013.
 */
// for the game class, different states the game can be in.
enum game_state_t { settingup, playing, finished };
// the different coloured players
enum color_t { white, black };
// the different pieces, for the piece class
enum piece_t { pawn, knight, bishop, rook, queen, king };
#endif /* enum.h */
