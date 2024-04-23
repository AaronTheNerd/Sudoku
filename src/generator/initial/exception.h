#pragma once

#include <exception>
#include <string>

namespace atn::generator::initial {

class GenerationFailedException : public std::exception {
 public:
  GenerationFailedException() noexcept;
  const char* what() const noexcept;

 private:
  std::string message;
};

}  // namespace atn::generator::initial
