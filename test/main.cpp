// Written by Aaron Barge
// Copyright 2022

#include <string>
#include <vector>
#include "unittest.h"

#include "techniques/candidate_lines.hpp"
#include "techniques/naked_pair.hpp"
#include "techniques/single_candidate.hpp"
#include "techniques/single_position.hpp"

int main(int argc, char** argv) {
  TIME(test_single_candidate());
  TIME(test_single_position());
  TIME(test_candidate_lines());
  TIME(test_naked_pair());
}
