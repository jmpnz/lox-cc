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
bool IsAlpha(char ch) { return isalpha(ch); }

bool IsNumeric(char ch) { return isnumber(ch); }

bool IsAlphaNumeric(char ch) { return isalnum(ch); }

namespace lox {

std::vector<Token> Scanner::ScanTokens() {
  int line = 0;
  while (!ReachedEnd()) {
    start = current;
    this->ScanToken();
  }
  // Add the EOF Token to signal end of source.
  tokens.push_back(Token(TokenType::L_EOF, "", '\0', line));
  return this->tokens;
}

bool Scanner::ReachedEnd() { return current >= source.length(); }

char Scanner::Advance() { return this->source.at(current++); }

void Scanner::AddToken(TokenType type) { this->AddToken(type, std::nullopt); }

void Scanner::AddToken(TokenType type, OptionalLiteral literal) {
  auto text = this->source.substr(start, current - start);
  this->tokens.push_back(Token(type, text, literal, this->line));
}

bool Scanner::Match(char expected) {
  if (this->ReachedEnd()) {
    return false;
  }
  if (source.at(current) != expected) {
    return false;
  }
  current++;
  return true;
}

void Scanner::ScanToken() {
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

char Scanner::Peek() {
  if (ReachedEnd())
    return '\0';
  return source.at(current);
}

void Scanner::ScanNumber() {
  while (IsNumeric(Peek())) {
    Advance();
  }
  std::cout << "Debug: " << source.substr(start, current) << '\n';
  AddToken(
      TokenType::NUMBER,
      NewOptionalLiteral(TokenType::NUMBER, source.substr(start, current)));
}

void Scanner::ScanString() {
  while(Peek() != '"' && !ReachedEnd()) {
    if (Peek() == '\n') line++;
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

void Scanner::ScanIdentifier() {
  while (IsAlphaNumeric(Peek())) {
    Advance();
  }
  std::string identifier = source.substr(start, current);
  std::cout << "Identifier: " << identifier;
  AddToken(TokenType::IDENTIFIER, identifier);
}

OptionalLiteral Scanner::NewOptionalLiteral(TokenType type,
                                            std::string lexeme) {
  switch (type) {
  case TokenType::NUMBER:
    return NewLiteral(atoi(lexeme.c_str()));
  case TokenType::STRING:
    return NewLiteral(lexeme);
  default:
    return std::nullopt;
  }
}

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

} // namespace lox
