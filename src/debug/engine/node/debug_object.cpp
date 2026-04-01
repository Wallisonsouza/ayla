#include "ast_debug.hpp"
#include "ayla-structural/ayla-ast/literal_nodes.hpp"

void ASTDebug::debug_object_literal(const parser::node::ObjectLiteralNode *node) {
  out << "Object\n";

  if (node->field_list) {
    for (size_t i = 0; i < node->field_list->elements.size(); ++i) {
      bool is_last = (i + 1 == node->field_list->elements.size());
      debug_node(node->field_list->elements[i], is_last);
    }
  }
}

void ASTDebug::debug_object_field(const parser::node::ObjectFieldNode *node) {
  out << "Field\n";

  if (node->key) { debug_node(node->key, false); }

  if (node->value) { debug_node(node->value, true); }
}
