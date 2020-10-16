//
// Created by Kaahan Motwani on 4/28/20.
//

#ifndef FINALPROJECT_LOGIC_H
#define FINALPROJECT_LOGIC_H

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <vector>

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::pair;

namespace logic {

// These vectors represent the 8 directions on the Othello board in
// which a piece can move; used to show valid moves to the players
const vector<int> kXChange{-1, 0, 1, -1, 1, -1, 0, 1};
const vector<int> kYChange{-1, -1, -1, 0, 0, 1, 1, 1};
const int kBoardSize = 8; // The size of the board (8x8)

/**
 * This method flipped the appropriate pieces if the user committed a valid
 * move and returned the game board with the updates pieces. This method was
 * used for the regular game board and for the hovering over capability.
 *
 * @param x_tile_coordinate_ the x-coordinate of the move the player committed
 * @param y_tile_coordinate_ the y-coordinate of the move the player committed
 * @param is_white_turn_ the boolean indicating if it's a white turn or not
 * @param game_board_ the current state of the game board
 * @return the game board, with all the appropriate pieces flipped
 */
vector<vector<string>> FlipPieces(int& x_tile_coordinate_,
                                  int& y_tile_coordinate_, bool is_white_turn_,
                                  vector<vector<string>> game_board_);

/**
 * This method checks if a given move is in the bounds of the board (positions
 * 0 through 7) on the x and y. It is used several times as a utility method.
 *
 * @param x the x coordinate of the move
 * @param y the y coordinate of the move
 * @return whether the move is in bounds (true) or not (false)
 */
bool InBounds(int x, int y);

/**
 * This method  loops through all directions to ensure that the move the
 * user is playing is valid. The reason this method is separate from FlipPieces
 * is because they will be called consecutively and the pieces cannot be flipped
 * if the move is not valid.
 *
 * @param x_tile_coordinate_ The x-coordinate of the user's move
 * @param y_tile_coordinate_ The y-coordinate of the user's move
 * @param is_white_turn_
 * @param game_board_
 * @return
 */
bool IsMoveValid(int& x_tile_coordinate_, int& y_tile_coordinate_,
    bool is_white_turn_, vector<vector<string>>& game_board_);

/**
 * This method obtains a vector of pairs of integers that represent the valid
 * moves at any given point in the game by looping through the  8x8
 * board and checking for validity.
 *
 * @param game_board_ the current state of the game board
 * @param is_white_turn_ whether it is white's turn or not
 * @return A vector of pairs of integers that are x,y coordinates of valid moves
 */
vector<pair<int, int>> GetValidMoves(vector<vector<string>>& game_board_,
                                     bool is_white_turn_);

}

#endif  // FINALPROJECT_LOGIC_H
