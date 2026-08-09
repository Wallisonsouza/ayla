#include "celestia/ast/expressions/AssignmentExpression.hpp"
#include "celestia/ast/expressions/ExpressionNode.hpp"
#include "celestia/syntax/parser/Parser.hpp"
#include "celestia/syntax/parser/ParserContext.hpp"
#include "celestia/syntax/parser/expressions/Expression.hpp"

namespace celestia::syntax {
celestia::ast::Expression *ExpressionParser::parse_assignment(celestia::ast::Expression *target) {
  auto &tokens = context.tokens();

  if (!tokens.match(TokenKind::ASSIGN)) return nullptr;

  auto *value = parse_expression();

  if (!value) return nullptr;

  return context.get_ast().create_node<celestia::ast::AssignmentExpressionNode>(target, value);
}
}