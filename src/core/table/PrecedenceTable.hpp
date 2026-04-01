#pragma once

#include "ayla-structural/ayla-token/kind.hpp"
#include <unordered_map>

namespace core::table {

class PrecedenceTable {
public:
  void add(ayla::structural::token::TokenKind kind, int precedence, bool right_assoc = false);

  bool has(ayla::structural::token::TokenKind kind) const;

  int get_precedence(ayla::structural::token::TokenKind kind) const;
  bool is_right_associative(ayla::structural::token::TokenKind kind) const;

private:
  struct OperatorInfo {
    int precedence;
    bool right_assoc;
  };

  std::unordered_map<ayla::structural::token::TokenKind, OperatorInfo> table;
};

} // namespace core::table
