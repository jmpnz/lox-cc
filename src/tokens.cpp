#include "tokens.hpp"
#include "types.hpp"
#include <iostream>
#include <sstream>

namespace lox {

auto TokenTypeToString(TokenType type) -> std::string {
  switch (type) {
  case TokenType::LPAREN:
    return "(";
  case TokenType::RPAREN:
    return ")";
  case TokenType::LBRACE:
    return "{";
  case TokenType::RBRACE:
    return "}";
  case TokenType::COMMA:
    return ",";
  case TokenType::DOT:
    return ".";
  case TokenType::MINUS:
    return "-";
  case TokenType::PLUS:
    return "+";
  case TokenType::SEMI_COLON:
    return ";";
  case TokenType::SLASH:
    return "/";
  case TokenType::STAR:
    return "*";
  case TokenType::BANG:
    return "!";
  case TokenType::BANG_EQUAL:
    return "!=";
  case TokenType::EQUAL:
    return "=";
  case TokenType::EQUAL_EQUAL:
    return "==";
  case TokenType::GREATER:
    return ">";
  case TokenType::GREATER_EQUAL:
    return ">=";
  case TokenType::LESS:
    return "<";
  case TokenType::LESS_EQUAL:
    return "<=";
  case TokenType::IDENTIFIER:
    return "IDENT";
  case TokenType::STRING:
    return "STRING";
  case TokenType::NUMBER:
    return "NUMBER";
  case TokenType::AND:
    return "AND";
  case TokenType::CLASS:
    return "CLASS";
  case TokenType::ELSE:
    return "ELSE";
  case TokenType::FALSE:
    return "FALSE";
  case TokenType::FUN:
    return "FUN";
  case TokenType::FOR:
    return "FOR";
  case TokenType::IF:
    return "IF";
  case TokenType::NIL:
    return "NIL";
  case TokenType::OR:
    return "OR";
  case TokenType::PRINT:
    return "PRINT";
  case TokenType::RETURN:
    return "RETURN";
  case TokenType::SUPER:
    return "SUPER";
  case TokenType::THIS:
    return "THIS";
  case TokenType::TRUE:
    return "TRUE";
  case TokenType::VAR:
    return "VAR";
  case TokenType::WHILE:
    return "WHILE";
  case TokenType::L_EOF:
    return "EOF";
  default:
    return "Unknown Token";
  }
}

auto Token::String() -> std::string {
  std::stringstream value;
  std::string literal_value;
  std::string type = lox::TokenTypeToString(this->type);

  switch (this->type) {
  case TokenType::STRING:
    literal_value = std::get<std::string>(this->literal.value());
    break;
  case TokenType::NUMBER:
    literal_value = std::get<int>(this->literal.value());
    break;
  case TokenType::IDENTIFIER:
    literal_value = std::get<std::string>(this->literal.value());
    break;
  default:
    literal_value = type;
  }
  value << "Line : " << line << " Type : " << type << " Lexeme : " << lexeme
        << " Literal : " << literal_value << '\n';

  return value.str();
}

} // namespace lox
