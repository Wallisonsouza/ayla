#include "syntax/parser/parser.hpp"
#include "core/modifiers/Modifier.hpp"
#include "core/modifiers/ModifierSet.hpp"
#include "core/operators/UnaryOperation.hpp"
#include "syntax/parser/DeclarationSpecifiers.hpp"

ayla::ast::node::VariableDeclarationNode *
Parser::parse_variable_declaration(DeclarationSpecifiers specifiers)
{
    if (!unit.tokens.match(TokenKind::VALUE_KEYWORD))
        return nullptr;

    auto *pattern = parse_pattern();

    if (!pattern)
        return nullptr;

    ayla::ast::ExpressionNode *initializer = nullptr;

    if (unit.tokens.match(TokenKind::ASSIGN))
        initializer = parse_expression();

    return unit.ast.create_node<
        ayla::ast::node::VariableDeclarationNode>(
            pattern,
            initializer,
            specifiers);
}


ayla::ast::StatementNode*
Parser::parse_function_declaration(
    DeclarationSpecifiers specifiers)
{
    auto start = unit.tokens.peek_slice();

    if (!unit.tokens.match(TokenKind::FUNCTION_KEYWORD))
        return nullptr;

    auto* name = parse_identifier();

    if (!name)
    {
        report_error(
            DiagnosticCode::ExpectedIdentifier,
            "function name");

        recover_until(RecoverBoundary::Function);

        return nullptr;
    }

    auto params =
        parse_generic_list<ayla::ast::PatternNode>(
            TokenKind::OPEN_PAREN,
            TokenKind::CLOSE_PAREN,
            TokenKind::COMMA,
            [&]()
            {
                return parse_pattern();
            });

    ayla::ast::TypeNode* return_type = nullptr;

    if (unit.tokens.match(TokenKind::ARROW))
    {
        return_type = parse_type();

        if (!return_type)
        {
            report_error(
                DiagnosticCode::ExpectedType,
                "return type");

            recover_until(RecoverBoundary::Function);

            return nullptr;
        }
    }

    ayla::ast::node::BlockStatementNode* body = nullptr;

    if (!specifiers.modifiers.has(Modifier::Extern))
    {
        body = parse_block_statement();

        if (body->flags.has(NodeFlags::HasError))
        {
            recover_until(RecoverBoundary::Function);

            return nullptr;
        }
    }

    return unit.ast.create_node<
        ayla::ast::node::FunctionDeclarationNode>(
            name,
            std::move(params),
            return_type,
            body,
            specifiers);
}

DeclarationSpecifiers Parser::parse_declaration_specifiers()
{
    DeclarationSpecifiers specifiers;

    while (auto *tok = unit.tokens.peek())
    {
        switch (tok->descriptor->kind)
        {
        case TokenKind::PUBLIC:
            specifiers.visibility = Visibility::Public;
            unit.tokens.advance();
            break;

        case TokenKind::PRIVATE:
            specifiers.visibility = Visibility::Private;
            unit.tokens.advance();
            break;

        case TokenKind::STATIC:
            specifiers.modifiers.add(Modifier::Static);
            unit.tokens.advance();
            break;

        case TokenKind::MUT:
            specifiers.modifiers.add(Modifier::Mut);
            unit.tokens.advance();
            break;

        case TokenKind::CONST:
            specifiers.modifiers.add(Modifier::Const);
            unit.tokens.advance();
            break;

        case TokenKind::EXTERN:
            specifiers.modifiers.add(Modifier::Extern);
            unit.tokens.advance();
            break;

        default:
            return specifiers;
        }
    }

    return specifiers;
}

