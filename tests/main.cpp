#include "ast.hpp"
#include <memory>
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
    tokens.clear();
  }
  SUBCASE("lexing an identifier") {
    auto scanner = lox::Scanner("lex a = 5;");
    tokens = scanner.ScanTokens();
    CHECK(tokens.size() == 6);
    for (auto &tok : tokens) {
      std::cout << tok.String();
    }
    tokens.clear();
  }
  SUBCASE("lexing a group of keywords") {
    auto scanner = lox::Scanner("var a = 5;");
    tokens = scanner.ScanTokens();
    CHECK(tokens.size() == 6);
    for (auto &tok : tokens) {
      std::cout << tok.String();
    }
    tokens.clear();
  }
}

TEST_CASE("parsing expressions with an AST") {
  std::unique_ptr<lox::Expr> expr = std::make_unique<lox::BinaryExpr>(
      std::make_unique<lox::LiteralExpr>(1),
      lox::Token(lox::TokenType::PLUS, "+", std::nullopt, 0),
      std::make_unique<lox::LiteralExpr>(2.5f));
  lox::ASTPrinter printer;
  expr->Accept(printer);
  std::cout << std::endl;
}
