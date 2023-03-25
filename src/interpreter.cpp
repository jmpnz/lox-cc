#include "interpreter.hpp"
#include "lexer.hpp"
#include <iostream>
#include <string>

namespace lox {

auto RunPrompt() -> void {
  std::cout << "This is an lox prompt" << '\n';
  while (true) {
    std::string line;
    std::cout << "> ";
    std::getline(std::cin, line);
    if (line == "exit") {
      exit(1);
    } else {
      Run(line);
    }
  }
}

auto Run(std::string source) -> void {
  auto scanner = Scanner(source);
  auto tokens = scanner.ScanTokens();

  for (auto &tok : tokens)
    std::cout << tok.String() << '\n';
}

} // namespace lox
