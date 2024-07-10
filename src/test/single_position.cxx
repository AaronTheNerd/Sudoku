#include "single_position.h"

#include <gtest/gtest.h>

#include "test_utils.h"

using namespace atn::sudoku;
using namespace atn::test_utils;
using namespace atn::generator::logic;

TEST(SinglePositionTest, FullBoardColumn) {
  // clang-format off
  BoardPtr board = generate_board_with_options({
    {{4, {}},        {0, {1, 2, 5, 9}},    {6, {}},        {0, {1, 2, 9}},       {0, {1, 5, 9}},       {0, {2, 5, 7, 9}},       {0, {2, 7, 8}},          {3, {}},              {0, {2, 5, 7, 8}}},
    {{0, {2, 5}},    {0, {1, 2, 3, 5, 9}}, {8, {}},        {0, {1, 2, 3, 6, 9}}, {0, {1, 3, 5, 6, 9}}, {0, {2, 3, 5, 6, 7, 9}}, {0, {2, 7}},             {4, {}},              {0, {2, 5, 7}}},
    {{7, {}},        {0, {2, 3, 5}},       {0, {2, 3, 5}}, {0, {2, 3, 8}},       {0, {3, 5, 8}},       {4, {}},                 {1, {}},                 {9, {}},              {6, {}}},
    {{1, {}},        {8, {}},              {0, {2, 5}},    {7, {}},              {0, {3, 5, 6, 9}},    {0, {3, 5, 6, 9}},       {4, {}},                 {0, {2, 6}},          {0, {2, 3, 9}}},
    {{9, {}},        {6, {}},              {0, {2, 5}},    {4, {}},              {0, {1, 3, 5, 8}},    {0, {3, 5, 8}},          {0, {2, 3, 7, 8}},       {0, {1, 2, 7, 8}},    {0, {1, 2, 3, 7, 8}}},
    {{3, {}},        {7, {}},              {4, {}},        {0, {1, 6, 8, 9}},    {2, {}},              {0, {6, 8, 9}},          {5, {}},                 {0, {1, 6, 8}},       {0, {1, 8, 9}}},
    {{0, {2, 5, 8}}, {0, {2, 3, 5}},       {1, {}},        {0, {2, 3, 6, 8, 9}}, {7, {}},              {0, {2, 3, 6, 8, 9}},    {0, {2, 3, 6, 7, 8, 9}}, {0, {2, 5, 6, 7, 8}}, {4, {}}},
    {{6, {}},        {4, {}},              {0, {3, 9}},    {0, {2, 3, 8, 9}},    {0, {3, 8, 9}},       {1, {}},                 {0, {2, 3, 7, 8, 9}},    {0, {2, 5, 7, 8}},    {0, {2, 3, 5, 7, 8, 9}}},
    {{0, {2, 8}},    {0, {2, 3}},          {7, {}},        {5, {}},              {4, {}},              {0, {2, 3, 6, 8, 9}},    {0, {2, 3, 6, 8, 9}},    {0, {1, 2, 6, 8}},    {0, {1, 2, 3, 8, 9}}},
  });
  // clang-format on
  std::vector<BoardState> before_state{{{2, 7}, {0, {3, 9}}},
                                       {{3, 7}, {0, {2, 3, 8, 9}}},
                                       {{4, 7}, {0, {3, 8, 9}}},
                                       {{6, 7}, {0, {2, 3, 7, 8, 9}}},
                                       {{8, 7}, {0, {2, 3, 5, 7, 8, 9}}}};
  std::vector<BoardState> after_state{{{2, 7}, {9, {}}},
                                      {{3, 7}, {0, {2, 3, 8}}},
                                      {{4, 7}, {0, {3, 8}}},
                                      {{6, 7}, {0, {2, 3, 7, 8}}},
                                      {{8, 7}, {0, {2, 3, 5, 7, 8}}}};
  SinglePosition move_candidate{board};
  std::optional<NextMove> optional_move = move_candidate.get_next_move();
  EXPECT_TRUE(optional_move.has_value());
  NextMove move = optional_move.value();
  TechniqueEnum technique = move.get_technique();
  EXPECT_EQ(technique, TechniqueEnum::SINGLE_POSITION);
  CommandPtr command = move.get_command();
  expect_board_state(board, before_state);
  command->apply();
  expect_board_state(board, after_state);
  command->undo();
  expect_board_state(board, before_state);
}

