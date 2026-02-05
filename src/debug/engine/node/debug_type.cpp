#include "ast_debug.hpp"

void ASTDebug::debug_type(const ayla::ast::TypeNode *node) {
  out << "Type\n";

  debug_node(node->identifier, true);

  size_t count = node->generics.size();
  for (size_t i = 0; i < count; ++i) { debug_node(node->generics[i], i == count - 1); }
}
