#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <string>

namespace lox {

// Run a given Lox source code.
auto Run(std::string source) -> void;

// Run the REPL.
auto RunPrompt() -> void;

} // namespace lox

#endif
