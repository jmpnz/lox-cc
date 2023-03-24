#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "lexer.hpp"
#include "tokens.hpp"

TEST_CASE("testing the Token class") {
  auto tok = lox::Token(lox::TokenType::STRING, "fun", "fun", 0);
  CHECK(tok.Type() == lox::TokenType::STRING);
  CHECK(tok.Lexeme() == "fun");
  CHECK(tok.Literal().has_value());
}

TEST_CASE("testing the Lexer scanning routine") {
  std::vector<lox::Token> tokens;
  // start with no tokens
  REQUIRE(tokens.size() == 0);
  SUBCASE("lexing a simple one line expression") {
    auto scanner = lox::Scanner("!*+-/=<> <= ==");
    tokens = scanner.ScanTokens();
    CHECK(tokens.size() == 11);
    for (auto &tok : tokens) {
      std::cout << tok.String();
    }
    tokens.clear();
  }
  SUBCASE("lexing a string value") {
    auto scanner = lox::Scanner("\"Hanzo\"");
    tokens = scanner.ScanTokens();
    // The EOF token is always appended at the end
    CHECK(tokens.size() == 2);
    for (auto &tok : tokens) {
      std::cout << tok.String();
    }
  }
}
