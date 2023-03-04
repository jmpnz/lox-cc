#include "debug.hpp"
#include "tokens.hpp"
#include <iostream>
#include <string>

// Helper functions for finding whether a character is a numeric, alphabet or
// else.
bool IsAlpha(char ch) { return isalpha(ch); }

bool IsNumeric(char ch) { return isnumber(ch); }

namespace ilox {

void Lex(std::string code) {
  std::cout << code << '\n';
  for (auto &ch : code) {
    if (IsAlpha(ch)) {
      DebugMessage("Got char");
    }
    if (IsNumeric(ch)) {
      DebugMessage("Got number");
    }
  }
}

} // namespace ilox
