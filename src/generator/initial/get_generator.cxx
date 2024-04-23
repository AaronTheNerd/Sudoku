#include "../initial/get_generator.h"

#include "recursive.h"

using namespace atn::generator::initial;

GeneratorPtr atn::generator::initial::get_generator(
    GeneratorType type) {
  switch (type) {
    case GeneratorType::RECURSIVE:
      return std::make_shared<Recursive>();
  }
}