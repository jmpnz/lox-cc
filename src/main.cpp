#include "debug.hpp"
#include "interpreter.hpp"
#include "lexer.hpp"
#include "tokens.hpp"
#include "usage.hpp"
#include <iostream>
#include <sysexits.h>

int main(int argc, char *argv[]) {

  if (argc > 2) {
    std::cout << UsageMessage << std::endl;
    exit(1);
  } else if (argc == 2) {
    auto lines = lox::ReadScriptFile(argv[1]);
    lox::DebugView(lines);
  } else {
    lox::RunPrompt();
  }
}
