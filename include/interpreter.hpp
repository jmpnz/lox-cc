#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <string>

namespace lox {

auto Run(std::string source) -> void;
auto RunPrompt() -> void;

} // namespace lox

#endif
