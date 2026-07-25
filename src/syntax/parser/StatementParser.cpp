#include "StatementParser.hpp"

#include "DeclarationParser.hpp"
#include "ExpressionParser.hpp"
#include "NameParser.hpp"
#include "Parser.hpp"
#include "ParserContext.hpp"
#include "ast/statements/IfStatementNode.hpp"
#include "ast/statements/ImportStatementNode.hpp"
#include "ast/statements/WhileStatementNode.hpp"

#include "ast/statements/BlockStatementNode.hpp"
#include "ast/statements/ReturnStatementNode.hpp"

#include "core/token/token_stream.hpp"
#include "syntax/parser/ParserUtil.hpp"
#include <iostream>

StatementParser::StatementParser(ParseContext &context, Parser &parser) : context(context), parser(parser) {}

ayla::ast::StatementNode *StatementParser::parse_statement() {
  auto &tokens = context.tokens();
  


  switch (tokens.peek()->descriptor->kind) {
  case TokenKind::IF_KEYWORD: return parse_if_statement();

  case TokenKind::WHILE_KEYWORD: return parse_while_statement();

  case TokenKind::RETURN_KEYWORD: return parse_return_statement();



  case TokenKind::OPEN_BRACE: return parse_block_statement();

  default: return nullptr;
  }
}

ayla::ast::StatementNode *StatementParser::parse_return_statement() {
  auto &tokens = context.tokens();

  tokens.match(TokenKind::RETURN_KEYWORD);

  // return vazio
  if (tokens.peek(TokenKind::CLOSE_BRACE) || tokens.peek(TokenKind::NEW_LINE)) { return context.ast().create_node<ayla::ast::node::ReturnStatementNode>(nullptr); }

  auto *value = parser.expressions().parse_expression();

  if (!value) return nullptr;

  return context.ast().create_node<ayla::ast::node::ReturnStatementNode>(value);
}

ayla::ast::node::BlockStatementNode *StatementParser::parse_block_statement() {
  auto &tokens = context.tokens();

  if (!tokens.match(TokenKind::OPEN_BRACE)) {
    // context.//report_error(...)
    return nullptr;
  }

  std::vector<ayla::ast::StatementNode *> statements;

  ayla::parser::consume_statement_separators(context);

  while (!tokens.is_end() && !tokens.peek(TokenKind::CLOSE_BRACE)) {

    if (auto *decl_node = parser.declarations().parse_declaration()) {
      statements.push_back(decl_node);
    } else if (auto *stmt_node = parser.statements().parse_statement()) {
      statements.push_back(stmt_node);
    } else {
      // context.//report_error("Comando ou declaração inválida dentro do bloco");
      tokens.advance();
    }

    ayla::parser::consume_statement_separators(context);
  }

  if (!tokens.match(TokenKind::CLOSE_BRACE)) {
    // context.//report_error(...)
    return nullptr;
  }

  return context.ast().create_node<ayla::ast::node::BlockStatementNode>(std::move(statements));
}

ayla::ast::StatementNode *StatementParser::parse_while_statement() {
  auto &tokens = context.tokens();

  if (!tokens.match(TokenKind::WHILE_KEYWORD)) return nullptr;

  auto *condition = parser.expressions().parse_expression();

  if (!condition || condition->flags.has(NodeFlags::HasError)) {
    // context.//report_error(
    //     DiagnosticCode::ConditionMissing,
    //     "expected condition after while"
    // );

    return nullptr;
  }

  if (condition->kind == ayla::ast::NodeKind::Assignment) {
    // context.//report_error(
    //     DiagnosticCode::ConditionAssignment,
    //     "assignment is not allowed in while condition"
    // );

    return nullptr;
  }

  auto *block = parse_block_statement();

  if (!block || block->flags.has(NodeFlags::HasError)) {
    // context.//report_error(
    //     DiagnosticCode::BlockError,
    //     "error in while block"
    // );

    return nullptr;
  }

  return context.ast().create_node<ayla::ast::node::WhileStatementNode>(condition, block);
}

ayla::ast::StatementNode *StatementParser::parse_if_statement() {
  auto &tokens = context.tokens();

  if (!tokens.match(TokenKind::IF_KEYWORD)) return nullptr;

  auto *condition = parser.expressions().parse_expression();

  if (!condition || condition->flags.has(NodeFlags::HasError)) {

    std::cout << "Fatal error: no condition in if statement";
    // context.//report_error(...)
    return nullptr;
  }

  if (condition->kind == ayla::ast::NodeKind::Assignment) {
    // context.//report_error(...)
    return nullptr;
  }

  auto *then_block = parse_block_statement();

  if (!then_block || then_block->flags.has(NodeFlags::HasError)) {
    // erro
    return nullptr;
  }

  ayla::ast::StatementNode *else_block = nullptr;

  if (tokens.match(TokenKind::ELSE_KEYWORD)) {

    if (tokens.peek(TokenKind::IF_KEYWORD)) {
      else_block = parse_if_statement();
    } else {
      else_block = parse_block_statement();
    }

    if (else_block && else_block->flags.has(NodeFlags::HasError)) { return nullptr; }
  }

  return context.ast().create_node<ayla::ast::node::IfStatementNode>(condition, then_block, else_block);
}
