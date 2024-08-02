#pragma once

#include <exception>
#include <string>

namespace atn {

class GenerationFailedException : public std::exception {
 public:
  GenerationFailedException() noexcept;
  const char* what() const noexcept;

 private:
  std::string message;
};

}  // namespace atn
