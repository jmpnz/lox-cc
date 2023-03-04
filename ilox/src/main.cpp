#include "debug.hpp"
#include "interpreter.hpp"
#include "lexer.hpp"
#include "tokens.hpp"
#include "usage.hpp"
#include <iostream>
#include <sysexits.h>

int main(int argc, char *argv[]) {

  auto tok = ilox::Token(ilox::TokenType::STRING, "fun", "fun", 0);
  std::cout << tok.String();
  if (argc > 2) {
    std::cout << UsageMessage << std::endl;
    exit(1);
  } else if (argc == 2) {
    auto lines = ilox::ReadScriptFile(argv[1]);
    ilox::DebugView(lines);
  } else {
    ilox::RunPrompt();
  }
}