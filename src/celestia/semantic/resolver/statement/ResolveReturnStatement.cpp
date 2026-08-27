#include "celestia/semantic/resolver/Resolver.hpp"

namespace celestia::semantic {

void Resolver::return_statement(celestia::ast::ReturnStatement *node) {

  if (node->value) { resolve(node->value); }
}
} // namespace celestia::semantic