TEST(SinglePositionTest, FullBoardRow) {
  // clang-format off
  BoardPtr board = generate_board_with_options({
    {{0, {2, 8}},          {6, {}},                 {0, {2, 5, 8}},          {3, {}},           {9, {}},              {1, {}},           {7, {}},        {0, {2, 5}},             {4, {}}},
    {{0, {2, 3}},          {4, {}},                 {0, {2, 3, 5}},          {7, {}},           {6, {}},              {8, {}},           {0, {2, 3, 5}}, {0, {1, 2, 3, 5, 9}},    {0, {1, 2, 5, 9}}},
    {{7, {}},              {0, {3, 9}},             {1, {}},                 {4, {}},           {0, {2, 5}},          {0, {2, 5}},       {0, {2, 3, 5}}, {8, {}},                 {6, {}}},
    {{5, {}},              {0, {2, 3, 8, 9}},       {0, {2, 3, 6, 8, 9}},    {0, {1, 6, 8, 9}}, {4, {}},              {7, {}},           {0, {2, 3, 8}}, {0, {1, 2, 3, 6, 9}},    {0, {1, 2, 9}}},
    {{4, {}},              {0, {3, 8, 9}},          {7, {}},                 {2, {}},           {0, {1, 3, 5, 8}},    {0, {3, 5, 6, 9}}, {0, {3, 5, 8}}, {0, {1, 3, 5, 6, 9}},    {0, {1, 5, 9}}},
    {{0, {2, 3, 6, 8, 9}}, {1, {}},                 {0, {2, 3, 6, 8, 9}},    {0, {6, 8, 9}},    {0, {3, 5, 8}},       {0, {3, 5, 6, 9}}, {4, {}},        {0, {2, 3, 5, 6, 7, 9}}, {0, {2, 5, 7, 9}}},
    {{0, {2, 3, 6, 8, 9}}, {0, {2, 3, 7, 8, 9}},    {0, {2, 3, 6, 7, 8, 9}}, {5, {}},           {0, {2, 3, 7, 8}},    {4, {}},           {1, {}},        {0, {2, 7}},             {0, {2, 7, 8}}},
    {{0, {1, 2, 6, 8}},    {0, {2, 5, 7, 8}},       {0, {2, 5, 6, 7, 8}},    {0, {1, 6, 8}},    {0, {1, 2, 7, 8}},    {0, {2, 6}},       {9, {}},        {4, {}},                 {3, {}}},
    {{0, {1, 2, 3, 8, 9}}, {0, {2, 3, 5, 7, 8, 9}}, {4, {}},                 {0, {1, 8, 9}},    {0, {1, 2, 3, 7, 8}}, {0, {2, 3, 9}},    {6, {}},        {0, {2, 5, 7}},          {0, {2, 5, 7, 8}}}
  });
  // clang-format on
  std::vector<BoardState> before_state{{{1, 2}, {0, {3, 9}}},
                                       {{1, 3}, {0, {2, 3, 8, 9}}},
                                       {{1, 4}, {0, {3, 8, 9}}},
                                       {{1, 6}, {0, {2, 3, 7, 8, 9}}},
                                       {{1, 8}, {0, {2, 3, 5, 7, 8, 9}}}};
  std::vector<BoardState> after_state{{{1, 2}, {9, {}}},
                                      {{1, 3}, {0, {2, 3, 8}}},
                                      {{1, 4}, {0, {3, 8}}},
                                      {{1, 6}, {0, {2, 3, 7, 8}}},
                                      {{1, 8}, {0, {2, 3, 5, 7, 8}}}};
  SinglePosition move_candidate{board};
  std::optional<NextMove> optional_move = move_candidate.get_next_move();
  EXPECT_TRUE(optional_move.has_value());
  NextMove move = optional_move.value();
  TechniqueEnum technique = move.get_technique();
  EXPECT_EQ(technique, TechniqueEnum::SINGLE_POSITION);
  CommandPtr command = move.get_command();
  expect_board_state(board, before_state);
  command->apply();
  expect_board_state(board, after_state);
  command->undo();
  expect_board_state(board, before_state);
}