ayla::ast::node::ModuleDeclarationNode *Parser::parse_module_declaration() {

  if (!unit.tokens.match(TokenKind::MODULE_KEYWORD)) return nullptr;

  std::vector<ayla::ast::node::IdentifierExpressionNode *> path;

  auto *id = parse_identifier();
  if (!id) {
    report_error(DiagnosticCode::ExpectedIdentifier, "module name");
    return nullptr;
  }
  path.push_back(id);

  while (unit.tokens.match(TokenKind::DOT)) {
    auto *next_id = parse_identifier();
    if (!next_id) {
      report_error(DiagnosticCode::ExpectedIdentifier, "submodule name after '.'");
      break;
    }
    path.push_back(next_id);
  }

  if (!unit.tokens.match(TokenKind::OPEN_BRACE)) {
    report_error(DiagnosticCode::ExpectedToken, "'{' to start module body");
    return nullptr;
  }

  std::vector<ayla::ast::AstNode *> body;

  while (!unit.tokens.match(TokenKind::CLOSE_BRACE) && !unit.tokens.is_end()) {
    auto *node = parse_statement();
    if (node) body.push_back(node);
  }

  return unit.ast.create_node<ayla::ast::node::ModuleDeclarationNode>(std::move(path), std::move(body));
}

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


ayla::ast::ExpressionNode *Parser::parse_member_acess(ayla::ast::ExpressionNode *base) {

  auto *dot = unit.tokens.match(TokenKind::DOT);
  if (!dot) return nullptr;

  auto *field = parse_identifier();

  if (!field) { return nullptr; }

  return unit.ast.create_node<ayla::ast::node::MemberAccessExpressionNode>(base, field);
}

ayla::ast::ExpressionNode *Parser::parse_index_access(ayla::ast::ExpressionNode *base) {

  auto *open = unit.tokens.match(TokenKind::OPEN_BRACKET);
  if (!open) return nullptr; // erro: '[' esperado

  ayla::ast::ExpressionNode *index_expr = parse_expression();
  if (!index_expr) return nullptr; // erro: expressão esperada dentro de '[]'

  auto *close = unit.tokens.match(TokenKind::CLOSE_BRACKET);
  if (!close) return nullptr; // erro: ']' esperado

  return unit.ast.create_node<ayla::ast::node::IndexAccessNode>(base, index_expr);
}

ayla::ast::ExpressionNode *Parser::parse_call_acess(ayla::ast::ExpressionNode *base) {
  if (!base) return nullptr;

  while (true) {
    auto *tok = unit.tokens.peek();
    if (!tok || tok->descriptor->kind != TokenKind::OPEN_PAREN) break;
    unit.tokens.advance(); // consumir '('

    std::vector<ayla::ast::ExpressionNode *> args;
    while (!unit.tokens.is_end() && !unit.tokens.match(TokenKind::CLOSE_PAREN)) {
      auto *expr = parse_expression();
      if (!expr) break;
      args.push_back(expr);

      if (!unit.tokens.match(TokenKind::COMMA)) {
        unit.tokens.match(TokenKind::CLOSE_PAREN);
        break;
      }
    }

    base = unit.ast.create_node<ayla::ast::node::CallExpressionNode>(base, args);
  }

  return base;
}

ayla::ast::ExpressionNode *Parser::parse_number_literal() {
  Token *token = unit.tokens.match(TokenKind::NUMBER_LITERAL);
  if (!token) return nullptr;

  std::string text = unit.source.buffer.get_text(token->slice.span);
  try {
    double value = std::stod(text);
    return unit.ast.create_node<ayla::ast::node::NumberLiteralNode>(value);
  } catch (const std::exception &) { return nullptr; }
}

ayla::ast::ExpressionNode *Parser::parse_string_literal() {

  Token *token = unit.tokens.match(TokenKind::STRING_LITERAL);
  if (!token) return nullptr;

  std::string text = unit.source.buffer.get_text(token->slice.span);

  return unit.ast.create_node<ayla::ast::node::StringLiteralNode>(text);
}

