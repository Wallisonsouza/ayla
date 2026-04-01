#include "ayla-syntax/ayla-parser/parser.hpp"

core::ast::TypeNode *Parser::parse_type() {

  auto identifier = parse_identifier();

  if (!identifier) return nullptr;

  std::vector<core::ast::TypeNode *> generic_args;
  return unit.ast.create_node<core::ast::TypeNode>(identifier, generic_args);
}
