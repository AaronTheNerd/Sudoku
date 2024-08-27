#include "line_box_view.h"

#include <gtest/gtest.h>

#include "test_utils.h"

struct CountTestCase {
  atn::Value value;
  atn::Line line;
  atn::Index index;
  uint8_t expected;
};

struct BitsetTestCase {
  atn::Value value;
  atn::Line line;
  atn::Index index;
  std::bitset<3> expected;
};

TEST(LineBoxViewTest, Constructor) {
  EXPECT_NO_THROW(atn::LineBoxView{atn::Board::create()});
}

TEST(LineBoxViewTest, CountTest) {
  // clang-format off
  atn::BoardPtr board = atn::generate_board_with_options({
    {{9, {}},        {3, {}},        {4, {}},           {0, {1, 2, 7}}, {6, {}},        {0, {2, 7}},       {0, {1, 7, 8}}, {5, {}},     {0, {1, 8}}},
    {{0, {1, 7}},    {0, {1, 5}},    {6, {}},           {0, {1, 7, 8}}, {0, {5, 7, 8}}, {4, {}},           {9, {}},        {2, {}},     {3, {}}},
    {{0, {1, 2, 7}}, {0, {1, 2, 5}}, {8, {}},           {9, {}},        {0, {3, 5, 7}}, {0, {3, 5, 7}},    {0, {1, 7}},    {4, {}},     {6, {}}},
    {{8, {}},        {0, {1, 2, 9}}, {0, {1, 2, 3, 9}}, {5, {}},        {4, {}},        {6, {}},           {0, {1, 3}},    {0, {1, 9}}, {7, {}}},
    {{6, {}},        {0, {4, 9}},    {0, {3, 7, 9}},    {0, {2, 7, 8}}, {1, {}},        {0, {2, 7, 8}},    {0, {3, 4, 8}}, {0, {8, 9}}, {5, {}}},
    {{5, {}},        {0, {1, 4}},    {0, {1, 7}},       {3, {}},        {9, {}},        {0, {7, 8}},       {0, {1, 4, 8}}, {6, {}},     {2, {}}},
    {{3, {}},        {6, {}},        {0, {5, 9}},       {4, {}},        {0, {5, 8}},    {1, {}},           {2, {}},        {7, {}},     {0, {8, 9}}},
    {{4, {}},        {7, {}},        {0, {2, 9}},       {6, {}},        {0, {2, 3, 8}}, {0, {2, 3, 8, 9}}, {5, {}},        {0, {1, 8}}, {0, {1, 8, 9}}},
    {{0, {1, 2}},    {8, {}},        {0, {1, 2, 5, 9}}, {0, {2, 7}},    {0, {2, 5, 7}}, {0, {2, 5, 7, 9}}, {6, {}},        {3, {}},     {4, {}}}
  });
  std::vector<CountTestCase> test_cases{
    {1, atn::Line::COLUMN, 0, 2},
    {1, atn::Line::COLUMN, 1, 2},
    {1, atn::Line::COLUMN, 2, 2},
    {1, atn::Line::COLUMN, 3, 1},
    {1, atn::Line::COLUMN, 4, 0},
    {1, atn::Line::COLUMN, 5, 0},
    {1, atn::Line::COLUMN, 6, 2},
    {1, atn::Line::COLUMN, 7, 2},
    {1, atn::Line::COLUMN, 8, 2},
    {1, atn::Line::ROW, 0, 2},
    {1, atn::Line::ROW, 1, 2},
    {1, atn::Line::ROW, 2, 2},
    {1, atn::Line::ROW, 3, 2},
    {1, atn::Line::ROW, 4, 0},
    {1, atn::Line::ROW, 5, 2},
    {1, atn::Line::ROW, 6, 0},
    {1, atn::Line::ROW, 7, 1},
    {1, atn::Line::ROW, 8, 1}    
  };
  // clang-format on
  atn::LineBoxView view{board};
  for (auto test_case : test_cases) {
    EXPECT_EQ(
        view.count_boxes(test_case.value, test_case.line, test_case.index),
        test_case.expected);
  }
}

TEST(LineBoxViewTest, BitsetTest) {
  // clang-format off
  atn::BoardPtr board = atn::generate_board_with_options({
    {{9, {}},        {3, {}},        {4, {}},           {0, {1, 2, 7}}, {6, {}},        {0, {2, 7}},       {0, {1, 7, 8}}, {5, {}},     {0, {1, 8}}},
    {{0, {1, 7}},    {0, {1, 5}},    {6, {}},           {0, {1, 7, 8}}, {0, {5, 7, 8}}, {4, {}},           {9, {}},        {2, {}},     {3, {}}},
    {{0, {1, 2, 7}}, {0, {1, 2, 5}}, {8, {}},           {9, {}},        {0, {3, 5, 7}}, {0, {3, 5, 7}},    {0, {1, 7}},    {4, {}},     {6, {}}},
    {{8, {}},        {0, {1, 2, 9}}, {0, {1, 2, 3, 9}}, {5, {}},        {4, {}},        {6, {}},           {0, {1, 3}},    {0, {1, 9}}, {7, {}}},
    {{6, {}},        {0, {4, 9}},    {0, {3, 7, 9}},    {0, {2, 7, 8}}, {1, {}},        {0, {2, 7, 8}},    {0, {3, 4, 8}}, {0, {8, 9}}, {5, {}}},
    {{5, {}},        {0, {1, 4}},    {0, {1, 7}},       {3, {}},        {9, {}},        {0, {7, 8}},       {0, {1, 4, 8}}, {6, {}},     {2, {}}},
    {{3, {}},        {6, {}},        {0, {5, 9}},       {4, {}},        {0, {5, 8}},    {1, {}},           {2, {}},        {7, {}},     {0, {8, 9}}},
    {{4, {}},        {7, {}},        {0, {2, 9}},       {6, {}},        {0, {2, 3, 8}}, {0, {2, 3, 8, 9}}, {5, {}},        {0, {1, 8}}, {0, {1, 8, 9}}},
    {{0, {1, 2}},    {8, {}},        {0, {1, 2, 5, 9}}, {0, {2, 7}},    {0, {2, 5, 7}}, {0, {2, 5, 7, 9}}, {6, {}},        {3, {}},     {4, {}}}
  });
  std::vector<BitsetTestCase> test_cases{
    {1, atn::Line::COLUMN, 0, 0b101},
    {1, atn::Line::COLUMN, 1, 0b011},
    {1, atn::Line::COLUMN, 2, 0b110},
    {1, atn::Line::COLUMN, 3, 0b001},
    {1, atn::Line::COLUMN, 4, 0b000},
    {1, atn::Line::COLUMN, 5, 0b000},
    {1, atn::Line::COLUMN, 6, 0b011},
    {1, atn::Line::COLUMN, 7, 0b110},
    {1, atn::Line::COLUMN, 8, 0b101},
    {1, atn::Line::ROW, 0, 0b110},
    {1, atn::Line::ROW, 1, 0b011},
    {1, atn::Line::ROW, 2, 0b101},
    {1, atn::Line::ROW, 3, 0b101},
    {1, atn::Line::ROW, 4, 0b000},
    {1, atn::Line::ROW, 5, 0b101},
    {1, atn::Line::ROW, 6, 0b000},
    {1, atn::Line::ROW, 7, 0b100},
    {1, atn::Line::ROW, 8, 0b001}    
  };
  // clang-format on
  atn::LineBoxView view{board};
  for (auto test_case : test_cases) {
    EXPECT_EQ(view.box_bitset(test_case.value, test_case.line, test_case.index),
              test_case.expected);
  }
}
