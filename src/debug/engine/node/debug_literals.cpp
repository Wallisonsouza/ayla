#include "ast_debug.hpp"
#include "core/node/Type.hpp"

void ASTDebug::debug_identifier(const ayla::ast::IdentifierNode *node) {

  out << "Identifier";

  if (!node->name.empty()) { out << ": " << node->name; }

  out << "\n";
}

void ASTDebug::debug_number_literal(const ayla::ast::node::NumberLiteralNode *node) { out << "NumberLiteral: " << node->value << "\n"; }

void ASTDebug::debug_string_literal(const ayla::ast::node::StringLiteralNode *node) { out << "StringLiteral: \"" << node->value << "\"\n"; }

void ASTDebug::debug_bool_literal(const ayla::ast::node::BoolLiteralNode *node) { out << "BoolLiteral: " << (node->value ? "true" : "false") << "\n"; }

void ASTDebug::debug_null_literal(const ayla::ast::node::NullLiteralNode *node) {
  (void)node;
  out << "NullLiteral\n";
}
