set(source_files
  candidate_lines.cxx
  double_pairs.cxx
  next_move.cxx
  single_candidate.cxx
  single_position.cxx
  technique.cxx
)

add_library(LogicalSolver ${source_files})

target_include_directories(LogicalSolver INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(LogicalSolver PUBLIC Command Sudoku compiler_flags)