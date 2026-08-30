
#include "DeclarationParser.hpp"
#include "NameParser.hpp"
#include "Parser.hpp"
#include "ParserContext.hpp"
#include "PatternParser.hpp"
#include "StatementParser.hpp"
#include "TypeParser.hpp"

#include "celestia/ast/declarations/Declaration.hpp"
#include "celestia/ast/declarations/FunctionDeclaration.hpp"
#include "celestia/ast/declarations/ImportDeclaration.hpp"
#include "celestia/ast/declarations/ModuleDeclaration.hpp"
#include "celestia/ast/declarations/StructDeclaration.hpp"
#include "celestia/ast/declarations/VariableDeclaration.hpp"
#include "celestia/ast/names/QualifiedNameNode.hpp"
#include "celestia/ast/patterns/NamedPatternNode.hpp"
#include "celestia/ast/patterns/PatternNode.hpp"
#include "celestia/ast/statements/BlockStatementNode.hpp"
#include "celestia/ast/types/NamedType.hpp"
#include "celestia/core/token/Token.hpp"
#include "celestia/core/token/TokenKind.hpp"
#include "celestia/core/token/token_stream.hpp"
#include "celestia/semantic/resolver/Trace.hpp"
#include "celestia/syntax/parser/ParserUtil.hpp"
#include "celestia/syntax/parser/expressions/Expression.hpp"

