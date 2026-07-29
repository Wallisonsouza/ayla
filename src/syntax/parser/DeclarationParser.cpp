#include "DeclarationParser.hpp"
#include "ExpressionParser.hpp"
#include "NameParser.hpp"
#include "Parser.hpp"
#include "ParserContext.hpp"
#include "PatternParser.hpp"
#include "StatementParser.hpp"
#include "TypeParser.hpp"

#include "ast/declarations/DeclarationNode.hpp"
#include "ast/declarations/FunctionDeclarationNode.hpp"
#include "ast/declarations/ModuleDeclarationNode.hpp"
#include "ast/declarations/VariableDeclarationNode.hpp"
#include "ast/names/QualifiedNameNode.hpp"
#include "ast/statements/BlockStatementNode.hpp"
#include "ast/statements/ImportStatementNode.hpp"
#include "core/token/Token.hpp"
#include "core/token/TokenKind.hpp"
#include "core/token/token_stream.hpp"
#include "diagnostic/DiagnosticCode.hpp"
#include "diagnostic/Label.hpp"
#include "diagnostic/Severity.hpp"
#include "syntax/parser/ParserUtil.hpp"

DeclarationParser::DeclarationParser(ParseContext &context, Parser &parser) : context(context), parser(parser) {}

ayla::ast::DeclarationNode *DeclarationParser::parse_declaration() {
  auto specifiers = parse_specifiers();

  auto &tokens = context.tokens();

  switch (tokens.peek()->descriptor->kind) {
  case TokenKind::MODULE_KEYWORD: return parse_module_declaration();

  case TokenKind::FUNCTION_KEYWORD: return parse_function_declaration(specifiers);

  case TokenKind::VALUE_KEYWORD: return parse_variable_declaration(specifiers);

  case TokenKind::IMPORT_KEYWORD: return parse_import_declaration();
  default: return nullptr;
  }
}

DeclarationSpecifiers DeclarationParser::parse_specifiers() {

  DeclarationSpecifiers specifiers;

  core::token::TokenStream &tokens = context.tokens();

  while (Token *tok = tokens.peek()) {
    switch (tok->descriptor->kind) {
    case TokenKind::PUBLIC:
      specifiers.visibility = Visibility::Public;
      tokens.advance();
      break;

    case TokenKind::PRIVATE:
      specifiers.visibility = Visibility::Private;
      tokens.advance();
      break;

    case TokenKind::STATIC:
      specifiers.modifiers.add(Modifier::Static);
      tokens.advance();
      break;

    case TokenKind::MUT:
      specifiers.modifiers.add(Modifier::Mut);
      tokens.advance();
      break;

    case TokenKind::CONST:
      specifiers.modifiers.add(Modifier::Const);
      tokens.advance();
      break;

    case TokenKind::EXTERN:
      specifiers.modifiers.add(Modifier::Extern);
      tokens.advance();
      break;

    default: return specifiers;
    }
  }

  return specifiers;
}

ayla::ast::DeclarationNode *DeclarationParser::parse_variable_declaration(DeclarationSpecifiers specifiers) {
  auto &tokens = context.tokens();

  if (!tokens.match(TokenKind::VALUE_KEYWORD)) return nullptr;

  auto *pattern = parser.patterns().parse_pattern();

  if (!pattern) {
    auto current = tokens.current();

    // {
    // .code = DiagnosticCode::ExpectedToken,

    // .expected =
    // {
    //     .token = TokenKind::RIGHT_PAREN
    // },

    // .found =
    // {
    //     .token = TokenKind::LEFT_BRACE
    // }

    // context.diagnostics().report({.severity = diagnostic::Severity::Error,

    //                               .code = diagnostic::DiagnosticCode::ExpectedPattern,

    //                               .expected = {.kind = diagnostic::ExpectedKind::Identifier},

    //                               .found = {.token = current->descriptor->kind},

    //                               .labels = {{.slice = current->slice,

    //                                           .kind = diagnostic::LabelKind::Primary}}});

    // pattern = context.ast()
    //     .create_node<ErrorPatternNode>();
  }

  ayla::ast::ExpressionNode *initializer = nullptr;

  if (tokens.match(TokenKind::ASSIGN)) {
    initializer = parser.expressions().parse_expression();

    if (!initializer) {
      auto current = tokens.current();

      // context.diagnostics().report({.severity = diagnostic::Severity::Error,

      //                               .code = diagnostic::DiagnosticCode::ExpectedExpression,

      //                               .labels = {{.slice = current->slice,

      //                                           .message = "expected expression here",

      //                                           .kind = diagnostic::LabelKind::Primary}}});
    }
  }

  return context.ast().create_node<ayla::ast::node::VariableDeclarationNode>(pattern, initializer, specifiers);
}

ayla::ast::DeclarationNode *DeclarationParser::parse_function_declaration(DeclarationSpecifiers specifiers) {

  auto &tokens = context.tokens();

  if (!tokens.match(TokenKind::FUNCTION_KEYWORD)) return nullptr;

  auto *name = parser.names().parse_name();

  if (!name) return nullptr;

  auto params = ayla::parser::parse_generic_list<ayla::ast::PatternNode>(context, TokenKind::OPEN_PAREN, TokenKind::CLOSE_PAREN, TokenKind::COMMA,

                                                                         [&]() { return parser.patterns().parse_pattern(); });

  ayla::ast::TypeNode *return_type = nullptr;

  if (tokens.match(TokenKind::ARROW)) {
    return_type = parser.types().parse_type();

    if (!return_type) {
      // context.//report_error(DiagnosticCode::ExpectedType, "return type");

      return nullptr;
    }
  }

  ayla::ast::node::BlockStatementNode *body = nullptr;

  if (!specifiers.modifiers.has(Modifier::Extern)) {
    body = parser.statements().parse_block_statement();

    if (body && body->flags.has(NodeFlags::HasError)) { return nullptr; }
  }

  return context.ast().create_node<ayla::ast::node::FunctionDeclarationNode>(name, std::move(params), return_type, body, specifiers);
}

ayla::ast::node::ModuleDeclarationNode *DeclarationParser::parse_module_declaration() {
  ayla::ast::QualifiedNameNode *name = nullptr;

  if (context.tokens().match(TokenKind::MODULE_KEYWORD)) {
    name = parser.names().parse_qualified_name();

    if (!name) return nullptr;
  } else {
    auto *part = context.ast().create_node<ayla::ast::IdentifierNode>(context.unit.source.stem());

    name = context.ast().create_node<ayla::ast::QualifiedNameNode>(std::vector{part});
  }

  return context.ast().create_node<ayla::ast::node::ModuleDeclarationNode>(name);
}

ayla::ast::DeclarationNode *DeclarationParser::parse_import_declaration() {
  auto &tokens = context.tokens();

  if (!tokens.match(TokenKind::IMPORT_KEYWORD)) return nullptr;

  auto *module = parser.names().parse_qualified_name();

  if (!module) return nullptr;

  return context.ast().create_node<ayla::ast::node::ImportDeclarationNode>(module);
}