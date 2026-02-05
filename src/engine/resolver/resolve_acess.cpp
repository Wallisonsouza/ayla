#include "engine/resolver/Resolver.hpp"

void Resolver::resolve_index_access(ayla::ast::node::IndexAccessNode *node) {

  if (node->base) resolve(node->base);

  if (node->index) resolve(node->index);
}

void Resolver::resolve_member_access(parser::node::MemberAccessNode *node) {

  if (node->base) { resolve(node->base); }

  // if (node->field) { resolve(node->field); }
}

void Resolver::resolve_function_call(ayla::ast::node::CallExpressionNode *node) {

  if (node->callee) resolve(node->callee);

  for (auto *arg : node->arguments) { resolve(arg); }
}