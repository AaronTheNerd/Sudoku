#include "../initial/get_generator.h"

#include "recursive.h"

atn::InitialGeneratorPtr atn::get_generator(InitialGeneratorType type) {
  switch (type) {
    case InitialGeneratorType::RECURSIVE:
      return std::make_shared<Recursive>();
  }
}