#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "lexer.hpp"
#include "tokens.hpp"

TEST_CASE("testing the Token class") {
  auto tok = ilox::Token(ilox::TokenType::STRING, "fun", "fun", 0);
  CHECK(tok.Type() == ilox::TokenType::STRING);
  CHECK(tok.Lexeme() == "fun");
  CHECK(tok.Literal().has_value());
}

TEST_CASE("testing the Lexer scanning routine") {
  std::vector<ilox::Token> tokens;
  // start with no tokens
  REQUIRE(tokens.size() == 0);
  SUBCASE("lexing a simple one line expression") {
    auto scanner = ilox::Scanner("!*+-/=<> <= ==");
    tokens = scanner.ScanTokens();
    CHECK(tokens.size() == 11);
    for (auto &tok : tokens) {
      std::cout << tok.String();
    }
  }
}