namespace celestia::syntax {

DeclarationParser::DeclarationParser(ParseContext &context, Parser &parser) : context(context), parser(parser) {}

celestia::ast::Declaration *DeclarationParser::parse_declaration() {

  auto specifiers = parse_specifiers();

  auto &tokens = context.tokens();

  switch (tokens.kind()) {

  case TokenKind::MODULE_KEYWORD: return parse_module_declaration();

  case TokenKind::IMPORT_KEYWORD: return parse_import_declaration();

  case TokenKind::FUN_KEYWORD: return parse_function_declaration(specifiers, true);

  case TokenKind::CAP_KEYWORD: return parse_capability_declaration(specifiers);

  case TokenKind::STRUCT_KEYWORD: return parse_struct_declaration(specifiers);

  case TokenKind::IMPL_KEYWORD: return parse_impl_declaration(specifiers);

  case TokenKind::TYPE_KEYWORD: return parse_type_declaration(specifiers);

  case TokenKind::LET_KEYWORD:
  case TokenKind::MUT_KEYWORD:
  case TokenKind::CONST_KEYWORD: return parse_variable_declaration(specifiers);

  default: return nullptr;
  }
}

DeclarationSpecifiers DeclarationParser::parse_specifiers() {

  DeclarationSpecifiers specifiers;

  auto &tokens = context.tokens();

  while (Token *tok = tokens.current()) {

    switch (tok->kind()) {

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

    case TokenKind::EXPORT_KEYWORD: tokens.advance(); break;

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

  switch (tokens.kind()) {

  case TokenKind::LET_KEYWORD: tokens.advance(); break;

  case TokenKind::MUT_KEYWORD: tokens.advance(); break;

  case TokenKind::CONST_KEYWORD: tokens.advance(); break;

  default: return nullptr;
  }

  // let x
  auto *name = parser.names().parse_name();

  if (!name) {

    report_expected(context, diagnostic::DiagnosticCode::ExpectedIdentifier, TokenKind::IDENTIFIER);

    return nullptr;
  }

  // let x:
  if (!tokens.match(TokenKind::COLON)) {

    report_expected(context, diagnostic::DiagnosticCode::ExpectedToken, TokenKind::COLON);

    return nullptr;
  }

  // let x: Int
  auto type_result = parser.types().parse_type();

  if (type_result.is_error()) { return nullptr; }

  if (type_result.is_no_match()) {

    // report_expected_type(context);

    return nullptr;
  }

  auto *type = type_result.value();

  ast::Expression *initializer = nullptr;

  // let x: Int = ...
  if (tokens.match(TokenKind::ASSIGN)) {

    initializer = parser.expressions().parse_expression();

    if (!initializer) { return nullptr; }
  }

  auto *pattern = context.get_ast().alloc<ast::NamedPattern>(name, type);

  return context.get_ast().alloc<ast::VariableDeclaration>(pattern, initializer, specifiers);
}

celestia::ast::ModuleDeclaration *DeclarationParser::parse_module_declaration() {

  celestia::ast::QualifiedNameNode *name = nullptr;

  if (context.tokens().match(TokenKind::MODULE_KEYWORD)) {

    name = parser.names().parse_qualified_name();

    if (!name) { return nullptr; }

  } else {

    auto *part = context.get_ast().alloc<celestia::ast::IdentifierNode>(context.unit.source.stem());

    name = context.get_ast().alloc<celestia::ast::QualifiedNameNode>(std::vector{part});
  }

  return context.get_ast().alloc<celestia::ast::ModuleDeclaration>(name);
}

celestia::ast::Declaration *DeclarationParser::parse_import_declaration() {

  auto &tokens = context.tokens();

  if (!tokens.match(TokenKind::IMPORT_KEYWORD)) { return nullptr; }

  auto *module = parser.names().parse_qualified_name();

  if (!module) { return nullptr; }

  return context.get_ast().alloc<celestia::ast::ImportDeclaration>(module);
}

celestia::ast::FieldDeclaration *DeclarationParser::_field() {

  auto &tokens = context.tokens();

  tokens.skip_trivia();

  auto *name = parser.names().parse_name();

  if (!name) { return nullptr; }

  if (!tokens.match(TokenKind::COLON)) { return nullptr; }

  auto type_result = parser.types().parse_type();

  if (type_result.is_error() || type_result.is_no_match()) { return nullptr; }

  auto *type = type_result.value();

  return context.get_ast().alloc<celestia::ast::FieldDeclaration>(name, type);
}

celestia::ast::Declaration *DeclarationParser::parse_struct_declaration(DeclarationSpecifiers specifiers) {

  auto &tokens = context.tokens();

  if (!tokens.match(TokenKind::STRUCT_KEYWORD)) { return nullptr; }

  // struct Point
  auto *name = parser.names().parse_name();

  if (!name) {

    report_expected(context, diagnostic::DiagnosticCode::ExpectedIdentifier, TokenKind::IDENTIFIER);

    return nullptr;
  }

  auto generic_parameters = parse_delimited_list<ast::IdentifierNode *>(context, TokenKind::LESS, TokenKind::GREATER, TokenKind::COMMA, [&]() -> ParseResult<ast::IdentifierNode *> {
    auto *generic = parser.names().parse_name();

    if (!generic) {

      report_expected(context, diagnostic::DiagnosticCode::ExpectedIdentifier, TokenKind::IDENTIFIER);

      return ParseResult<ast::IdentifierNode *>::fail();
    }

    return ParseResult<ast::IdentifierNode *>::ok(generic);
  });

  if (generic_parameters.is_error()) { return nullptr; }

  std::vector<ast::TypeNode *> compositions;

  // struct Point: Type, Type
  if (!tokens.check(TokenKind::OPEN_BRACE)) {

    while (true) {

      auto type_result = parser.types().parse_type();

      if (type_result.is_error() || type_result.is_no_match()) { return nullptr; }

      compositions.push_back(type_result.value());

      if (!tokens.match(TokenKind::COMMA)) { break; }
    }
  }

  // {
  if (!tokens.match(TokenKind::OPEN_BRACE)) { return nullptr; }

  std::vector<ast::FieldDeclaration *> fields;

  while (!tokens.is_end()) {

    tokens.skip_trivia();

    if (tokens.match(TokenKind::CLOSE_BRACE)) { break; }

    auto *field = _field();

    if (!field) { return nullptr; }

    fields.push_back(field);

    tokens.skip_trivia();

    tokens.match(TokenKind::COMMA);
  }

  return context.get_ast().alloc<ast::StructDeclaration>(name, std::move(generic_parameters.value()), std::move(compositions), std::move(fields), specifiers);
}

celestia::ast::Declaration *DeclarationParser::parse_capability_declaration(DeclarationSpecifiers specifiers) {

  auto &tokens = context.tokens();

  debug::trace(debug::Category::Parser, "parsing capability declaration");

  if (!tokens.match(TokenKind::CAP_KEYWORD)) { return nullptr; }

  // cap Add
  auto *name = parser.names().parse_name();

  if (!name) {

    report_expected(context, diagnostic::DiagnosticCode::ExpectedIdentifier, TokenKind::IDENTIFIER);

    return nullptr;
  }

  auto generic_parameters = parse_delimited_list<ast::IdentifierNode *>(context, TokenKind::LESS, TokenKind::GREATER, TokenKind::COMMA, [&]() -> ParseResult<ast::IdentifierNode *> {
    auto *generic = parser.names().parse_name();

    if (!generic) {

      report_expected(context, diagnostic::DiagnosticCode::ExpectedIdentifier, TokenKind::IDENTIFIER);

      return ParseResult<ast::IdentifierNode *>::fail();
    }

    return ParseResult<ast::IdentifierNode *>::ok(generic);
  });

  if (generic_parameters.is_error()) { return nullptr; }

  // {
  if (!tokens.match(TokenKind::OPEN_BRACE)) {

    report_expected(context, diagnostic::DiagnosticCode::ExpectedToken, TokenKind::OPEN_BRACE);

    return nullptr;
  }

  debug::trace(debug::Category::Parser, "capability body started");

  std::vector<celestia::ast::FunctionDeclaration *> members;

  tokens.skip_trivia();

  while (!tokens.is_end()) {

    if (tokens.match(TokenKind::CLOSE_BRACE)) {

      debug::trace(debug::Category::Parser, "capability body ended");

      break;
    }

    // cap Add { fun add(...) }
    auto *function = parse_function_declaration(specifiers, false);

    if (!function) { return nullptr; }

    members.push_back(function);

    tokens.skip_trivia();
  }

  if (tokens.is_end()) {

    context.unit.diagnostics.report({
        .severity = diagnostic::Severity::Error,
        .code = diagnostic::DiagnosticCode::UnexpectedToken,
        .arguments =
            {
                diagnostic::expected(TokenKind::CLOSE_BRACE),
            },
        .labels =
            {
                diagnostic::location(tokens.current()->slice),
            },
    });

    return nullptr;
  }

  debug::trace(debug::Category::Parser, "creating CapabilityDeclaration with {} members", members.size());

  return context.get_ast().alloc<celestia::ast::CapabilityDeclaration>(name, std::move(generic_parameters.value()), std::move(members), specifiers);
}

celestia::ast::Declaration *DeclarationParser::parse_impl_declaration(DeclarationSpecifiers specifiers) {

  auto &tokens = context.tokens();

  if (!tokens.match(TokenKind::IMPL_KEYWORD)) { return nullptr; }

  // impl Int
  auto *target_name = parser.names().parse_name();

  if (!target_name) {
    report_expected(context, diagnostic::DiagnosticCode::ExpectedIdentifier, TokenKind::IDENTIFIER);

    return nullptr;
  }

  auto *target = context.get_ast().alloc<ast::NamedType>(target_name);

  auto generic_parameters = parse_delimited_list<ast::IdentifierNode *>(context, TokenKind::LESS, TokenKind::GREATER, TokenKind::COMMA, [&]() -> ParseResult<ast::IdentifierNode *> {
    auto *generic = parser.names().parse_name();

    if (!generic) {

      report_expected(context, diagnostic::DiagnosticCode::ExpectedIdentifier, TokenKind::IDENTIFIER);

      return ParseResult<ast::IdentifierNode *>::fail();
    }

    return ParseResult<ast::IdentifierNode *>::ok(generic);
  });

  if (generic_parameters.is_error()) { return nullptr; }

  // impl Int: Add
  auto capability_result = parser.types().parse_type();

  if (capability_result.is_error() || capability_result.is_no_match()) {
    // report_expected_type(context);
    return nullptr;
  }

  auto *capability = capability_result.value();

  // {
  if (!tokens.match(TokenKind::OPEN_BRACE)) { return nullptr; }

  std::vector<celestia::ast::FunctionDeclaration *> members;

  tokens.skip_trivia();

  while (!tokens.is_end()) {

    if (tokens.match(TokenKind::CLOSE_BRACE)) { break; }

    // impl Int: Add {
    //     fun add(...) -> Int { ... }
    auto *function = parse_function_declaration(specifiers, true);

    if (!function) { return nullptr; }

    members.push_back(function);

    tokens.skip_trivia();
  }

  return context.get_ast().alloc<celestia::ast::ImplDeclaration>(std::move(generic_parameters.value()), target, capability, std::move(members));
}

} // namespace celestia::syntax