ayla::ast::ExpressionNode *Parser::parse_bool_literal() {

  Token *token = unit.tokens.advance();
  if (!token) return nullptr;

  bool value = (token->descriptor->kind == TokenKind::TRUE_KEYWORD);

  auto *node = unit.ast.create_node<ayla::ast::node::BoolLiteralNode>(value);
  node->slice = token->slice;

  return node;
}

ayla::ast::ExpressionNode *Parser::parse_object_literal() {

  auto fields = parse_generic_list<ayla::ast::node::ObjectFieldNode>(TokenKind::OPEN_BRACE, TokenKind::CLOSE_BRACE, TokenKind::COMMA, [&]() -> ayla::ast::node::ObjectFieldNode * {
    auto *key = parse_identifier();
    if (!key) return nullptr;

    unit.tokens.expect(TokenKind::COLON);

    auto *value = parse_expression();
    if (!value) return nullptr;

    return unit.ast.create_node<ayla::ast::node::ObjectFieldNode>(key, value);
  });

  if (fields.empty()) return nullptr;

  return unit.ast.create_node<ayla::ast::node::ObjectLiteralNode>(std::move(fields));
}

ayla::ast::ExpressionNode *Parser::parse_assignment(ayla::ast::ExpressionNode *target) {

  if (!unit.tokens.match(TokenKind::ASSIGN)) { return nullptr; }

  auto start = unit.tokens.peek_slice();

  auto *value = parse_expression();

  if (!value) {
    // unit.diagnostics.emit(
    //     {DiagnosticCode::InvalidAssignment, stream.last_slice(), {}}, unit);
    // return nullptr;
  }

  auto node = unit.ast.create_node<ayla::ast::node::AssignmentExpressionNode>(target, value);
  node->slice = start;
  return node;
}

ayla::ast::ExpressionNode *Parser::parse_binary_expression(int min_bp, ayla::ast::ExpressionNode *left) {
  if (!left) return nullptr;

  while (true) {
    auto *tok = unit.tokens.peek();
    if (!tok) break;

    auto info = unit.context.precedence_table.get(tok->descriptor->kind);

    if (!info || info->lbp < min_bp) break;

    unit.tokens.advance();

    auto *right = parse_unary_expression();
    if (!right) return nullptr;

    right = parse_binary_expression(info->rbp, right);

    left = unit.ast.create_node<ayla::ast::node::BinaryExpressionNode>(left, info->op, right);
  }

  return left;
}

ayla::ast::ExpressionNode *Parser::parse_expression() {
  auto *lhs = parse_unary_expression();

  if (!lhs) return nullptr;

  if (auto *assign = parse_assignment(lhs)) return assign;

  return parse_binary_expression(0, lhs);
}

ayla::ast::ExpressionNode *Parser::parse_grouped_expression() {

  auto *open = unit.tokens.match(TokenKind::OPEN_PAREN);
  if (!open) return nullptr;

  ayla::ast::ExpressionNode *expr = parse_expression();
  if (!expr) { return nullptr; }

  auto *close = unit.tokens.match(TokenKind::CLOSE_PAREN);
  if (!close) { return nullptr; }

  return expr;
}

ayla::ast::node::IdentifierExpressionNode *Parser::parse_identifier() {

  Token *token = unit.tokens.match(TokenKind::IDENTIFIER);
  if (!token) return nullptr;

  auto *node = unit.ast.create_node<ayla::ast::node::IdentifierExpressionNode>(unit.source.buffer.get_text(token->slice.span));
  node->slice = token->slice;

  return node;
}

ayla::ast::ExpressionNode *Parser::parse_postfix_expression() {

  auto *expr = parse_primary_expression();
  if (!expr) return nullptr;

  while (true) {
    auto *tok = unit.tokens.peek();
    if (!tok) break;

    switch (tok->descriptor->kind) {

    case TokenKind::OPEN_PAREN:
      expr = parse_call_acess(expr);
      if (!expr) return nullptr;
      break;

    case TokenKind::DOT:
      expr = parse_member_acess(expr);
      if (!expr) return nullptr;
      break;

    case TokenKind::OPEN_BRACKET:
      expr = parse_index_access(expr);
      if (!expr) return nullptr;
      break;

    default: return expr;
    }
  }

  return expr;
}

