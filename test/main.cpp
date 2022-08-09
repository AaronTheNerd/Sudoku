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
  TEST_SUITE_INIT();
  TEST_SUITE("Single Candidate", test_single_candidate());
  TEST_SUITE("Single Position", test_single_position());
  TEST_SUITE("Candidate Lines", test_candidate_lines());
  // Double Pairs
  // Multiple Lines
  TEST_SUITE("Naked Pair", test_naked_pair());
  // Hidden Pair
  // Naked Triple
  // Hidden Triple
  // X Wing
  // Forcing Chains
  // Naked Quad
  // Hidden Quad
  // Swordfish
  PRINT_RESULTS();
}
