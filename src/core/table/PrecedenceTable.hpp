#pragma once

#include "core/node/BinaryOp.hpp"
#include "core/token/TokenKind.hpp"
#include <unordered_map>

namespace core::table {

class PrecedenceTable {
public:
  struct OperatorInfo {
    int lbp;
    int rbp;
    ayla::ast::BinaryOperation op;
  };

  void add(TokenKind kind, int lbp, int rbp, ayla::ast::BinaryOperation op) { table[kind] = {lbp, rbp, op}; }

  void add_left(TokenKind kind, int prec, ayla::ast::BinaryOperation op) { add(kind, prec, prec + 1, op); }

  void add_right(TokenKind kind, int prec, ayla::ast::BinaryOperation op) { add(kind, prec, prec - 1, op); }

  bool has(TokenKind kind) const { return table.contains(kind); }

  const OperatorInfo *get(TokenKind kind) const {
    auto it = table.find(kind);
    if (it == table.end()) return nullptr;

    return &it->second;
  }

private:
  std::unordered_map<TokenKind, OperatorInfo> table;
};

} // namespace core::table
