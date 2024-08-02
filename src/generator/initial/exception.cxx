#include "../initial/exception.h"

atn::GenerationFailedException::GenerationFailedException() noexcept {
  this->message = "Initial board generation failed";
}

const char* atn::GenerationFailedException::what() const noexcept {
  return this->message.c_str();
}