#include "core/modifiers/Modifier.hpp"

#include "semantic/resolver/Resolver.hpp"
#include <iostream>

void Resolver::assignment(ayla::ast::node::AssignmentExpressionNode *node) {

  if (node->target) { resolve(node->target); }

  auto symbol = context.compiler.symbols.get(node->target->resolved_symbol_id);

  if (symbol->modifiers.has(Modifier::Mut)) { std::cout << "aaaaaaaaaaaaaaaa, e mut"; }

  if (node->value) { resolve(node->value); }
}
