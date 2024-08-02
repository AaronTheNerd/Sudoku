#pragma once

#include <memory>

#include "../initial/generator.h"

namespace atn {

enum class InitialGeneratorType { RECURSIVE };

InitialGeneratorPtr get_generator(InitialGeneratorType);

}  // namespace atn
