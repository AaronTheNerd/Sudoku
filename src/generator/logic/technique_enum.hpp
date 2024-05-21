#pragma once

namespace atn::generator::logic {

enum class TechniqueEnum {
  SINGLE_CANDIDATE,
  SINGLE_POSITION,
  CANDIDATE_LINES,
  DOUBLE_PAIRS,
  MULTIPLE_LINES,
  NAKED_PAIR,
  HIDDEN_PAIR,
  NAKED_TRIPLE,
  HIDDEN_TRIPLE,
  X_WING,
  FORCING_CHAINS,
  NAKED_QUAD,
  HIDDEN_QUAD,
  SWORDFISH
};

}  // namespace atn::generator::logic
