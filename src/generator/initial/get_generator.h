#pragma once

#include <memory>

#include "../initial/generator.h"

namespace atn::generator::initial {

enum class GeneratorType { RECURSIVE };

atn::generator::initial::GeneratorPtr get_generator(
    atn::generator::initial::GeneratorType);

}  // namespace atn::generator::initial
