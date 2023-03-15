#include "types.hpp"

namespace ilox {

OptionalLiteral NewLiteral(int value) {
  return OptionalLiteral(std::in_place, value);
}

OptionalLiteral NewLiteral(float value) {
  return OptionalLiteral(std::in_place, value);
}

OptionalLiteral NewLiteral(char value) {
  return OptionalLiteral(std::in_place, value);
}

OptionalLiteral NewLiteral(std::string value) {
  return OptionalLiteral(std::in_place, value);
}
} // namespace ilox