ayla::ast::ExpressionNode *Parser::parse_primary_expression() {

  auto *tok = unit.tokens.peek();
  if (!tok) return nullptr;

  switch (tok->descriptor->kind) {

  case TokenKind::NUMBER_LITERAL: return parse_number_literal();

  case TokenKind::STRING_LITERAL: return parse_string_literal();

  case TokenKind::IDENTIFIER: return parse_identifier();

  case TokenKind::TRUE_KEYWORD:
  case TokenKind::FALSE_KEYWORD: return parse_bool_literal();

  case TokenKind::OPEN_PAREN: return parse_grouped_expression();

  case TokenKind::OPEN_BRACE: return parse_object_literal();

  case TokenKind::OPEN_BRACKET: return parse_array_literal();

  default: return nullptr;
  }
}

ayla::ast::ExpressionNode *Parser::parse_unary_expression() {
  auto *tok = unit.tokens.peek();
  if (!tok) return parse_postfix_expression();

  UnaryOperation op;

  switch (tok->descriptor->kind) {
  case TokenKind::NOT:
    op = UnaryOperation::Not;
    break;

    // case TokenKind::MINUS: op = UnaryOperation::NEGATE; break;

  default: return parse_postfix_expression();
  }

  unit.tokens.advance();

  auto *operand = parse_unary_expression(); // recursivo!

  return unit.ast.create_node<ayla::ast::node::UnaryExpressionNode>(op, operand);
}

ayla::ast::node::ArrayLiteralNode *Parser::parse_array_literal() {

  auto elements = parse_generic_list<ayla::ast::ExpressionNode>(TokenKind::OPEN_BRACKET, TokenKind::CLOSE_BRACKET, TokenKind::COMMA, [&]() { return parse_expression(); });

  return unit.ast.create_node<ayla::ast::node::ArrayLiteralNode>(std::move(elements));
}

ayla::ast::StatementNode *Parser::parse_import_statement() {

  if (!unit.tokens.match(TokenKind::IMPORT_KEYWORD)) return nullptr;

  std::vector<ayla::ast::node::IdentifierExpressionNode *> path_nodes;

  // primeiro identificador é obrigatório
  auto *name_token = unit.tokens.match(TokenKind::IDENTIFIER);
  if (!name_token) {
    report_error(DiagnosticCode::ExpectedToken, "expected module name after 'import'", unit.tokens.peek_slice());
    return nullptr;
  }

  while (true) {
    auto name = unit.source.buffer.get_text(name_token->slice.span);
    path_nodes.push_back(unit.ast.create_node<ayla::ast::node::IdentifierExpressionNode>(name));

    if (!unit.tokens.match(TokenKind::DOT)) break;

    name_token = unit.tokens.match(TokenKind::IDENTIFIER);
    if (!name_token) {
      report_error(DiagnosticCode::ExpectedToken, "expected identifier after '.' in import path", unit.tokens.peek_slice());
      break;
    }
  }

  auto *node = unit.ast.create_node<ayla::ast::node::ImportStatementNode>(std::move(path_nodes));
  node->slice = unit.tokens.last_slice();
  return node;
}

