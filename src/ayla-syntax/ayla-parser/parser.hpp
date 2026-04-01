#pragma once
#include "ayla-compilation/unit.hpp"
#include "ayla-source/source.hpp"
#include "ayla-structural/ayla-ast/literal_nodes.hpp"
#include "ayla-structural/ayla-ast/statement_nodes.hpp"
#include "ayla-structural/ayla-ast/statements/ImportStatement.hpp"

#include "ayla-syntax/ayla-parser/error/recover.hpp"
#include "core/node/Modifier.hpp"
#include "core/node/Type.hpp"

enum class ParserResultCode { Success, Error };

template <typename NodeType> struct ParserResult {
  ParserResultCode code;
  NodeType *node;

  static ParserResult success(NodeType *n) { return ParserResult{ParserResultCode::Success, n}; }

  static ParserResult error() { return ParserResult{ParserResultCode::Error, nullptr}; }
};

struct Parser {
  ayla::compilation::Unit &unit;

  core::ast::TypeNode *parse_type();

private:
  void recover_until(RecoverBoundary boundaries);
  using BoundaryFn = std::function<bool(ayla::structural::token::TokenKind)>;

  void recover_until(BoundaryFn boundary);

  core::ast::ASTExpressionNode *parse_assignment(core::ast::ASTExpressionNode *target);
  core::ast::ASTExpressionNode *parse_call_acess(core::ast::ASTExpressionNode *callee);
  core::ast::ASTExpressionNode *finish_member(core::ast::ASTExpressionNode *base);
  core::ast::ASTExpressionNode *finish_index(core::ast::ASTExpressionNode *base);
  core::ast::Modifiers parse_modifiers();
  std::vector<core::ast::PatternNode *> parse_function_parameters();

  std::vector<core::ast::PatternNode *> parse_parameter_list();

public:
  parser::node::ReturnStatementNode *parse_return_statement();
  core::ast::ASTExpressionNode *parse_path_expression();
  core::ast::ASTExpressionNode *parse_expression();
  core::ast::ASTExpressionNode *parse_postfix_expression();
  core::ast::ASTExpressionNode *parse_primary_expression();
  core::ast::ASTExpressionNode *parse_binary_expression(int min_precedence, core::ast::ASTExpressionNode *lef);
  core::ast::ASTExpressionNode *parse_object_literal();

  core::ast::ASTStatementNode *parse_statement();
  core::ast::ASTStatementNode *parse_import_statement();
  parser::node::ASTArrayLiteralNode *parse_array_literal();

  core::ast::ASTStatementNode *parse_variable_declaration(core::ast::Modifiers modifiers);
  core::ast::ASTStatementNode *parse_function_declaration(core::ast::Modifiers modifiers);
  parser::node::statement::ModuleDeclarationNode *parse_module_declaration();
  core::ast::ASTStatementNode *parse_if_statement();
  parser::node::ASTWhileStatementNode *parse_while_statemente();

  parser::node::BlockStatementNode *parse_block_statement();
  core::ast::PatternNode *parse_function_parameter();

  core::ast::ASTExpressionNode *parse_number_literal();
  core::ast::ASTExpressionNode *parse_string_literal();
  core::ast::IdentifierNode *parse_identifier();
  core::ast::ASTExpressionNode *parse_grouped_expression();
  core::ast::ASTExpressionNode *parse_member_acess(core::ast::ASTExpressionNode *base);
  core::ast::ASTExpressionNode *parse_index_access(core::ast::ASTExpressionNode *base);

  core::ast::PatternNode *parse_pattern(core::ast::Modifiers mods);

  void parse_program() {

    consume_statement_separators();

    while (!unit.tokens.is_end()) {

      auto *stmt = parse_statement();

      if (stmt) { unit.ast.add_root(stmt); }

      consume_statement_separators();
    }
  }

  void consume_statement_separators() { while (unit.tokens.match(ayla::structural::token::TokenKind::NEW_LINE) || unit.tokens.match(ayla::structural::token::TokenKind::SEMI_COLON)); }

  void report_error(DiagnosticCode code, const std::string &expected, const ayla::source::SourceSlice &slice_override = ayla::source::SourceSlice{}) {

    auto *diag = unit.diagns.create(code, unit.tokens.peek_slice());
    diag->set_expected(expected);

    if (auto current = unit.tokens.peek()) { diag->set_found(unit.source.buffer.get_text(current->slice.span)); }
  }

  template <typename ErrorNodeT> ErrorNodeT *make_error(DiagnosticCode code, const std::string &message, const ayla::source::SourceSlice &slice) {
    report_error(code, message);
    recover_until(RecoverBoundary::Function);

    return unit.ast.create_node<ErrorNodeT>(slice);
  }

  template <typename ListNodeType, typename ElementType, typename ParseFunc>
  ListNodeType *
  parse_generic_list(ayla::structural::token::TokenKind open_token, ayla::structural::token::TokenKind close_token, ayla::structural::token::TokenKind separator_token, ParseFunc parse_element) {
    std::vector<ElementType *> elements;

    if (!unit.tokens.match(open_token)) {
      auto desc = unit.context.descriptor_table.lookup_by_kind(open_token);
      report_error(DiagnosticCode::ExpectedToken, desc ? desc->name : "opening token");
      return nullptr;
    }

    bool expect_element = true;

    while (!unit.tokens.is_end()) {
      consume_statement_separators();

      if (unit.tokens.match(close_token)) { return unit.ast.create_node<ListNodeType>(std::move(elements)); }

      auto *current = unit.tokens.peek();
      if (!current) break;

      if (expect_element) {
        auto *el = parse_element(); // agora funciona com qualquer callable

        if (!el || el->flags.has(NodeFlags::HasError)) { return nullptr; }

        elements.push_back(el);
        expect_element = false;
        continue;
      }

      if (unit.tokens.match(separator_token)) {
        expect_element = true;
        continue;
      }

      if (current->descriptor->kind == ayla::structural::token::TokenKind::OPEN_BRACE) {
        report_error(DiagnosticCode::ExpectedToken, "expected closing token before block");
      } else {
        auto sep_desc = unit.context.descriptor_table.lookup_by_kind(separator_token);
        report_error(DiagnosticCode::ExpectedToken, sep_desc ? sep_desc->name : "separator token");
      }

      return nullptr;
    }

    report_error(DiagnosticCode::ExpectedToken, "unterminated list");
    return nullptr;
  }

  ayla::structural::token::Token *expect(ayla::structural::token::TokenKind kind) {
    if (unit.tokens.check(kind)) { return unit.tokens.advance(); }

    report_error(DiagnosticCode::ExpectedToken, "expected token");

    return unit.tokens.advance();
  }
};
