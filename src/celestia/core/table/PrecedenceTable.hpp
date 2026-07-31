#pragma once

#include "celestia/core/operators/Associativity.hpp"
#include "celestia/core/operators/BinaryOperation.hpp"
#include "celestia/core/operators/OperatorKind.hpp"
#include "celestia/core/operators/PostfixOperation.hpp"
#include "celestia/core/operators/UnaryOperation.hpp"
#include "celestia/core/token/TokenKind.hpp"

#include <unordered_map>
#include <variant>

namespace core::table {

using ExpressionOperator = std::variant<BinaryOperation, UnaryOperation, PostfixOperation>;

struct OperatorInfo {

  int lbp;
  int rbp;

  OperatorKind kind;

  ExpressionOperator op;
};

class OperatorTable {

public:
  void add(TokenKind token, int lbp, int rbp, OperatorKind kind, ExpressionOperator op) { table[token] = {lbp, rbp, kind, op}; }

  void add_infix(TokenKind token, int precedence, Associativity assoc, BinaryOperation op) {
    if (assoc == Associativity::Left) {
      add(token, precedence, precedence + 1, OperatorKind::Infix, op);
    } else {
      add(token, precedence, precedence - 1, OperatorKind::Infix, op);
    }
  }

  void add_prefix(TokenKind token, int precedence, UnaryOperation op) { add(token, precedence, precedence, OperatorKind::Prefix, op); }

  void add_postfix(TokenKind token, int precedence, PostfixOperation op) { add(token, precedence, precedence, OperatorKind::Postfix, op); }

  bool has(TokenKind token) const { return table.contains(token); }

  const OperatorInfo *get(TokenKind token) const {
    auto it = table.find(token);

    if (it == table.end()) return nullptr;

    return &it->second;
  }

private:
  std::unordered_map<TokenKind, OperatorInfo> table;
};

} // namespace core::table