ayla::ast::StatementNode *Parser::parse_if_statement() {
  if (!unit.tokens.match(TokenKind::IF_KEYWORD)) return nullptr;

  auto *condition = parse_expression();
  if (!condition || condition->flags.has(NodeFlags::HasError)) {

    report_error(DiagnosticCode::ConditionMissing, "expected condition after 'if'");

    recover_until(RecoverBoundary::If);

    return nullptr;
  }

  if (condition->kind == ayla::ast::NodeKind::Assignment) {

    report_error(DiagnosticCode::ConditionAssignment, "assignment is not allowed in if condition");

    recover_until(RecoverBoundary::If);

    return nullptr;
  }

  auto *then_block = parse_block_statement();

  if (then_block->flags.has(NodeFlags::HasError)) {

    report_error(DiagnosticCode::BlockError, "error in then block");

    recover_until(RecoverBoundary::If);

    return nullptr;
  }

  ayla::ast::StatementNode *else_block = nullptr;
  if (unit.tokens.match(TokenKind::ELSE_KEYWORD)) {
    if (unit.tokens.peek(TokenKind::IF_KEYWORD)) {
      else_block = parse_if_statement();
    } else {
      else_block = parse_block_statement();
    }

    if (else_block && else_block->flags.has(NodeFlags::HasError)) {

      report_error(DiagnosticCode::BlockError, "error in else block");

      recover_until(RecoverBoundary::If);

      return nullptr;
    }
  }

  return unit.ast.create_node<ayla::ast::node::IfStatementNode>(condition, then_block, else_block);
}
ayla::ast::StatementNode *Parser::parse_statement() {
  auto specifiers = parse_declaration_specifiers();
  auto *tok = unit.tokens.peek();
  if (!tok) return nullptr;

  switch (tok->descriptor->kind) {
  case TokenKind::MODULE_KEYWORD: return parse_module_declaration();
  case TokenKind::IMPORT_KEYWORD: return parse_import_statement();
  case TokenKind::IF_KEYWORD: return parse_if_statement();
  case TokenKind::WHILE_KEYWORD: return parse_while_statemente();
  case TokenKind::RETURN_KEYWORD: return parse_return_statement();
  case TokenKind::VALUE_KEYWORD:
  case TokenKind::CONST: return parse_variable_declaration(specifiers);
  case TokenKind::FUNCTION_KEYWORD: return parse_function_declaration(specifiers);
  default:
    if (auto *expr = parse_expression()) { return unit.ast.create_node<ayla::ast::node::ExpressionStatementNode>(expr); }
    unit.tokens.advance();
    return nullptr;
  }
}

ayla::ast::TypeNode *Parser::parse_type() {
  auto identifier = parse_identifier();
  if (!identifier) return nullptr;

  std::string type_name = identifier->name;

  std::vector<ayla::ast::TypeNode *> generic_args;
  return unit.ast.create_node<ayla::ast::TypeNode>(type_name, generic_args);
}

ayla::ast::node::WhileStatementNode *Parser::parse_while_statemente() {

  if (!unit.tokens.match(TokenKind::WHILE_KEYWORD)) return nullptr;

  auto *condition = parse_expression();

  if (!condition || condition->flags.has(NodeFlags::HasError)) {

    report_error(DiagnosticCode::ConditionMissing, "expected condition after 'while'");

    recover_until(RecoverBoundary::If);

    return nullptr;
  }

  if (condition->kind == ayla::ast::NodeKind::Assignment) {

    report_error(DiagnosticCode::ConditionAssignment, "assignment is not allowed in if condition");

    recover_until(RecoverBoundary::If);

    return nullptr;
  }

  auto *block = parse_block_statement();

  if (block->flags.has(NodeFlags::HasError)) {

    report_error(DiagnosticCode::BlockError, "error in while block");

    recover_until(RecoverBoundary::If);

    return nullptr;
  }

  return unit.ast.create_node<ayla::ast::node::WhileStatementNode>(condition, block);
}

ayla::ast::PatternNode *Parser::parse_pattern() {
  auto *id = parse_identifier();
  if (!id) return nullptr;

  ayla::ast::TypeNode *type = nullptr;

  if (unit.tokens.match(TokenKind::COLON)) { type = parse_type(); }

  return unit.ast.create_node<ayla::ast::IdentifierPatternNode>(id, type);
}
