#include "types.hpp"

namespace lox {

auto NewLiteral(int value) -> OptionalLiteral {
  return OptionalLiteral(std::in_place, value);
}

auto NewLiteral(float value) -> OptionalLiteral {
  return OptionalLiteral(std::in_place, value);
}

auto NewLiteral(char value) -> OptionalLiteral {
  return OptionalLiteral(std::in_place, value);
}

auto NewLiteral(std::string value) -> OptionalLiteral {
  return OptionalLiteral(std::in_place, value);
}
} // namespace lox
