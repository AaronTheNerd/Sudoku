#include "candidate_box.h"

#include <gtest/gtest.h>

#include "test_utils.h"

TEST(CandidateBoxTest, DoublePairsFullBoard) {
  // clang-format off
  atn::BoardPtr board = atn::generate_board_with_options({
    {{9, {}},        {3, {}},        {4, {}},           {0, {1, 2, 7}}, {6, {}},        {0, {2, 7}},       {0, {1, 7, 8}}, {5, {}},     {0, {1, 8}}},
    {{0, {1, 7}},    {0, {1, 5, 9}}, {6, {}},           {0, {1, 7, 8}}, {0, {5, 7, 8}}, {4, {}},           {9, {}},        {2, {}},     {3, {}}},
    {{0, {1, 2, 7}}, {0, {1, 2, 5}}, {8, {}},           {9, {}},        {0, {3, 5, 7}}, {0, {3, 5, 7}},    {0, {1, 7}},    {4, {}},     {6, {}}},
    {{8, {}},        {0, {1, 2, 9}}, {0, {1, 2, 3, 9}}, {5, {}},        {4, {}},        {6, {}},           {0, {1, 3}},    {0, {1, 9}}, {7, {}}},
    {{6, {}},        {0, {4, 9}},    {0, {3, 7, 9}},    {0, {2, 7, 8}}, {1, {}},        {0, {2, 7, 8}},    {0, {3, 4, 8}}, {0, {8, 9}}, {5, {}}},
    {{5, {}},        {0, {1, 4}},    {0, {1, 7}},       {3, {}},        {9, {}},        {0, {7, 8}},       {0, {1, 4, 8}}, {6, {}},     {2, {}}},
    {{3, {}},        {6, {}},        {0, {5, 9}},       {4, {}},        {0, {5, 8}},    {1, {}},           {2, {}},        {7, {}},     {0, {8, 9}}},
    {{4, {}},        {7, {}},        {0, {2, 9}},       {6, {}},        {0, {2, 3, 8}}, {0, {2, 3, 8, 9}}, {5, {}},        {0, {1, 8}}, {0, {1, 8, 9}}},
    {{0, {1, 2}},    {8, {}},        {0, {1, 2, 5, 9}}, {0, {2, 7}},    {0, {2, 5, 7}}, {0, {2, 5, 7, 9}}, {6, {}},        {3, {}},     {4, {}}}
  });
  // clang-format on
  std::vector<atn::BoardState> before_state{{{3, 8}, {0, {2, 7}}},
                                            {{5, 7}, {0, {2, 3, 8, 9}}},
                                            {{5, 8}, {0, {2, 5, 7, 9}}}};
  std::vector<atn::BoardState> after_state{
      {{3, 8}, {0, {7}}}, {{5, 7}, {0, {3, 8, 9}}}, {{5, 8}, {0, {5, 7, 9}}}};
  atn::CandidateBox move_candidate{board};
  std::optional<atn::NextMove> optional_move = move_candidate.get_next_move();
  EXPECT_TRUE(optional_move.has_value());
  atn::NextMove move = optional_move.value();
  atn::TechniqueEnum technique = move.get_technique();
  EXPECT_EQ(technique, atn::TechniqueEnum::CANDIDATE_BOX);
  atn::CommandPtr command = move.get_command();
  expect_board_state(board, before_state);
  command->apply();
  expect_board_state(board, after_state);
  command->undo();
  expect_board_state(board, before_state);
}

TEST(CandidateBoxTest, MultipleLinesFullBoard) {
  // clang-format off
  atn::BoardPtr board = atn::generate_board_with_options({
    {{0, {2, 4, 5, 7, 8}}, {0, {2, 5, 7}}, {1, {}},        {0, {2, 3, 4, 5, 7}},    {0, {2, 3, 4, 5, 7}}, {0, {2, 3, 4, 5}}, {6, {}},           {9, {}},        {0, {4, 5, 8}}},
    {{0, {2, 4, 5, 8}},    {3, {}},        {0, {2, 4}},    {9, {}},                 {1, {}},              {6, {}},           {0, {2, 4, 5, 8}}, {7, {}},        {0, {4, 5, 8}}},
    {{9, {}},              {6, {}},        {0, {4, 7}},    {0, {4, 5, 7}},          {0, {4, 5, 7}},       {8, {}},           {1, {}},           {2, {}},        {3, {}}},
    {{0, {2, 5, 7}},       {0, {2, 5, 7}}, {8, {}},        {0, {1, 2, 3, 4, 5, 7}}, {0, {2, 3, 4, 5, 7}}, {0, {2, 3, 4, 5}}, {9, {}},           {6, {}},        {0, {1, 5, 7}}},
    {{3, {}},              {1, {}},        {6, {}},        {0, {5, 7}},             {0, {5, 7, 8}},       {9, {}},           {0, {5, 7, 8}},    {4, {}},        {2, {}}},
    {{0, {2, 5, 7}},       {4, {}},        {9, {}},        {0, {1, 2, 5, 6, 7}},    {0, {2, 5, 6, 7, 8}}, {0, {2, 5}},       {3, {}},           {0, {1, 5, 8}}, {0, {1, 5, 7, 8}}},
    {{6, {}},              {0, {2, 7}},    {0, {2, 4, 7}}, {8, {}},                 {0, {2, 4, 5}},       {1, {}},           {0, {4, 5, 7}},    {3, {}},        {9, {}}},
    {{0, {1, 2, 4}},       {8, {}},        {3, {}},        {0, {2, 4, 5, 6}},       {9, {}},              {7, {}},           {0, {4, 5}},       {0, {1, 5}},    {0, {1, 4, 5, 6}}},
    {{0, {1, 4, 7}},       {9, {}},        {5, {}},        {0, {3, 4, 6}},          {0, {3, 4, 6}},       {0, {3, 4}},       {2, {}},           {0, {1, 8}},    {0, {1, 4, 6, 7, 8}}}
  });
  // clang-format on
  std::vector<atn::BoardState> before_state{{{3, 0}, {0, {2, 3, 4, 5, 7}}},
                                            {{4, 0}, {0, {2, 3, 4, 5, 7}}},
                                            {{5, 0}, {0, {2, 3, 4, 5}}}};
  std::vector<atn::BoardState> after_state{{{3, 0}, {0, {2, 3, 4, 7}}},
                                           {{4, 0}, {0, {2, 3, 4, 7}}},
                                           {{5, 0}, {0, {2, 3, 4}}}};
  atn::CandidateBox move_candidate{board};
  std::optional<atn::NextMove> optional_move = move_candidate.get_next_move();
  EXPECT_TRUE(optional_move.has_value());
  atn::NextMove move = optional_move.value();
  atn::TechniqueEnum technique = move.get_technique();
  EXPECT_EQ(technique, atn::TechniqueEnum::CANDIDATE_BOX);
  atn::CommandPtr command = move.get_command();
  expect_board_state(board, before_state);
  command->apply();
  expect_board_state(board, after_state);
  command->undo();
  expect_board_state(board, before_state);
}
