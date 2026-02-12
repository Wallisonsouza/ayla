#include "core/node/Modifier.hpp"
#include "semantic/resolver/Resolver.hpp"
#include <iostream>

void Resolver::resolve_assignment(ayla::ast::node::AssignmentExpressionNode *node) {

  if (node->target) { resolve(node->target); }

  auto symbol = unit.context.symbol_manager.get(node->target->resolved_symbol_id);

  if (symbol->modifiers.has(ayla::ast::Modifier::Mut)) { std::cout << "aaaaaaaaaaaaaaaa, e mut"; }

  if (node->value) { resolve(node->value); }
}
