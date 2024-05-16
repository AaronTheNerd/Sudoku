#include <gtest/gtest.h>

#include <memory>
#include <optional>

#include "board.h"
#include "command/clear_options.h"
#include "command/macro_command.h"
#include "command/set_value.h"
#include "test_utils.h"

using namespace atn::generator::command;
using namespace atn::sudoku;
using namespace atn::test_utils;

TEST(CommandsTest, SetValue) {
  Board board = generate_board({{0, 2, 3, 4, 5, 6, 7, 8, 9},
                                {2, 3, 4, 5, 6, 7, 8, 9, 1},
                                {3, 4, 5, 6, 7, 8, 9, 1, 2},
                                {4, 5, 6, 7, 8, 9, 1, 2, 3},
                                {5, 6, 7, 8, 9, 1, 2, 3, 4},
                                {6, 7, 8, 9, 1, 2, 3, 4, 5},
                                {7, 8, 9, 1, 2, 3, 4, 5, 6},
                                {8, 9, 1, 2, 3, 4, 5, 6, 7},
                                {9, 1, 2, 3, 4, 5, 6, 7, 8}});
  Position pos{0, 0};
  CellPtr cell = board.get(pos);
  Value value{1};
  SetValue command{cell, value};
  EXPECT_FALSE(board.get(pos)->is_set());
  command.apply();
  EXPECT_EQ(board.get(pos)->get(), value);
  command.undo();
  EXPECT_FALSE(board.get(pos)->is_set());
}

TEST(CommandsTest, ClearOptions) {
  Board board = generate_board({{0, 2, 3, 4, 5, 6, 7, 8, 9},
                                {2, 3, 4, 5, 6, 7, 8, 9, 1},
                                {3, 4, 5, 6, 7, 8, 9, 1, 2},
                                {4, 5, 6, 7, 8, 9, 1, 2, 3},
                                {5, 6, 7, 8, 9, 1, 2, 3, 4},
                                {6, 7, 8, 9, 1, 2, 3, 4, 5},
                                {7, 8, 9, 1, 2, 3, 4, 5, 6},
                                {8, 9, 1, 2, 3, 4, 5, 6, 7},
                                {9, 1, 2, 3, 4, 5, 6, 7, 8}});
  Position pos{0, 0};
  CellPtr cell = board.get(pos);
  std::vector<Value> all_values{1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::vector<Value> removed_options{1, 3, 5, 7, 9};
  std::vector<Value> remaining_options{2, 4, 6, 8};
  ClearOptions command{cell, removed_options};
  EXPECT_TRUE(cell_has_options_set(board.get(pos), all_values));
  command.apply();
  EXPECT_TRUE(cell_has_options_set(board.get(pos), remaining_options));
  command.undo();
  EXPECT_TRUE(cell_has_options_set(board.get(pos), all_values));
}

struct MacroCommandTestCase {
  Position pos;
  std::optional<Value> before_value;
  std::optional<Value> after_value;
  std::optional<std::vector<Value>> before_options;
  std::optional<std::vector<Value>> after_options;
};

TEST(CommandsTest, MacroCommand) {
  Board board = generate_board({{0, 0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0}});
  std::vector<Value> all_options{1, 2, 3, 4, 5, 6, 7, 8, 9};
  // clang-format off
  std::vector<MacroCommandTestCase> test_cases{
    {{0, 0}, 0,            6,            std::nullopt, std::nullopt},
    {{0, 1}, std::nullopt, std::nullopt, all_options,  {{1, 2, 3, 4, 5, 7, 8, 9}}},
    {{1, 0}, std::nullopt, std::nullopt, all_options,  {{2, 4, 6, 8}}},
    {{2, 0}, 0,            3,            std::nullopt, std::nullopt}
  };
  std::vector<CommandPtr> commands{
    std::make_shared<SetValue>(board.get({0, 0}), 6),
    std::make_shared<ClearOptions>(board.get({0, 1}), std::vector<Value>{6}),
    std::make_shared<ClearOptions>(board.get({1, 0}), std::vector<Value>{1, 3, 5, 7, 9}),
    std::make_shared<SetValue>(board.get({2, 0}), 3)
  };
  // clang-format on
  MacroCommand command{commands};
  for (uint i{0}; i < test_cases.size(); ++i) {
    auto test_case = test_cases[i];
    auto pos = test_case.pos;
    if (auto before_value = test_case.before_value) {
      EXPECT_EQ(board.get(pos)->get(), *before_value);
    }
    if (auto before_options = test_case.before_options) {
      EXPECT_TRUE(cell_has_options_set(board.get(pos), *before_options));
    }
  }
  command.apply();
  for (uint i{0}; i < test_cases.size(); ++i) {
    auto test_case = test_cases[i];
    auto pos = test_case.pos;
    if (auto after_value = test_case.after_value) {
      EXPECT_EQ(board.get(pos)->get(), *after_value);
    }
    if (auto after_options = test_case.after_options) {
      EXPECT_TRUE(cell_has_options_set(board.get(pos), *after_options));
    }
  }
  command.undo();
  for (uint i{0}; i < test_cases.size(); ++i) {
    auto test_case = test_cases[i];
    auto pos = test_case.pos;
    if (auto before_value = test_case.before_value) {
      EXPECT_EQ(board.get(pos)->get(), *before_value);
    }
    if (auto before_options = test_case.before_options) {
      EXPECT_TRUE(cell_has_options_set(board.get(pos), *before_options));
    }
  }
}
