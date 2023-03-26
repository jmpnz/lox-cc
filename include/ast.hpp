#ifndef AST_HPP
#define AST_HPP

#include "tokens.hpp"
#include <any>
#include <initializer_list>
#include <memory>
#include <sstream>
#include <variant>
#include <vector>

namespace lox {

class Expr;
class LiteralExpr;
class BinaryExpr;
class ExprVisitor;

using ExprPtr = std::unique_ptr<Expr>;
using ExprVariant =
    std::variant<std::unique_ptr<LiteralExpr>, std::unique_ptr<BinaryExpr>>;
// Expr base class defines an interface for all possible expressions.
class Expr {
public:
  virtual ~Expr() = default;
  virtual void Accept(ExprVisitor &visitor) = 0;
};

// BinaryExpr is a concrete implementation of binary expressions.
class BinaryExpr : public Expr {
public:
  BinaryExpr(ExprPtr left, Token op, ExprPtr right)
      : left(std::move(left)), op(op), right(std::move(right)) {}

  void Accept(ExprVisitor &visitor) override;

  std::unique_ptr<Expr> left;
  Token op;
  std::unique_ptr<Expr> right;
};

// LiteralExpr is a concrete implementation of Literal expressions.
class LiteralExpr : public Expr {
public:
  LiteralExpr(std::variant<int, float> value) : value(value) {}
  void Accept(ExprVisitor &visitor) override;

  std::variant<int, float> value;
};

class ExprVisitor {
public:
  virtual ~ExprVisitor(){};
  virtual void VisitBinaryExpr(const BinaryExpr &expr) = 0;
  virtual void VisitLiteralExpr(const LiteralExpr &expr) = 0;
};

class ASTPrinter : public ExprVisitor {
public:
  void VisitBinaryExpr(const BinaryExpr &expr) override;
  void VisitLiteralExpr(const LiteralExpr &expr) override;
  void PrintAST(std::unique_ptr<Expr> &expr);
  std::string Parenthesize(const std::string &name,
                           const std::vector<ExprPtr> &expressions);
};

} // namespace lox
#endif
