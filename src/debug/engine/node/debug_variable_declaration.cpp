#include "ast_debug.hpp"

void ASTDebug::debug_variable_declaration(const ayla::ast::node::VariableDeclarationNode *node) {

  out << "VariableDeclaration\n";

  std::vector<LabeledChild> children;

  if (node->pattern) children.push_back({"Pattern", node->pattern});

  // if (node->i) children.push_back({"Type", node->i});

  if (node->initializer) children.push_back({"Initializer", node->initializer});

  for (size_t i = 0; i < children.size(); ++i) {

    bool is_last = (i + 1 == children.size());

    debug_labeled(children[i].label, children[i].node, is_last);
  }
}

void ASTDebug::debug_array_literal(const ayla::ast::node::ArrayLiteralNode *node) {
  out << "ArrayLiteral\n";

  for (size_t i = 0; i < node->elements.size(); ++i) {
    bool is_last = (i + 1 == node->elements.size());
    debug_node(node->elements[i], is_last);
  }
}
