#include "ast_debug.hpp"
#include "ayla-structural/ayla-ast/statement_nodes.hpp"

void ASTDebug::debug_index_acess(const parser::node::IndexAccessNode *node) {

  debug_header("IndexAcess");

  debug_labeled("Base", node->base, false);
  debug_labeled("Index", node->index, true);
}
