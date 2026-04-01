#include "core/table/PrecedenceTable.hpp"

namespace core::table {

void PrecedenceTable::add(ayla::structural::token::TokenKind kind, int precedence, bool right_assoc) { table[kind] = OperatorInfo{precedence, right_assoc}; }

bool PrecedenceTable::has(ayla::structural::token::TokenKind kind) const { return table.find(kind) != table.end(); }

int PrecedenceTable::get_precedence(ayla::structural::token::TokenKind kind) const {
  auto it = table.find(kind);
  if (it == table.end()) return -1;
  return it->second.precedence;
}

bool PrecedenceTable::is_right_associative(ayla::structural::token::TokenKind kind) const {
  auto it = table.find(kind);
  if (it == table.end()) return false;
  return it->second.right_assoc;
}

} // namespace core::table
