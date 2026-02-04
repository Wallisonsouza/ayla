#include "ast_debug.hpp"

void ASTDebug::debug_if_statement(const parser::node::IfStatementNode *node) {

  out << "If\n";

  std::vector<LabeledChild> children;

  if (node->condition) children.push_back({"Condition", node->condition});

  if (node->then_block) children.push_back({"Then", node->then_block});

  if (node->else_block) children.push_back({"Else", node->else_block});

  for (size_t i = 0; i < children.size(); ++i) {
    bool is_last = (i + 1 == children.size());
    debug_labeled(children[i].label, children[i].node, is_last);
  }
}
