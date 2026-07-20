#include "ast/names/QualifiedNameNode.hpp"
#include "ast_debug.hpp"

void ASTDebug::debug_name(const ayla::ast::NameNode *node) { out << "Name: " << node->str << "\n"; }

void ASTDebug::debug_import(const ayla::ast::node::ImportStatementNode *node) {
  out << "Import\n";

  size_t count = node->name->parts.size();

  for (size_t i = 0; i < count; ++i) { debug_node(node->name->parts[i], i == count - 1); }
}

void ASTDebug::debug_module_declaration(const ayla::ast::node::ModuleDeclarationNode *node) {
  out << "Module\n";

  for (size_t i = 0; i < node->name->parts.size(); ++i) { debug_node(node->name->parts[i], i == node->name->parts.size() - 1); }

  for (size_t i = 0; i < node->body.size(); ++i) { debug_node(node->body[i], i == node->body.size() - 1); }
}
