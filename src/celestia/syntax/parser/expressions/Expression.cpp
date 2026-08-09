#include "Expression.hpp"

#include "celestia/ast/expressions/ExpressionNode.hpp"
#include "celestia/syntax/parser/Parser.hpp"
namespace celestia::syntax {
ExpressionParser::ExpressionParser(ParseContext &context, Parser &parser) : context(context), parser(parser) {}

celestia::ast::Expression *ExpressionParser::parse_expression() {
  auto *lhs = parse_unary_expression();

  if (!lhs) return nullptr;

  return parse_binary_expression(0, lhs);
}
}