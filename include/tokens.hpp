#ifndef TOKENS_HPP
#define TOKENS_HPP
#include "types.hpp"
#include <string>
#include <unordered_map>

namespace lox {

// Enum TokenType is used to assign a type to each token.
enum class TokenType {
  // Single character tokens
  LPAREN,
  RPAREN,
  LBRACE,
  RBRACE,
  COMMA,
  DOT,
  MINUS,
  PLUS,
  SEMI_COLON,
  SLASH,
  STAR,

  // One or two character tokens
  BANG,
  BANG_EQUAL,
  EQUAL,
  EQUAL_EQUAL,
  GREATER,
  GREATER_EQUAL,
  LESS,
  LESS_EQUAL,

  // Literals strings, numerics and identifiers.
  IDENTIFIER,
  STRING,
  NUMBER,

  // Keywords
  AND,
  CLASS,
  ELSE,
  FALSE,
  FUN,
  FOR,
  IF,
  NIL,
  OR,
  PRINT,
  RETURN,
  SUPER,
  THIS,
  TRUE,
  VAR,
  WHILE,

  L_EOF

};

// Keywords defines the Lox language keywords.
const static std::unordered_map<std::string, TokenType> Keywords = {
    {"and", TokenType::AND},       {"class", TokenType::CLASS},
    {"else", TokenType::ELSE},     {"false", TokenType::FALSE},
    {"for", TokenType::FOR},       {"fun", TokenType::FUN},
    {"if", TokenType::IF},         {"nil", TokenType::NIL},
    {"or", TokenType::OR},         {"print", TokenType::PRINT},
    {"return", TokenType::RETURN}, {"super", TokenType::SUPER},
    {"this", TokenType::THIS},     {"true", TokenType::TRUE},
    {"var", TokenType::VAR},       {"while", TokenType::WHILE},
};

auto TokenTypeToString(TokenType type) -> std::string;

// Token represents a single token in our code which is a string literal
// with a wrapped token type (keyword, identifier, numeric..), position
// and other useful metadata.
class Token {
  TokenType type;
  std::string lexeme;
  OptionalLiteral literal;
  int line;

public:
  // Construct class for our token.
  Token(TokenType type, std::string lexeme, OptionalLiteral literal, int line)
      : type(type), lexeme(lexeme), literal(literal), line(line) {}

  // General Getters
  auto Type() -> TokenType { return this->type; }
  auto Literal() -> OptionalLiteral { return this->literal; }
  auto Lexeme() const -> std::string { return this->lexeme; }

  // String prints a string representation of the token.
  auto String() -> std::string;
};

} // namespace lox

#endif
