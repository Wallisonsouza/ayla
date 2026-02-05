#include "ast_debug.hpp"

void ASTDebug::debug_import(const ayla::ast::node::ImportStatementNode *node) {
  out << "Import\n";

  size_t count = node->path.size();

  for (size_t i = 0; i < count; ++i) { debug_node(node->path[i], i == count - 1); }
}

void ASTDebug::debug_module_declaration(const ayla::ast::node::ModuleDeclarationNode *node) {
  out << "Module\n";

  for (size_t i = 0; i < node->path.size(); ++i) { debug_node(node->path[i], i == node->path.size() - 1); }

  for (size_t i = 0; i < node->body.size(); ++i) { debug_node(node->body[i], i == node->body.size() - 1); }
}
