set(source_files
  candidate_lines.cxx
  candidate_box.cxx
  next_move.cxx
  single_candidate.cxx
  single_position.cxx
  technique.cxx
  line_box_view.cxx
)

add_library(LogicalSolver ${source_files})

target_include_directories(LogicalSolver INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(LogicalSolver PUBLIC Command Sudoku compiler_flags)