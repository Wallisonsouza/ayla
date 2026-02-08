#include "engine/parser/parser.hpp"

ayla::ast::TypeNode *Parser::parse_type() {
  auto identifier = parse_identifier();
  if (!identifier) return nullptr;

  std::string type_name = identifier->name;

  std::vector<ayla::ast::TypeNode *> generic_args;
  return unit.ast.create_node<ayla::ast::TypeNode>(type_name, generic_args);
}
