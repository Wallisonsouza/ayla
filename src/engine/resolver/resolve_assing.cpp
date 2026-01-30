#include "debug/console/console.hpp"
#include "engine/parser/node/literal_nodes.hpp"
#include "engine/parser/node/statement/ImportStatement.hpp"
#include "engine/resolver/Resolver.hpp"

void Resolver::resolve_assignment(parser::node::statement::AssignmentNode *node) {

  resolve(node->target);

  resolve(node->value);
}

void Resolver::resolve_array_literal(parser::node::ASTArrayLiteralNode *node) {

  debug::Console::log("resolvendo array");
  for (auto &el : node->elements) { resolve(el); }
}
