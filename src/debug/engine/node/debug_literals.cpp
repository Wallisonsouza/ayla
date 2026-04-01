#include "ast_debug.hpp"
#include "ayla-structural/ayla-ast/literal_nodes.hpp"
#include "core/node/Type.hpp"
#include "utils/Utf8.hpp"

void ASTDebug::debug_identifier(const core::ast::IdentifierNode *node) {

  out << "Identifier";

  if (!node->name.empty()) { out << ": " << node->name; }

  out << "\n";
}

void ASTDebug::debug_number_literal(const parser::node::NumberLiteralNode *node) { out << "NumberLiteral: " << node->value << "\n"; }

void ASTDebug::debug_string_literal(const parser::node::StringLiteralNode *node) { out << "StringLiteral: \"" << node->value << "\"\n"; }

void ASTDebug::debug_bool_literal(const parser::node::BoolLiteralNode *node) { out << "BoolLiteral: " << (node->value ? "true" : "false") << "\n"; }

void ASTDebug::debug_char_literal(const parser::node::CharLiteralNode *node) {
  std::string utf8;
  utils::Utf::encode(node->value, utf8);

  out << "CharLiteral: '" << utf8 << "'\n";
}

void ASTDebug::debug_null_literal(const parser::node::NullLiteralNode *node) {
  (void)node;
  out << "NullLiteral\n";
}
