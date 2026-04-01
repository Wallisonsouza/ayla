#include "ayla-structural/ayla-ast/operator_nodes.hpp"
#include "ayla-syntax/ayla-parser/parser.hpp"
#include "core/node/BinaryOp.hpp"

core::ast::ASTExpressionNode *Parser::parse_binary_expression(int min_precedence, core::ast::ASTExpressionNode *left) {
  if (!left) return nullptr;

  while (true) {
    auto *tok = unit.tokens.peek();
    if (!tok) break;

    int prec = unit.context.precedence_table.get_precedence(tok->descriptor->kind);
    if (prec < min_precedence) break;

    bool right_assoc = unit.context.precedence_table.is_right_associative(tok->descriptor->kind);

    unit.tokens.advance();

    auto *right = parse_primary_expression();
    if (!right) return nullptr;

    int next_min_prec = right_assoc ? prec : prec + 1;

    while (true) {
      auto *next = unit.tokens.peek();
      if (!next) break;

      int next_prec = unit.context.precedence_table.get_precedence(next->descriptor->kind);

      if (next_prec < next_min_prec) break;

      right = parse_binary_expression(next_min_prec, right);
    }

    core::ast::BinaryOperation op;
    switch (tok->descriptor->kind) {
    case TokenKind::PLUS: op = core::ast::BinaryOperation::Add; break;
    case TokenKind::MINUS: op = core::ast::BinaryOperation::Subtract; break;
    case TokenKind::STAR: op = core::ast::BinaryOperation::Multiply; break;
    case TokenKind::SLASH: op = core::ast::BinaryOperation::Divide; break;
    case TokenKind::EQUAL: op = core::ast::BinaryOperation::Equal; break;
    case TokenKind::LESS: op = core::ast::BinaryOperation::Less; break;
    case TokenKind::LESS_EQUAL: op = core::ast::BinaryOperation::LessEqual; break;
    default: return left;
    }

    left = unit.ast.create_node<parser::node::BinaryExpressionNode>(left, op, right);
  }

  return left;
}
