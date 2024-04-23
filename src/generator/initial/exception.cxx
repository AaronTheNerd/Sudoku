#include "../initial/exception.h"

atn::generator::initial::GenerationFailedException::
    GenerationFailedException() noexcept {
  this->message = "Initial board generation failed";
}

const char* atn::generator::initial::GenerationFailedException::what()
    const noexcept {
  return this->message.c_str();
}