#ifndef TYPES_HPP
#define TYPES_HPP

#include <optional>
#include <string>
#include <variant>

namespace lox {
using Literal = std::variant<int, float, std::string, char>;
using OptionalLiteral = std::optional<Literal>;

auto NewLiteral(int value) -> OptionalLiteral;
auto NewLiteral(float value) -> OptionalLiteral;
auto NewLiteral(char value) -> OptionalLiteral;
auto NewLiteral(std::string value) -> OptionalLiteral;

} // namespace lox

// Literal type defintion

#endif
