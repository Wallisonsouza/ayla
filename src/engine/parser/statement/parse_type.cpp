#include "engine/parser/parser.hpp"

ayla::ast::TypeNode *Parser::parse_type() {

  auto identifier = parse_identifier();

  if (!identifier) return nullptr;

  std::vector<ayla::ast::TypeNode *> generic_args;
  return unit.ast.create_node<ayla::ast::TypeNode>(identifier, generic_args);
}
