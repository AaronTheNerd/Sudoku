#include <gtest/gtest.h>

#include "single_candidate.h"
#include "test_utils.h"

using namespace atn::sudoku;
using namespace atn::test_utils;
using namespace atn::generator::logic;

TEST(SingleCandidateTest, FullBoard) {
  Board board = generate_board_with_options({
    {{0, {2, 9}},       {4, {}},              {0, {2, 3}},       {0, {7, 8, 9}},       {0, {6, 7, 8, 9}},    {0, {2, 6, 7, 9}},    {0, {3, 9}},          {1, {}},        {5, {}}},
    {{8, {}},           {0, {5, 6, 9}},       {0, {5}},          {3, {}},              {0, {1, 5, 6, 7, 9}}, {0, {1, 4, 6, 7, 9}}, {0, {4, 9}},          {2, {}},        {0, {4, 7, 9}}},
    {{7, {}},           {0, {2, 3, 5, 9}},    {1, {}},           {0, {4, 5, 8, 9}},    {0, {5, 8, 9}},       {0, {2, 4, 9}},       {6, {}},              {0, {4, 8}},    {0, {3, 4, 8, 9}}},
    {{5, {}},           {0, {1, 2, 8, 9}},    {6, {}},           {0, {1, 4, 7, 8, 9}}, {0, {1, 7, 8, 9}},    {0, {1, 4, 7, 9}},    {0, {1, 4}},          {3, {}},        {0, {1, 2, 4}}},
    {{0, {1, 4}},       {0, {1, 3, 8}},       {7, {}},           {2, {}},              {0, {1, 3, 6, 8}},    {0, {1, 4, 6}},       {0, {1, 4, 5}},       {9, {}},        {0, {1, 4, 8}}},
    {{0, {1, 2, 4, 9}}, {0, {1, 2, 3, 8, 9}}, {0, {2, 3, 4, 8}}, {0, {1, 4, 8, 9}},    {0, {1, 3, 6, 8, 9}}, {5, {}},              {7, {}},              {0, {4, 6, 8}}, {0, {1, 2, 4, 8}}},
    {{6, {}},           {0, {1, 2, 5, 7}},    {9, {}},           {0, {1, 5, 7}},       {4, {}},              {3, {}},              {8, {}},              {0, {5, 7}},    {0, {1, 7}}},
    {{0, {1, 4}},       {0, {1, 5, 7, 8}},    {0, {4, 5, 8}},    {6, {}},              {2, {}},              {0, {1, 7, 9}},       {0, {1, 3, 4, 5, 9}}, {0, {4, 5, 7}}, {0, {1, 3, 4, 7, 9}}},
    {{3, {}},           {0, {1, 5, 7}},       {0, {4, 5}},       {0, {1, 5, 7, 9}},    {0, {1, 5, 7, 9}},    {8, {}},              {2, {}},              {0, {4, 5, 7}}, {6, {}}}
  });
  std::vector<BoardState> before_state{
    {{1, 1}, {0, {5, 6, 9}}},
    {{2, 1}, {0, {5}}},
    {{1, 2}, {0, {2, 3, 5, 9}}},
    {{4, 1}, {0, {1, 5, 6, 7, 9}}},
    {{2, 7}, {0, {4, 5, 8}}},
    {{2, 8}, {0, {4, 5}}}
  };
  std::vector<BoardState> after_state{
    {{1, 1}, {0, {6, 9}}},
    {{2, 1}, {5, {}}},
    {{1, 2}, {0, {2, 3, 9}}},
    {{4, 1}, {0, {1, 6, 7, 9}}},
    {{2, 7}, {0, {4, 8}}},
    {{2, 8}, {0, {4}}}
  };
  SingleCandidate move_candidate{board};
  std::optional<NextMove> optional_move = move_candidate.get_next_move();
  EXPECT_TRUE(optional_move.has_value());
  NextMove move = optional_move.value();
  CommandPtr command = move.get_command();
  expect_board_state(board, before_state);
  command->apply();
  expect_board_state(board, after_state);
  command->undo();
  expect_board_state(board, before_state);
}
