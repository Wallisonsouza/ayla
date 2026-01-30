#include "core/node/Type.hpp"
#include "core/node/flags.hpp"
#include "core/token/TokenKind.hpp"
#include "engine/parser/node/literal_nodes.hpp"
#include "engine/parser/node/statement_nodes.hpp"
#include "engine/parser/parser.hpp"

parser::node::ReturnStatementNode *Parser::parse_return_statement() {

  unit.tokens.match(TokenKind::RETURN_KEYWORD);

  // return sem valor
  if (unit.tokens.peek(TokenKind::CLOSE_BRACE) || unit.tokens.peek(TokenKind::NEW_LINE)) { return unit.ast.create_node<parser::node::ReturnStatementNode>(nullptr); }

  auto *value = parse_expression();
  if (!value) {
    report_error(DiagnosticCode::ExpectedToken, "expected expression after 'return'");
    unit.tokens.advance();
  }

  return unit.ast.create_node<parser::node::ReturnStatementNode>(value);
}

//

parser::node::BlockStatementNode *Parser::parse_block_statement() {

  std::vector<core::ast::ASTStatementNode *> statements;

  if (!unit.tokens.match(TokenKind::OPEN_BRACE)) {

    report_error(DiagnosticCode::ExpectedToken, "'{' to start block");

    return unit.ast.create_node<parser::node::BlockStatementNodeError>();
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

    return unit.ast.create_node<parser::node::BlockStatementNodeError>();
  }

  return unit.ast.create_node<parser::node::BlockStatementNode>(std::move(statements));
}

core::ast::ASTStatementNode *Parser::parse_function_declaration() {
  auto start = unit.tokens.peek_slice();

  if (!unit.tokens.match(TokenKind::FUNCTION_KEYWORD)) { return nullptr; }

  auto *name = parse_identifier_name();

  if (!name) {

    report_error(DiagnosticCode::ExpectedIdentifier, "function name");

    recover_until(RecoverBoundary::Function);

    return unit.ast.create_node<parser::node::FunctionErrorNode>(start);
  }

  auto param_list = parse_generic_list<parser::node::ASTParameterListNode, core::ast::PatternNode>(
      // test
      TokenKind::OPEN_PAREN,  // open
      TokenKind::CLOSE_PAREN, // close
      TokenKind::COMMA,       // sep
      [&]() { return parse_pattern({}); });

  if (param_list->flags.has(NodeFlags::HasError)) {

    recover_until(RecoverBoundary::Function);

    return unit.ast.create_node<parser::node::FunctionErrorNode>(start);
  }

  core::ast::TypeNode *return_type = nullptr;

  if (unit.tokens.match(TokenKind::ARROW)) {

    return_type = parse_type();

    if (!return_type) {

      report_error(DiagnosticCode::ExpectedType, "return type");

      recover_until(RecoverBoundary::Function);

      return unit.ast.create_node<parser::node::FunctionErrorNode>(start);
    }
  }

  auto body = parse_block_statement();

  if (body->flags.has(NodeFlags::HasError)) {

    recover_until(RecoverBoundary::Function);

    return unit.ast.create_node<parser::node::FunctionErrorNode>(start);
  }

  return unit.ast.create_node<parser::node::FunctionDeclarationNode>(name, param_list->elements, return_type, body);

  return nullptr;
}