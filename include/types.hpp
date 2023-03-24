#ifndef TYPES_HPP
#define TYPES_HPP

#include <optional>
#include <string>
#include <variant>

namespace lox {
using Literal = std::variant<int, float, std::string, char>;
using OptionalLiteral = std::optional<Literal>;

OptionalLiteral NewLiteral(int value);
OptionalLiteral NewLiteral(float value);
OptionalLiteral NewLiteral(char value);
OptionalLiteral NewLiteral(std::string value);

} // namespace lox

// Literal type defintion

#endif
