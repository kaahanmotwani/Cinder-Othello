// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <mylibrary/logic.h>

using std::vector;
using std::pair;
using std::map;
using std::string;
using std::make_pair;

const int kBoardSize = 8;
const bool is_white_turn = false;

/**
 * This method is used in order to avoid having to repeat code for filling in
 * the game board. It first fills the board with all empty strings, then uses
 * the map to fill in spots with "black" or "white", indicated by the coords.
 *
 * @param coord_to_color_map This is a map of a pair of integers (representing
 * coordinates) to strings of the color at that coordinate
 * @return a filled game board using the map that was passed in
 */
vector<vector<string>> FillGameBoard(const map<pair<int, int>, string>&
    coord_to_color_map) {
  vector<vector<string>> game_board;
  vector<string> v(kBoardSize, "");
  // Fills the game board with all empty strings initially
  for (size_t i = 0; i < kBoardSize; i++) {
    game_board.push_back(v);
  }
  for (const auto& coord_to_color : coord_to_color_map) {
    game_board[coord_to_color.first.first][coord_to_color.first.second]
      = coord_to_color.second;
  }

  return game_board;
}

/** This method takes a given game board and fills every spot with black or
 * white to represent a full game board. Used for testing edge cases with a full
 * board.
 *
 * @param game_board the state of the game board
 * @return a completely filled (with "black" and "white" pieces) game board
 */
vector<vector<string>> GetFullBoard(vector<vector<string>>& game_board) {
  // Fills the entire game board with black or white
  for (size_t i = 0; i < kBoardSize; i++) {
    for (size_t j = 0; j < kBoardSize; j++) {
      if (i % 2 == 0) {
        game_board[j][i] = "white";
      } else {
        game_board[j][i] = "black";
      }
    }
  }
  return game_board;
}

TEST_CASE("Valid moves can be found", "[valid-moves]") {
  map<pair<int, int>, string> coord_to_color_map
      = {{make_pair(3, 3), "white"},
         {make_pair(3, 4), "black"},
         {make_pair(4, 3), "black"},
         {make_pair(4, 4), "white"}};
  vector<vector<string>> game_board = FillGameBoard(coord_to_color_map);
  // The vector of pairs of ints represents the expected valid move coordinates
  vector<pair<int, int>> valid_move_coords = {{2, 3}, {3, 2},
                                              {4, 5}, {5, 4}};

  SECTION("Find valid moves on a normal board") {
    REQUIRE(logic::GetValidMoves(game_board, false) == valid_move_coords);
  }

  SECTION("Find valid moves on a full board") {
    game_board = GetFullBoard(game_board);
    valid_move_coords.clear();

    // In a full board, there should be no valid moves, which is why
    // valid_move_coords was cleared
    REQUIRE(logic::GetValidMoves(game_board, false) == valid_move_coords);
  }
}

TEST_CASE("Pieces on the game board can be flipped", "[flip-pieces]") {
  map<pair<int, int>, string> coord_to_color_map
    = {{make_pair(3, 2), "black"},
     {make_pair(3, 3), "black"},
     {make_pair(3, 4), "black"},
     {make_pair(4, 3), "black"},
     {make_pair(4, 4), "white"},
     {make_pair(2, 2), "white"}};
  vector<vector<string>> game_board = FillGameBoard(coord_to_color_map);
  int x_move = 2;
  int y_move = 2;

  SECTION("Flip pieces on a normal board") {
    // {3, 3} should flip to white if the last move was {2, 2}
    coord_to_color_map[{3, 3}] = "white";
    vector<vector<string>> expected_game_board
      = FillGameBoard(coord_to_color_map);

    REQUIRE(logic::FlipPieces(x_move, y_move, true, game_board)
            == expected_game_board);
  }

  SECTION("Flip pieces with an invalid move") {
    x_move = 7;

    REQUIRE(logic::FlipPieces(x_move, y_move, true, game_board)
            == game_board);
  }

  SECTION("Flip pieces on a completely full board") {
    game_board = GetFullBoard(game_board);

    // If the board is full, no pieces should be flipped, regardless of the move
    REQUIRE(logic::FlipPieces(x_move, y_move, is_white_turn, game_board)
            == game_board);
  }
}

TEST_CASE("Checks If Moves Are Valid", "[is-move-valid]") {
  map<pair<int, int>, string> coord_to_color_map
      = {{make_pair(3, 3), "white"},
         {make_pair(3, 4), "black"},
         {make_pair(4, 3), "black"},
         {make_pair(4, 4), "white"}};

  vector<vector<string>> game_board = FillGameBoard(coord_to_color_map);
  int x_move = 2;
  int y_move = 3;

  SECTION("Test for a Valid Move") {
    REQUIRE(logic::IsMoveValid(x_move, y_move, is_white_turn, game_board));
  }

  SECTION("Test for an Invalid Move") {
    y_move = 2;

    REQUIRE(!logic::IsMoveValid(x_move, y_move, is_white_turn, game_board));
  }

  SECTION("Test for when the board is completely full") {
    game_board = GetFullBoard(game_board);

    REQUIRE(!logic::IsMoveValid(x_move, y_move, is_white_turn, game_board));
  }
}

TEST_CASE("Checks if Coordinates Are In Bounds", "[in-bounds]") {
  int x_coord = 0;
  int y_coord = 0;

  SECTION("In Bounds Coordinates") {
    // Checks for in-bounds coordinates (x or y less than or equal to 7)
    REQUIRE(logic::InBounds(x_coord, y_coord));
  }

  SECTION("Out of Bounds Coordinates") {
    y_coord = 10;

    // Checks for out-of-bounds coordinates (x or y greater than 7)
    REQUIRE(!logic::InBounds(x_coord, y_coord));
  }
}