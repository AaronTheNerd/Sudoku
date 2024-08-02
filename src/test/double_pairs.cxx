#include <gtest/gtest.h>

#include "candidate_lines.h"
#include "test_utils.h"

TEST(DoublePairsTest, FullBoard) {
  // clang-format off
  atn::BoardPtr board = atn::generate_board_with_options({
    {{9, {}},        {3, {}},        {4, {}},           {0, {1, 2, 7}}, {6, {}},        {0, {2, 7}},       {0, {1, 7, 8}}, {5, {}},     {0, {1, 8}}},
    {{0, {1, 7}},    {0, {1, 5}},    {6, {}},           {0, {1, 7, 8}}, {0, {5, 7, 8}}, {4, {}},           {9, {}},        {2, {}},     {3, {}}},
    {{0, {1, 2, 7}}, {0, {1, 2, 5}}, {8, {}},           {9, {}},        {0, {3, 5, 7}}, {0, {3, 5, 7}},    {0, {1, 7}},    {4, {}},     {6, {}}},
    {{8, {}},        {0, {1, 2, 9}}, {0, {1, 2, 3, 9}}, {5, {}},        {4, {}},        {6, {}},           {0, {1, 3}},    {0, {1, 9}}, {7, {}}},
    {{6, {}},        {0, {4, 9}},    {0, {3, 7, 9}},    {0, {2, 7, 8}}, {1, {}},        {0, {2, 7, 8}},    {0, {3, 4, 8}}, {0, {8, 9}}, {5, {}}},
    {{5, {}},        {0, {1, 4}},    {0, {1, 7}},       {3, {}},        {9, {}},        {0, {7, 8}},       {0, {1, 4, 8}}, {6, {}},     {2, {}}},
    {{3, {}},        {6, {}},        {0, {5, 9}},       {4, {}},        {0, {5, 8}},    {1, {}},           {2, {}},        {7, {}},     {0, {8, 0}}},
    {{4, {}},        {7, {}},        {0, {2, 9}},       {6, {}},        {0, {2, 3, 8}}, {0, {2, 3, 8, 9}}, {5, {}},        {0, {1, 8}}, {0, {1, 8, 9}}},
    {{0, {1, 2}},    {8, {}},        {0, {1, 2, 5, 9}}, {0, {2, 7}},    {0, {2, 5, 7}}, {0, {2, 5, 7, 9}}, {6, {}},        {3, {}},     {4, {}}}
  });
  // clang-format on
  std::vector<atn::BoardState> before_state{{{3, 8}, {0, {2, 7}}},
                                       {{5, 7}, {0, {2, 3, 8, 9}}},
                                       {{5, 8}, {0, {2, 5, 7, 9}}}};
  std::vector<atn::BoardState> after_state{
      {{3, 8}, {0, {7}}}, {{5, 7}, {0, {3, 8, 9}}}, {{5, 8}, {0, {5, 7, 9}}}};
  atn::CandidateLines move_candidate{board};
  std::optional<atn::NextMove> optional_move = move_candidate.get_next_move();
  EXPECT_TRUE(optional_move.has_value());
  atn::NextMove move = optional_move.value();
  atn::TechniqueEnum technique = move.get_technique();
  EXPECT_EQ(technique, atn::TechniqueEnum::DOUBLE_PAIRS);
  atn::CommandPtr command = move.get_command();
  expect_board_state(board, before_state);
  command->apply();
  expect_board_state(board, after_state);
  command->undo();
  expect_board_state(board, before_state);
}
