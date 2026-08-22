#include "StatementParser.hpp"

#include "DeclarationParser.hpp"
#include "Parser.hpp"
#include "ParserContext.hpp"
#include "celestia/ast/statements/ExpressionStatementNode.hpp"
#include "celestia/ast/statements/IfStatementNode.hpp"
#include "celestia/ast/statements/WhileStatementNode.hpp"

#include "celestia/ast/statements/BlockStatementNode.hpp"
#include "celestia/ast/statements/ReturnStatementNode.hpp"

#include "celestia/core/token/token_stream.hpp"
#include "celestia/syntax/parser/ParserUtil.hpp"
#include "celestia/syntax/parser/expressions/Expression.hpp"
namespace celestia::syntax {
StatementParser::StatementParser(ParseContext &context, Parser &parser) : context(context), parser(parser) {}

celestia::ast::Statement *StatementParser::parse_statement() {
  auto &tokens = context.tokens();

  switch (tokens.peek()->desc->kind) {
  case TokenKind::IF_KEYWORD: return parse_if_statement();

  case TokenKind::WHILE_KEYWORD: return parse_while_statement();

  case TokenKind::RETURN_KEYWORD: return parse_return_statement();

  case TokenKind::OPEN_BRACE: return parse_block_statement();

  default: return parse_expression_statement();
  }
}

celestia::ast::Statement *StatementParser::parse_return_statement() {
  auto &tokens = context.tokens();

  tokens.match(TokenKind::RETURN_KEYWORD);

  // return vazio
  if (tokens.peek(TokenKind::CLOSE_BRACE) || tokens.peek(TokenKind::NEW_LINE)) { return context.get_ast().alloc<celestia::ast::ReturnStatement>(nullptr); }

  auto *value = parser.expressions().parse_expression();

  if (!value) return nullptr;

  return context.get_ast().alloc<celestia::ast::ReturnStatement>(value);
}

celestia::ast::BlockStatement *StatementParser::parse_block_statement() {
  auto &tokens = context.tokens();

  if (!tokens.match(TokenKind::OPEN_BRACE)) {
    // context.//report_error(...)
    return nullptr;
  }

  std::vector<celestia::ast::Statement *> statements;

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

  return context.get_ast().alloc<celestia::ast::BlockStatement>(std::move(statements));
}

celestia::ast::Statement *StatementParser::parse_while_statement() {
  auto &tokens = context.tokens();

  if (!tokens.match(TokenKind::WHILE_KEYWORD)) return nullptr;

  auto *condition = parser.expressions().parse_expression();

  if (!condition) {
    // context.//report_error(
    //     DiagnosticCode::ConditionMissing,
    //     "expected condition after while"
    // );

    return nullptr;
  }

  if (condition->kind == celestia::ast::NodeKind::Assignment) {
    // context.//report_error(
    //     DiagnosticCode::ConditionAssignment,
    //     "assignment is not allowed in while condition"
    // );

    return nullptr;
  }

  auto *block = parse_block_statement();

  if (!block ) {
    // context.//report_error(
    //     DiagnosticCode::BlockError,
    //     "error in while block"
    // );

    return nullptr;
  }

  return context.get_ast().alloc<celestia::ast::WhileStatement>(condition, block);
}

celestia::ast::Statement *StatementParser::parse_if_statement() {
  auto &tokens = context.tokens();

  if (!tokens.match(TokenKind::IF_KEYWORD)) return nullptr;

  auto *condition = parser.expressions().parse_expression();

  if (!condition ) {
    // context.//report_error(...)
    return nullptr;
  }

  if (condition->kind == celestia::ast::NodeKind::Assignment) {
    // context.//report_error(...)
    return nullptr;
  }

  auto *then_block = parse_block_statement();

  if (!then_block ) {
    // erro
    return nullptr;
  }

  celestia::ast::Statement *else_block = nullptr;

  if (tokens.match(TokenKind::ELSE_KEYWORD)) {

    if (tokens.peek(TokenKind::IF_KEYWORD)) {
      else_block = parse_if_statement();
    } else {
      else_block = parse_block_statement();
    }

    if (else_block) { return nullptr; }
  }

  return context.get_ast().alloc<celestia::ast::IfStatement>(condition, then_block, else_block);
}

celestia::ast::Statement *StatementParser::parse_expression_statement() {
  auto *expr = parser.expressions().parse_expression();

  if (!expr) return nullptr;

  return context.get_ast().alloc<celestia::ast::ExpressionStatement>(expr);
}

} // namespace celestia::syntax
