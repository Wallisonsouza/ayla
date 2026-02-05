#include "ast_debug.hpp"

void ASTDebug::debug_index_acess(const ayla::ast::node::IndexAccessNode *node) {

  debug_header("IndexAcess");

  debug_labeled("Base", node->base, false);
  debug_labeled("Index", node->index, true);
}
