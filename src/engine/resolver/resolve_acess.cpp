#include "engine/resolver/Resolver.hpp"

void Resolver::resolve_index_access(parser::node::IndexAccessNode *node) {

  if (node->base) resolve(node->base);

  if (node->index) resolve(node->index);
}

void Resolver::resolve_member_access(parser::node::MemberAccessNode *node) {
  if (!node || !node->base) return;
  resolve(node->base);
}

void Resolver::resolve_function_call(parser::node::FunctionCallNode *node) {

  if (node->callee) resolve(node->callee);

  for (auto *arg : node->arguments) { resolve(arg); }
}