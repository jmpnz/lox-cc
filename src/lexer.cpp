#include "lexer.hpp"
#include "debug.hpp"
#include "tokens.hpp"
#include "types.hpp"
#include <cctype>
#include <iostream>
#include <string>
#include <vector>

// Helper functions for finding whether a character is a numeric, alphabet or
// else.
auto IsAlpha(char ch) -> bool { return isalpha(ch); }

auto IsNumeric(char ch) -> bool { return isnumber(ch); }

auto IsAlphaNumeric(char ch) -> bool { return isalnum(ch); }

namespace lox {

auto Scanner::ScanTokens() -> std::vector<Token> {
  int line = 0;
  while (!ReachedEnd()) {
    start = current;
    this->ScanToken();
  }
  // Add the EOF Token to signal end of source.
  tokens.push_back(Token(TokenType::L_EOF, "", '\0', line));
  return this->tokens;
}

auto Scanner::ReachedEnd() -> bool { return current >= source.length(); }

auto Scanner::Advance() -> char { return this->source.at(current++); }

auto Scanner::AddToken(TokenType type) -> void {
  this->AddToken(type, std::nullopt);
}

auto Scanner::AddToken(TokenType type, OptionalLiteral literal) -> void {
  auto text = this->source.substr(start, current - start);
  this->tokens.push_back(Token(type, text, literal, this->line));
}

auto Scanner::Match(char expected) -> bool {
  if (this->ReachedEnd()) {
    return false;
  }
  if (source.at(current) != expected) {
    return false;
  }
  current++;
  return true;
}

auto Scanner::ScanToken() -> void {
  char c = Advance();
  switch (c) {
    // Single char tokens.
  case '(':
    AddToken(TokenType::LPAREN);
    break;
  case ')':
    AddToken(TokenType::RPAREN);
    break;
  case '{':
    AddToken(TokenType::RBRACE);
    break;
  case '}':
    AddToken(TokenType::LBRACE);
    break;
  case ',':
    AddToken(TokenType::COMMA);
    break;
  case '.':
    AddToken(TokenType::DOT);
    break;
  case '-':
    AddToken(TokenType::MINUS);
    break;
  case '+':
    AddToken(TokenType::PLUS);
    break;
  case ';':
    AddToken(TokenType::SEMI_COLON);
    break;
  case '*':
    AddToken(TokenType::STAR);
    break;
  // Multichar tokens.
  case '!':
    AddToken(Match('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
    break;
  case '=':
    AddToken(Match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
    break;
  case '<':
    AddToken(Match('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
    break;
  case '>':
    AddToken(Match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
    break;
  case '/':
    if (Match('/')) {
      while (Peek() != '\n' && !this->ReachedEnd()) {
        Advance();
      }
    } else {
      AddToken(TokenType::SLASH);
    }
    break;
  case ' ':
  case '\r':
  case '\t':
    break;
  case '\n':
    line++;
    break;
  case '"':
    ScanString();
    break;
  default:
    if (IsNumeric(c)) {
      ScanNumber();
    } else if (IsAlpha(c)) {
      ScanIdentifier();
    } else {
      std::cerr << "Unexpected character :" << c;
    }
    break;
  }
}

auto Scanner::Peek() -> char {
  if (ReachedEnd())
    return '\0';
  return source.at(current);
}

auto Scanner::ScanNumber() -> void {
  while (IsNumeric(Peek())) {
    Advance();
  }
  AddToken(
      TokenType::NUMBER,
      NewOptionalLiteral(TokenType::NUMBER, source.substr(start, current)));
}

auto Scanner::ScanString() -> void {
  while (Peek() != '"' && !ReachedEnd()) {
    if (Peek() == '\n')
      line++;
    Advance();
  }
  if (ReachedEnd()) {
    std::cerr << line << "Unterminated string";
    return;
  }
  // Eat the closing "
  Advance();
  // Trim surrounding quotes
  std::string value = source.substr(start + 1, current - 2);
  AddToken(TokenType::STRING, NewOptionalLiteral(TokenType::STRING, value));
}

auto Scanner::ScanIdentifier() -> void {
  while (IsAlphaNumeric(Peek())) {
    Advance();
  }
  std::string identifier = source.substr(start, current);
  auto iter = Keywords.find(identifier);
  if (iter == Keywords.end()) {
    AddToken(TokenType::IDENTIFIER, identifier);
    return;
  }
  AddToken(iter->second);
}

auto Scanner::NewOptionalLiteral(TokenType type, std::string lexeme)
    -> OptionalLiteral {
  switch (type) {
  case TokenType::NUMBER:
    return NewLiteral(atoi(lexeme.c_str()));
  case TokenType::STRING:
    return NewLiteral(lexeme);
  default:
    return std::nullopt;
  }
}

} // namespace lox
