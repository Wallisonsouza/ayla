#include "ast_debug.hpp"

void ASTDebug::debug_object_literal(const ayla::ast::node::ObjectLiteralNode *node) {
  out << "Object\n";

  if (!node->fields.empty()) {
    for (size_t i = 0; i < node->fields.size(); ++i) {
      bool is_last = (i + 1 == node->fields.size());
      debug_node(node->fields[i], is_last);
    }
  }
}

void ASTDebug::debug_object_field(const ayla::ast::node::ObjectFieldNode *node) {
  out << "Field\n";

  if (node->key) { debug_node(node->key, false); }

  if (node->value) { debug_node(node->value, true); }
}
