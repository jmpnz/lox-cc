#ifndef LEXER_HPP
#define LEXER_HPP
#include "tokens.hpp"
#include "types.hpp"
#include <string>
#include <vector>
namespace lox {

// Scanner class will implement a lexer for our language here.
class Scanner {
  // Source is essentially the source code we are trying to scan, we can load
  // all of it in memory.
  std::string source;
  // Tokens is the output of our scanner, a list of tokens representing
  // the source code.
  std::vector<Token> tokens;
  // Start points to the first character in the lexeme being scanned.
  size_t start = 0;
  // Current points to the current character in the lexeme being scanned.
  size_t current = 0;
  // Line points to the current line in the source file being scanned.
  size_t line = 1;

public:
  // Typical constructor for this class, file processing will be done outside
  // the Scanner class.
  Scanner(std::string source) : source(source){};
  // ScanTokens will walk the source code string and try to determine at each
  // step which token should be created given the input returning the expected
  // output tokens to the caller as well.
  auto ScanTokens() -> std::vector<Token>;
  // ScanToken scans the current lexeme outputing the token it represents.
  auto ScanToken() -> void;
  // Advance advances the scanner's offset in the source.
  auto Advance() -> char;
  // AddToken is a helper function that builds a token from the current
  // lexeme and adds it to our tokens vector.
  auto AddToken(TokenType type, OptionalLiteral literal) -> void;
  // AddToken without literals.
  auto AddToken(TokenType type) -> void;
  // ReachedEnd will check if we reached the end of the source being scanned.
  auto ReachedEnd() -> bool;
  // NewOptionalLiteral builds an optional literal value given a token type.
  auto NewOptionalLiteral(TokenType type, std::string lexeme)
      -> OptionalLiteral;
  // Match is a conditional advance used to process multi char tokens.
  auto Match(char expected) -> bool;
  // ScanNumber scans a numerical value.
  auto ScanNumber() -> void;
  // ScanString scans inline strings.
  auto ScanString() -> void;
  // ScanIdentifier scans identifier.
  auto ScanIdentifier() -> void;
  // Peek returns the next token by performing a lookahead.
  auto Peek() -> char;
};

} // namespace lox

#endif // LEXER_HPP
