#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "lexer.hpp"
#include "tokens.hpp"

int factorial(int number) {
  return number <= 1 ? number : factorial(number - 1) * number;
}

TEST_CASE("testing the factorial function") {
  CHECK(factorial(1) == 1);
  CHECK(factorial(2) == 2);
  CHECK(factorial(3) == 6);
  CHECK(factorial(10) == 3628800);
}

TEST_CASE("testing the Lexer for Lox") {
  auto tok = ilox::Token(ilox::TokenType::STRING, "fun", "fun", 0);
  CHECK(tok.Type() == ilox::TokenType::STRING);
  CHECK(tok.Lexeme() == "fun");
  CHECK(tok.Literal().has_value());
}