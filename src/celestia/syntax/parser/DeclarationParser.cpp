#include "DeclarationParser.hpp"
#include "ExpressionParser.hpp"
#include "NameParser.hpp"
#include "Parser.hpp"
#include "ParserContext.hpp"
#include "PatternParser.hpp"
#include "StatementParser.hpp"
#include "TypeParser.hpp"

#include "celestia/ast/NodeState.hpp"
#include "celestia/ast/declarations/Declaration.hpp"
#include "celestia/ast/declarations/FunctionDeclaration.hpp"
#include "celestia/ast/declarations/ModuleDeclaration.hpp"
#include "celestia/ast/declarations/VariableDeclaration.hpp"
#include "celestia/ast/names/QualifiedNameNode.hpp"
#include "celestia/ast/patterns/PatternNode.hpp"
#include "celestia/ast/statements/BlockStatementNode.hpp"
#include "celestia/ast/declarations/ImportDeclaration.hpp"
#include "celestia/core/token/Token.hpp"
#include "celestia/core/token/TokenKind.hpp"
#include "celestia/core/token/token_stream.hpp"
#include "celestia/diagnostic/Diagnostic.hpp"
#include "celestia/diagnostic/DiagnosticCode.hpp"
#include "celestia/diagnostic/Expected.hpp"
#include "celestia/syntax/parser/ParserUtil.hpp"

DeclarationParser::DeclarationParser(ParseContext &context, celestia::Parser &parser) : context(context), parser(parser) {}

celestia::ast::Declaration *DeclarationParser::parse_declaration() {
  auto specifiers = parse_specifiers();

  auto &tokens = context.tokens();

  switch (tokens.peek()->desc->kind) {

  case TokenKind::MODULE_KEYWORD: return parse_module_declaration();

  case TokenKind::FUNCTION_KEYWORD: return parse_function_declaration(specifiers);

  case TokenKind::VALUE_KEYWORD: return parse_variable_declaration(specifiers);

  case TokenKind::IMPORT_KEYWORD: return parse_import_declaration();

  default: return nullptr;
  }
}

DeclarationSpecifiers DeclarationParser::parse_specifiers() {

  DeclarationSpecifiers specifiers;

  auto &tokens = context.tokens();

  while (Token *tok = tokens.peek()) {

    switch (tok->desc->kind) {

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

celestia::ast::Declaration *DeclarationParser::parse_variable_declaration(DeclarationSpecifiers specifiers) {

  auto &tokens = context.tokens();

  if (!tokens.match(TokenKind::VALUE_KEYWORD)) return nullptr;

  auto *pattern = parser.patterns().parse_pattern();

  if (!pattern) {

    auto *current = tokens.current();

    context.report_error({.code = diagnostic::DiagnosticCode::ExpectedIdentifier,
                          .arguments = {diagnostic::expected(diagnostic::ExpectedKind::Identifier), diagnostic::found(current), diagnostic::previous(tokens.previous())},
                          .labels = {{
                              .slice = current->slice,
                          }}});

    return nullptr;
  }

  celestia::ast::Expression *initializer = nullptr;

  if (tokens.match(TokenKind::ASSIGN)) {

    initializer = parser.expressions().parse_expression();

    if (!initializer) {

      auto *current = tokens.current();

      context.report_error({.code = diagnostic::DiagnosticCode::ExpectedExpression,
                            .arguments = {diagnostic::expected(diagnostic::ExpectedKind::Expression), diagnostic::found(current), diagnostic::previous(tokens.previous())},
                            .labels = {{
                                .slice = current->slice,
                            }}});

      return nullptr;
    }
  }

  return context.get_ast().create_node<celestia::ast::VariableDeclaration>(pattern, initializer, specifiers);
}

celestia::ast::Declaration *DeclarationParser::parse_function_declaration(DeclarationSpecifiers specifiers) {

  auto &tokens = context.tokens();

  if (!tokens.match(TokenKind::FUNCTION_KEYWORD)) return nullptr;

  auto *name = parser.names().parse_name();

  if (!name) { return nullptr; }

  auto params =
      ayla::parser::parse_generic_list<celestia::ast::PatternNode>(context, TokenKind::OPEN_PAREN, TokenKind::CLOSE_PAREN, TokenKind::COMMA, [&]() { return parser.patterns().parse_pattern(); });

  celestia::ast::TypeNode *return_type = nullptr;

  if (tokens.match(TokenKind::ARROW)) {

    return_type = parser.types().parse_type();

    if (!return_type) { return nullptr; }
  }

  celestia::ast::BlockStatement *body = nullptr;

  if (!specifiers.modifiers.has(Modifier::Extern)) {

    body = parser.statements().parse_block_statement();

    if (body && body->flags.has(celestia::ast::NodeFlags::HasError)) return nullptr;
  }

  return context.get_ast().create_node<celestia::ast::FunctionDeclaration>(name, std::move(params), return_type, body, specifiers);
}

celestia::ast::ModuleDeclaration *DeclarationParser::parse_module_declaration() {

  celestia::ast::QualifiedNameNode *name = nullptr;

  if (context.tokens().match(TokenKind::MODULE_KEYWORD)) {

    name = parser.names().parse_qualified_name();

    if (!name) { return nullptr; }

  } else {

    auto *part = context.get_ast().create_node<celestia::ast::IdentifierNode>(context.unit.source.stem());

    name = context.get_ast().create_node<celestia::ast::QualifiedNameNode>(std::vector{part});
  }

  return context.get_ast().create_node<celestia::ast::ModuleDeclaration>(name);
}

celestia::ast::Declaration *DeclarationParser::parse_import_declaration() {

  auto &tokens = context.tokens();

  if (!tokens.match(TokenKind::IMPORT_KEYWORD)) return nullptr;

  auto *module = parser.names().parse_qualified_name();

  if (!module) { return nullptr; }

  return context.get_ast().create_node<celestia::ast::ImportDeclaration>(module);
}
