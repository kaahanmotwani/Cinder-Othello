// Copyright (c) 2020 Kaahan Motwani. All rights reserved.
#ifndef FINALPROJECT_MYLIBRARY_EXAMPLE_H_
#define FINALPROJECT_MYLIBRARY_EXAMPLE_H_

#include <sqlite_modern_cpp.h>

namespace othello {

class Scoreboard {
 public:
  // Creates a new leaderboard table if it doesn't already exist.
  explicit Scoreboard(const std::string& db_path);
  // Adds the winner, their score, and the loser to the leaderboard.
  void AddWinnerToScoreBoard(const std::string& winner,
      const std::string& loser, int score);

 private:
  sqlite::database db_;
};

}  // namespace mylibrary


#endif // FINALPROJECT_MYLIBRARY_EXAMPLE_H_
