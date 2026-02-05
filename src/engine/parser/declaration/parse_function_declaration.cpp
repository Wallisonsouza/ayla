#include "core/node/Modifier.hpp"
#include "core/node/Type.hpp"
#include "core/node/flags.hpp"
#include "core/token/TokenKind.hpp"
#include "engine/parser/node/literal_nodes.hpp"

#include "engine/parser/parser.hpp"

ayla::ast::node::ReturnStatementNode *Parser::parse_return_statement() {

  unit.tokens.match(TokenKind::RETURN_KEYWORD);

  // return sem valor
  if (unit.tokens.peek(TokenKind::CLOSE_BRACE) || unit.tokens.peek(TokenKind::NEW_LINE)) { return unit.ast.create_node<ayla::ast::node::ReturnStatementNode>(nullptr); }

  auto *value = parse_expression();
  if (!value) {
    report_error(DiagnosticCode::ExpectedToken, "expected expression after 'return'");
    unit.tokens.advance();
  }

  return unit.ast.create_node<ayla::ast::node::ReturnStatementNode>(value);
}

ayla::ast::node::BlockStatementNode *Parser::parse_block_statement() {

  std::vector<ayla::ast::StatementNode *> statements;

  if (!unit.tokens.match(TokenKind::OPEN_BRACE)) {

    report_error(DiagnosticCode::ExpectedToken, "'{' to start block");

    return nullptr;
  }

  consume_statement_separators();

  while (!unit.tokens.is_end() && !unit.tokens.peek(TokenKind::CLOSE_BRACE)) {

    auto *stmt = parse_statement();
    if (stmt) {
      statements.push_back(stmt);
    } else {
      unit.tokens.advance();
    }

    consume_statement_separators();
  }

  // '}'
  if (!unit.tokens.match(TokenKind::CLOSE_BRACE)) {

    report_error(DiagnosticCode::ExpectedToken, "'}' to close block");

    return nullptr;
  }

  return unit.ast.create_node<ayla::ast::node::BlockStatementNode>(std::move(statements));
}

ayla::ast::StatementNode *Parser::parse_function_declaration(ayla::ast::Modifiers modifiers) {

  auto start = unit.tokens.peek_slice();

  if (!unit.tokens.match(TokenKind::FUNCTION_KEYWORD)) { return nullptr; }

  auto *name = parse_identifier();
  if (!name) {
    report_error(DiagnosticCode::ExpectedIdentifier, "function name");
    recover_until(RecoverBoundary::Function);
    return nullptr;
  }

  auto param_list =
      parse_generic_list<parser::node::ASTParameterListNode, ayla::ast::PatternNode>(TokenKind::OPEN_PAREN, TokenKind::CLOSE_PAREN, TokenKind::COMMA, [&]() { return parse_pattern({}); });

  if (param_list->flags.has(NodeFlags::HasError)) {
    recover_until(RecoverBoundary::Function);
    return nullptr;
  }

  ayla::ast::TypeNode *return_type = nullptr;

  if (unit.tokens.match(TokenKind::ARROW)) {
    return_type = parse_type();
    if (!return_type) {
      report_error(DiagnosticCode::ExpectedType, "return type");
      recover_until(RecoverBoundary::Function);
      return nullptr;
    }
  }

  ayla::ast::node::BlockStatementNode *body = nullptr;

  if (!modifiers.has(ayla::ast::Modifier::Extern)) {
    body = parse_block_statement();

    if (body->flags.has(NodeFlags::HasError)) {
      recover_until(RecoverBoundary::Function);
      return nullptr;
    }
  }

  return unit.ast.create_node<ayla::ast::node::FunctionDeclarationNode>(name, param_list->elements, return_type, body, modifiers);
}
