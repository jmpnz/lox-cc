#include "ast.hpp"
#include <any>
#include <iostream>
#include <type_traits>
#include <variant>
#include <vector>

namespace lox {

auto BinaryExpr::Accept(ExprVisitor &visitor) -> void {
  return visitor.VisitBinaryExpr(*this);
}

auto LiteralExpr::Accept(ExprVisitor &visitor) -> void {
  return visitor.VisitLiteralExpr(*this);
}

auto ASTPrinter::VisitBinaryExpr(const BinaryExpr &expr) -> void {
  auto lexeme = expr.op.Lexeme();
  std::cout << "(";
  expr.left->Accept(*this);
  std::cout << " " << expr.op.Lexeme() << " ";
  expr.right->Accept(*this);
  std::cout << ")";
}

auto ASTPrinter::VisitLiteralExpr(const LiteralExpr &expr) -> void {
  std::visit(
      [](auto &&arg) {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, int>) {
          std::cout << arg;
        } else {
          std::cout << arg;
        }
      },
      expr.value);
}
} // namespace lox
