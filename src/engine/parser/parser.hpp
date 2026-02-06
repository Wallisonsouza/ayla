#pragma once
#include "core/node/Modifier.hpp"
#include "core/token/Location.hpp"
#include "core/token/TokenKind.hpp"
#include "engine/CompilationUnit.hpp"
#include "engine/parser/error/recover.hpp"

#include "frontend/ast/AstNode.hpp"
#include "frontend/ast/expressions/AssignmentExpression.hpp"
#include "frontend/ast/expressions/BinaryExpressionNode.hpp"
#include "frontend/ast/expressions/CallExpressionNode.hpp"
#include "frontend/ast/expressions/IndexAcessExpressionNode.hpp"
#include "frontend/ast/expressions/LiteralExpressionNode.hpp"
#include "frontend/ast/expressions/MemberAccessExpressionNode.hpp"
#include "frontend/ast/statements/ExpressionStatementNode.hpp"
#include "frontend/ast/statements/IfStatementNode.hpp"
#include "frontend/ast/statements/ImportStatementNode.hpp"
#include "frontend/ast/statements/ModuleDeclarationNode.hpp"
#include "frontend/ast/statements/ReturnStatementNodes.hpp"
#include "frontend/ast/statements/VariableDeclarationNode.hpp"
#include "frontend/ast/statements/WhileStatementNode.hpp"

struct Parser {
  CompilationUnit &unit;

  ayla::ast::TypeNode *parse_type();

private:
  void recover_until(RecoverBoundary boundaries);
  using BoundaryFn = std::function<bool(TokenKind)>;

  void recover_until(BoundaryFn boundary);

  ayla::ast::ExpressionNode *parse_assignment(ayla::ast::ExpressionNode *target);
  ayla::ast::ExpressionNode *parse_call_acess(ayla::ast::ExpressionNode *callee);
  ayla::ast::ExpressionNode *finish_member(ayla::ast::ExpressionNode *base);
  ayla::ast::ExpressionNode *finish_index(ayla::ast::ExpressionNode *base);
  ayla::ast::Modifiers parse_modifiers();
  std::vector<ayla::ast::PatternNode *> parse_function_parameters();

  std::vector<ayla::ast::PatternNode *> parse_parameter_list();

public:
  ayla::ast::node::ReturnStatementNode *parse_return_statement();
  ayla::ast::ExpressionNode *parse_path_expression();
  ayla::ast::ExpressionNode *parse_expression();
  ayla::ast::ExpressionNode *parse_postfix_expression();
  ayla::ast::ExpressionNode *parse_primary_expression();
  ayla::ast::ExpressionNode *parse_binary_expression(int min_precedence, ayla::ast::ExpressionNode *lef);
  ayla::ast::ExpressionNode *parse_object_literal();

  ayla::ast::StatementNode *parse_statement();
  ayla::ast::StatementNode *parse_import_statement();
  ayla::ast::node::ArrayLiteralNode *parse_array_literal();

  ayla::ast::node::VariableDeclarationNode *parse_variable_declaration(ayla::ast::Modifiers modifiers);
  ayla::ast::StatementNode *parse_function_declaration(ayla::ast::Modifiers modifiers);
  ayla::ast::node::ModuleDeclarationNode *parse_module_declaration();
  ayla::ast::StatementNode *parse_if_statement();
  ayla::ast::node::WhileStatementNode *parse_while_statemente();

  ayla::ast::node::BlockStatementNode *parse_block_statement();
  ayla::ast::PatternNode *parse_function_parameter();

  ayla::ast::ExpressionNode *parse_number_literal();
  ayla::ast::ExpressionNode *parse_string_literal();
  ayla::ast::node::IdentifierExpressionNode *parse_identifier();
  ayla::ast::ExpressionNode *parse_grouped_expression();
  ayla::ast::ExpressionNode *parse_member_acess(ayla::ast::ExpressionNode *base);
  ayla::ast::ExpressionNode *parse_index_access(ayla::ast::ExpressionNode *base);

  ayla::ast::PatternNode *parse_pattern();

  void parse_program() {

    consume_statement_separators();

    while (!unit.tokens.is_end()) {

      auto *stmt = parse_statement();

      if (stmt) { unit.ast.add_root(stmt); }

      consume_statement_separators();
    }
  }

  void consume_statement_separators() { while (unit.tokens.match(TokenKind::NEW_LINE) || unit.tokens.match(TokenKind::SEMI_COLON)); }

  void report_error(DiagnosticCode code, const std::string &expected, const SourceSlice &slice_override = SourceSlice{}) {

    auto *diag = unit.diagns.create(code, unit.tokens.peek_slice());
    diag->set_expected(expected);

    if (auto current = unit.tokens.peek()) { diag->set_found(unit.source.buffer.get_text(current->slice.span)); }
  }

  template <typename ErrorNodeT> ErrorNodeT *make_error(DiagnosticCode code, const std::string &message, const SourceSlice &slice) {
    report_error(code, message);
    recover_until(RecoverBoundary::Function);

    return unit.ast.create_node<ErrorNodeT>(slice);
  }

  template <typename ElementType, typename ParseFunc> std::vector<ElementType *> parse_generic_list(TokenKind open_token, TokenKind close_token, TokenKind separator_token, ParseFunc parse_element) {

    std::vector<ElementType *> elements;

    if (!unit.tokens.match(open_token)) {
      auto desc = unit.context.descriptor_table.lookup_by_kind(open_token);
      report_error(DiagnosticCode::ExpectedToken, desc ? desc->name : "opening token");
      return {};
    }

    bool expect_element = true;

    while (!unit.tokens.is_end()) {
      consume_statement_separators();

      if (unit.tokens.match(close_token)) { return elements; }

      auto *current = unit.tokens.peek();
      if (!current) break;

      if (expect_element) {
        auto *el = parse_element();

        if (!el || el->flags.has(NodeFlags::HasError)) return {};

        elements.push_back(el);
        expect_element = false;
        continue;
      }

      if (unit.tokens.match(separator_token)) {
        expect_element = true;
        continue;
      }

      auto sep_desc = unit.context.descriptor_table.lookup_by_kind(separator_token);

      report_error(DiagnosticCode::ExpectedToken, sep_desc ? sep_desc->name : "separator token");

      return {};
    }

    report_error(DiagnosticCode::ExpectedToken, "unterminated list");
    return {};
  }

  Token *expect(TokenKind kind) {
    if (unit.tokens.check(kind)) { return unit.tokens.advance(); }

    report_error(DiagnosticCode::ExpectedToken, "expected token");

    return unit.tokens.advance();
  }
};
