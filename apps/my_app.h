// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/Color.h>
#include <cinder/app/App.h>
#include <cinder/gl/Texture.h>
#include <mylibrary/scoreboard.h>
#include <cinder/audio/Voice.h>
#include <string>
#include <cinder/app/App.h>
#include <sqlite_modern_cpp.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include <mylibrary/logic.h>

using std::vector;
using std::string;
using std::pair;
using std::cout;
using std::endl;
using cinder::Color;
using cinder::ColorA;
using cinder::Rectf;
using cinder::TextBox;
using std::string;
using std::to_string;
using cinder::app::KeyEvent;
using std::chrono::duration_cast;
using std::chrono::seconds;
using std::chrono::system_clock;
using namespace ci;
using namespace ci::app;

namespace myapp {

class MyApp : public cinder::app::App {

 public:

  /**
   * The constructor for the MyApp class that initializes the sqlite database.
   */
  MyApp();

  /**
   * Sets up the initial game board and sets the images for the board and reset
   * button.
   */
  void setup() override;

  /**
   * Cinder's update only used to repeat the music.
   */
  void update() override;

  /**
   * The method that is called several times every seconds and is responsible
   * for drawing on the screen.
   */
  void draw() override;

  /**
   * This method has several uses. The first is for when the user is playing a
   * move. This method reads where the user has clicked, and then verifies that
   * it is a valid move by calling on other methods. Then, it changes the state
   * of the game board at that coordinate to be "black" or "white". Another
   * use is to check if the reset button was clicked. Lastly, it checks if the
   * game is over because this is the method where the board state changes.
   */
  void mouseDown(cinder::app::MouseEvent) override;

  /**
   * This method is used for the hover over functionality that allows users to
   * see what the outcome of a potential move will be by detecting when the
   * mouse moves.
   */
  void mouseMove(cinder::app::MouseEvent) override;

 private:

  /**
   * This method is called by Cinder's draw method and draws the state of the
   * board and the hover-over board (potential board) each time. This happens
   * by looping through the 2d board vector and checking if there are white
   * and black pieces at that x,y coordinate.
   */
  void DrawBoard();

  /**
   * This method loops through the board state to count up the scores for the
   * black and white players.
   */
  void UpdateScores();

  /**
   * This method checks if the game is over (if the total score is 64, which
   * means every square on the board is filled).
   *
   * @return whether the game is over (true) or not (false)
   */
  bool IsGameOver();

  /**
   * This method is responsible for drawing the scores and text in the right
   * hand panel. The method is called by draw, and is thus being constantly
   * being drawn.
   */
  void DrawScoresAndText();

  /**
   * This method gets the winner by comparing the black and white scores when
   * the game is over.
   *
   * @return "black" if black won, "white" if white won, and "tie" if they tied
   */
  string GetWinner();

  /**
   * This method is used to play any sound during the game, depending on the
   * parameter.
   *
   * @param voice the string that is used to represent each of the sounds
   */
  static void PlaySound(const string& voice);

  /**
   * This method resets the game by clearing the game board and resetting it
   * to the initial state of an Othello game.
   */
  void ResetGame();

  /**
   * This method sets the initial game board as all empty strings in the 2d
   * vector of string, except the middle four pieces that are constant in
   * Othello games.
   */
  void SetInitialGameBoard();

  /**
   * This method ends the game by adding the winner to the sql leaderboard, as
   * well as the winning player's score.
   */
  void EndGameAndAddToLeaderboard();

 private:
  othello::Scoreboard leaderboard_;
  cinder::gl::Texture2dRef background_;
  cinder::gl::Texture2dRef reset_;
  vector<vector<string>> game_board_;
  vector<pair<int, int>> valid_moves_;
  // Potential game board acts as the game board if the user was to play a
  // move. They are able to see what happens when they hover over a valid move.
  vector<vector<string>> potential_game_board_;
  bool is_white_turn_ = false;
  int black_score_ = 2;
  int white_score_ = 2;
  const int kBoardSize = 8;
  const int kBoardBounds = getWindowBounds().getHeight();
  const int kTileLength = getWindowBounds().getHeight() / kBoardSize;
  const int kTileCenter = kTileLength / 2;
  const int kCirclePieceRadius = 35;
  // The rgb values to get a green color matching the color of the game board
  const float kBoardRed = 46.0 / 255.0;
  const float kBoardGreen = 174.0 / 255.0;
  const float kBoardBlue = 82.0 / 255.0;
  const int kFirstStartCoord = 3;
  const int kSecondStartCoord = 4;
  // These vectors represent the 8 directions on the Othello board in
  // which a piece can move; used to show valid moves to the players
  const vector<int> kXChange{-1, 0, 1, -1, 1, -1, 0, 1};
  const vector<int> kYChange{-1, -1, -1, 0, 0, 1, 1, 1};
  const int kPanelCenterX = 860; // The center x-coord of the game's panel
  // The following four constants represent the y coordinates of places where
  // messages are printed in the panel for the user
  const int kTurnY = 100;
  const int kWhiteScoreY = 200;
  const int kBlackScoreY = 300;
  const int kGameOverY = 400;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
