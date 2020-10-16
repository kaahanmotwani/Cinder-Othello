// Copyright (c) 2020 Kaahan Motwani. All rights reserved.

#include <mylibrary/scoreboard.h>

namespace othello {

 Scoreboard::Scoreboard(const std::string& db_path) : db_{db_path} {
    db_ << "CREATE TABLE if not exists scoreboard (\n"
           "  winner  TEXT NOT NULL,\n"
           "  loser  TEXT NOT NULL,\n"
           "  score INTEGER NOT NULL\n"
           ");";
 }

 void Scoreboard::AddWinnerToScoreBoard(const std::string& winner,
     const std::string& loser, const int score) {
   db_ << "insert into scoreboard (winner,loser,score) values (?,?,?);"
     << winner << loser << score;
 }

}  // namespace mylibrary
