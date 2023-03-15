#ifndef TOKENS_HPP
#define TOKENS_HPP
#include "types.hpp"
#include <string>
#include <unordered_map>

namespace ilox {

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

std::string TokenTypeToString(TokenType type);

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
  TokenType Type() { return this->type; }
  OptionalLiteral Literal() { return this->literal; }
  std::string Lexeme() { return this->lexeme; }

  // String prints a string representation of the token.
  std::string String();
};

} // namespace ilox

#endif