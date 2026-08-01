#include "celestia/core/modifiers/Modifier.hpp"

#include "celestia/semantic/resolver/Resolver.hpp"
#include <iostream>

void Resolver::assignment(celestia::ast::AssignmentExpressionNode *node) {

  if (node->target) { resolve(node->target); }

  auto symbol = context.compiler.symbols.get(node->target->resolved_symbol_id);

  if (symbol->modifiers.has(Modifier::Mut)) { std::cout << "aaaaaaaaaaaaaaaa, e mut"; }

  if (node->value) { resolve(node->value); }
}
