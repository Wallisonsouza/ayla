#pragma once

#include "core/node/Modifier.hpp"
#include "core/token/TokenKind.hpp"
#include "engine/CompilationUnit.hpp"
#include "syntax/parser/recovery/recover.hpp"

#include "ayla/syntax/ast/ExpressionNode.hpp"
#include "ayla/syntax/ast/expressions/AssignmentExpression.hpp"
#include "ayla/syntax/ast/expressions/BinaryExpressionNode.hpp"
#include "ayla/syntax/ast/expressions/CallExpressionNode.hpp"
#include "ayla/syntax/ast/expressions/IndexAcessExpressionNode.hpp"
#include "ayla/syntax/ast/expressions/LiteralExpressionNode.hpp"
#include "ayla/syntax/ast/expressions/MemberAccessExpressionNode.hpp"
#include "ayla/syntax/ast/expressions/UnaryExpressionNode.hpp"
#include "ayla/syntax/ast/statements/ExpressionStatementNode.hpp"
#include "ayla/syntax/ast/statements/FunctionDeclarationNode.hpp"
#include "ayla/syntax/ast/statements/IfStatementNode.hpp"
#include "ayla/syntax/ast/statements/ImportStatementNode.hpp"
#include "ayla/syntax/ast/statements/ModuleDeclarationNode.hpp"
#include "ayla/syntax/ast/statements/ReturnStatementNodes.hpp"
#include "ayla/syntax/ast/statements/VariableDeclarationNode.hpp"
#include "ayla/syntax/ast/statements/WhileStatementNode.hpp"

namespace ayla::syntax {
struct Parser {
  CompilationUnit &unit;

  ast::TypeNode *parse_type();

private:
  void recover_until(RecoverBoundary boundaries);
  using BoundaryFn = std::function<bool(TokenKind)>;

  void recover_until(BoundaryFn boundary);

  ast::ExpressionNode *parse_assignment(ast::ExpressionNode *target);
  ast::ExpressionNode *parse_call_acess(ast::ExpressionNode *callee);
  ast::ExpressionNode *finish_member(ast::ExpressionNode *base);
  ast::ExpressionNode *finish_index(ast::ExpressionNode *base);
  ast::Modifiers parse_modifiers();
  std::vector<ast::PatternNode *> parse_function_parameters();

  std::vector<ast::PatternNode *> parse_parameter_list();

public:
  ast::node::ReturnStatementNode *parse_return_statement();
  ast::ExpressionNode *parse_path_expression();
  ast::ExpressionNode *parse_expression();
  ast::ExpressionNode *parse_postfix_expression();
  ast::ExpressionNode *parse_primary_expression();
  ast::ExpressionNode *parse_binary_expression(int min_precedence, ast::ExpressionNode *lef);
  ast::ExpressionNode *parse_object_literal();
  ast::ExpressionNode *parse_unary_expression();

  ast::StatementNode *parse_statement();
  ast::StatementNode *parse_import_statement();
  ast::node::ArrayLiteralNode *parse_array_literal();

  ast::node::VariableDeclarationNode *parse_variable_declaration(ast::Modifiers modifiers);
  ast::StatementNode *parse_function_declaration(ast::Modifiers modifiers);
  ast::node::ModuleDeclarationNode *parse_module_declaration();
  ast::StatementNode *parse_if_statement();
  ast::node::WhileStatementNode *parse_while_statemente();

  ast::node::BlockStatementNode *parse_block_statement();
  ast::PatternNode *parse_function_parameter();

  ast::ExpressionNode *parse_number_literal();
  ast::ExpressionNode *parse_string_literal();
  ast::ExpressionNode *parse_bool_literal();
  ast::node::IdentifierExpressionNode *parse_identifier();
  ast::ExpressionNode *parse_grouped_expression();
  ast::ExpressionNode *parse_member_acess(ast::ExpressionNode *base);
  ast::ExpressionNode *parse_index_access(ast::ExpressionNode *base);

  ast::PatternNode *parse_pattern();

  void parse_program() {

    consume_statement_separators();

    while (!unit.tokens.is_end()) {

      auto *stmt = parse_statement();

      if (stmt) { unit.ast.add_root(stmt); }

      consume_statement_separators();
    }
  }

  void consume_statement_separators() { while (unit.tokens.match(TokenKind::NEW_LINE) || unit.tokens.match(TokenKind::SEMI_COLON)); }

  // void report_error(DiagnosticCode code, const std::string &expected, const SourceSlice &slice_override = SourceSlice{}) {

  //   auto *diag = unit.diagns.create(code, unit.tokens.peek_slice());
  //   diag->set_expected(expected);

  //   if (auto current = unit.tokens.peek()) { diag->set_found(unit.source.buffer.get_text(current->slice.span)); }
  // }

  // template <typename ErrorNodeT> ErrorNodeT *make_error(DiagnosticCode code, const std::string &message, const SourceSlice &slice) {
  //   report_error(code, message);
  //   recover_until(RecoverBoundary::Function);

  //   return unit.ast.create_node<ErrorNodeT>(slice);
  // }

  template <typename ElementType, typename ParseFunc> std::vector<ElementType *> parse_generic_list(TokenKind open_token, TokenKind close_token, TokenKind separator_token, ParseFunc parse_element) {

    std::vector<ElementType *> elements;

    if (!unit.tokens.match(open_token)) {
      auto desc = unit.context.descriptor_table.lookup_by_kind(open_token);
      // report_error(DiagnosticCode::ExpectedToken, desc ? desc->name : "opening token");
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

      // report_error(DiagnosticCode::ExpectedToken, sep_desc ? sep_desc->name : "separator token");

      return {};
    }

    // report_error(DiagnosticCode::ExpectedToken, "unterminated list");
    return {};
  }

  Token *expect(TokenKind kind) {
    if (unit.tokens.check(kind)) { return unit.tokens.advance(); }

    // report_error(DiagnosticCode::ExpectedToken, "expected token");

    return unit.tokens.advance();
  }
};

} // namespace ayla::syntax