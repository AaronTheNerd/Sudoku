// Written by Aaron Barge
// Copyright 2022

#ifndef _INCLUDE_JSON_H_
#define _INCLUDE_JSON_H_

#include <string>  //std::string
#include "sudoku.h"

namespace atn::json {

static const std::unordered_map<atn::DIFFICULTY, std::string>
    difficulty_to_string_map = {{atn::SOLUTION, "Solution"},
        {atn::VERY_EASY, "Very Easy"}, {atn::EASY, "Easy"},
        {atn::MEDIUM, "Medium"}, {atn::HARD, "Hard"}, {atn::KILLER, "Killer"},
        {atn::EVIL, "Evil"}};

template <uint8_t T>
std::string to_json(
    uint32_t, atn::DIFFICULTY, const atn::Sudoku<T>&, const atn::Sudoku<T>&);

template <uint8_t T>
atn::Sudoku<T> from_json(const std::string);

}  // namespace atn::json

#include "../src/json.cpp"

#endif  // _INCLUDE_JSON_H_
