// Written by Aaron Barge
// Copyright 2022

#define GAME_SIZE 3

#include <chrono>                // std::chrono
#include <fstream>               // std::ofstream
#include <iostream>              // std::cout, std::endl
#include "json.h"                // atn::json
#include "sudoku_game.h"         // atn::SudokuGame

int main(int argc, char** argv) {
  atn::SudokuGame<3> game(atn::VERY_EASY);
  std::cout << game.to_str() << std::endl;
  
  std::ofstream outfile;
  outfile.open("puzzle.json", std::ios::out | std::ios::trunc);
  outfile << atn::json::to_json(game);
  outfile.close();

  return 0;
}
