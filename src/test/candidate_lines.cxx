#include "candidate_lines.h"

#include <gtest/gtest.h>

#include "test_utils.h"

using namespace atn::sudoku;
using namespace atn::test_utils;
using namespace atn::generator::logic;

TEST(CandidateLinesTest, FullBoard) {
  // clang-format off
  BoardPtr board = generate_board_with_options({
    {{0, {2, 4, 8}}, {0, {2, 4, 8}}, {1, {}},     {9, {}}, {5, {}},     {7, {}},     {0, {2, 4}},       {6, {}},           {3, {}}},
    {{0, {2, 4, 5}}, {0, {2, 3, 4}}, {0, {3, 5}}, {8, {}}, {0, {2, 4}}, {6, {}},     {0, {1, 2, 4, 9}}, {7, {}},           {0, {1, 2, 4, 9}}},
    {{7, {}},        {6, {}},        {9, {}},     {1, {}}, {3, {}},     {0, {2, 4}}, {8, {}},           {0, {2, 4}},       {5, {}}},
    {{0, {4, 8, 9}}, {0, {4, 8}},    {7, {}},     {2, {}}, {6, {}},     {1, {}},     {3, {}},           {5, {}},           {0, {4, 9}}},
    {{3, {}},        {1, {}},        {2, {}},     {4, {}}, {9, {}},     {5, {}},     {7, {}},           {8, {}},           {6, {}}},
    {{0, {4, 9}},    {5, {}},        {6, {}},     {3, {}}, {7, {}},     {8, {}},     {0, {1, 2, 4, 9}}, {0, {1, 2, 4, 9}}, {0, {1, 2, 4, 9}}},
    {{1, {}},        {0, {2, 3}},    {8, {}},     {6, {}}, {0, {2, 4}}, {9, {}},     {5, {}},           {0, {2, 3, 4}},    {7, {}}},
    {{0, {2, 5}},    {9, {}},        {0, {3, 5}}, {7, {}}, {1, {}},     {0, {2, 4}}, {6, {}},           {0, {2, 3, 4}},    {8, {}}},
    {{6, {}},        {7, {}},        {4, {}},     {5, {}}, {8, {}},     {3, {}},     {0, {1, 2, 9}},    {0, {1, 2, 9}},    {0, {1, 2, 9}}}
  });
  // clang-format on
  std::vector<BoardState> before_state{
      {{7, 7}, {0, {2, 3, 4}}},
      {{7, 6}, {0, {2, 3, 4}}},
      {{7, 5}, {0, {1, 2, 4, 9}}},
      {{7, 2}, {0, {2, 4}}},
  };
  std::vector<BoardState> after_state{
      {{7, 7}, {0, {2, 3, 4}}},
      {{7, 6}, {0, {2, 3, 4}}},
      {{7, 5}, {0, {1, 2, 9}}},
      {{7, 2}, {0, {2}}},
  };
  CandidateLines move_candidate{board};
  std::optional<NextMove> optional_move = move_candidate.get_next_move();
  EXPECT_TRUE(optional_move.has_value());
  NextMove move = optional_move.value();
  TechniqueEnum technique = move.get_technique();
  EXPECT_EQ(technique, TechniqueEnum::CANDIDATE_LINES);
  CommandPtr command = move.get_command();
  expect_board_state(board, before_state);
  command->apply();
  expect_board_state(board, after_state);
  command->undo();
  expect_board_state(board, before_state);
}
