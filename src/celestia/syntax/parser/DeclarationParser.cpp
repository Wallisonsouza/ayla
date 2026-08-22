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
#include "celestia/ast/patterns/IdentifierPatternNode.hpp"
#include "celestia/ast/patterns/PatternNode.hpp"
#include "celestia/ast/statements/BlockStatementNode.hpp"
#include "celestia/ast/types/NamedType.hpp"
#include "celestia/core/token/Token.hpp"
#include "celestia/core/token/TokenKind.hpp"
#include "celestia/core/token/token_stream.hpp"
#include "celestia/syntax/parser/ParserUtil.hpp"
#include "celestia/syntax/parser/expressions/Expression.hpp"
#include <iostream>

namespace celestia::syntax {
DeclarationParser::DeclarationParser(ParseContext &context, Parser &parser) : context(context), parser(parser) {}

celestia::ast::Declaration *DeclarationParser::parse_declaration() {

  auto specifiers = parse_specifiers();

  auto &tokens = context.tokens();

  switch (tokens.peek()->kind()) {

  case TokenKind::MODULE_KEYWORD: return parse_module_declaration();

  case TokenKind::IMPORT_KEYWORD: return parse_import_declaration();

  case TokenKind::IDENTIFIER: return named(specifiers);

  default: return nullptr;
  }
}

celestia::ast::Declaration *DeclarationParser::named(DeclarationSpecifiers specifiers) {

  auto *name = parser.names().parse_name();

  if (!name) return nullptr;

  auto &tokens = context.tokens();

  if (!tokens.match(TokenKind::COLON)) return nullptr;

  switch (tokens.peek()->kind()) {

  case TokenKind::CAP_KEYWORD: return parse_capability_declaration(name, specifiers);

  case TokenKind::STRUCT_KEYWORD: return parse_struct_declaration(name, specifiers);

  case TokenKind::IMPL_KEYWORD: {
    auto *target = context.get_ast().alloc<ast::NamedType>(name);

    return parse_impl_declaration(target, specifiers);
  }

  case TokenKind::OPEN_PAREN: return parse_function_declaration(name, specifiers, true);

  default: return parse_variable_declaration(name, specifiers);
  }
}

DeclarationSpecifiers DeclarationParser::parse_specifiers() {

  DeclarationSpecifiers specifiers;

  auto &tokens = context.tokens();

  while (Token *tok = tokens.peek()) {

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

celestia::ast::Declaration *DeclarationParser::parse_variable_declaration(ast::IdentifierNode *name, DeclarationSpecifiers specifiers) {

  auto &tokens = context.tokens();

  auto *type = parser.types().parse_type().value();

  if (!type) return nullptr;

  ast::Expression *initializer = nullptr;

  if (tokens.match(TokenKind::ASSIGN)) {

    initializer = parser.expressions().parse_expression();

    if (!initializer) return nullptr;
  }

  auto *pattern = context.get_ast().alloc<ast::IdentifierPatternNode>(name, type);

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

  if (!tokens.match(TokenKind::IMPORT_KEYWORD)) return nullptr;

  auto *module = parser.names().parse_qualified_name();

  if (!module) { return nullptr; }

  return context.get_ast().alloc<celestia::ast::ImportDeclaration>(module);
}

celestia::ast::FieldDeclaration *DeclarationParser::_field() {

  auto &tokens = context.tokens();

  tokens.skip_trivial();

  auto *name = parser.names().parse_name();

  if (!name) return nullptr;

  if (!tokens.match(TokenKind::COLON)) return nullptr;

  auto *type = parser.types().parse_type().value();

  if (!type) return nullptr;

  return context.get_ast().alloc<celestia::ast::FieldDeclaration>(name, type);
}

ast::FunctionDeclaration *DeclarationParser::parse_function_declaration(ast::IdentifierNode *name, DeclarationSpecifiers specifiers, bool require_body) {

  auto &tokens = context.tokens();

  // (a: int, b: int)
  auto parameters = ayla::parser::parse_generic_list<ast::PatternNode *>(context, TokenKind::OPEN_PAREN, TokenKind::CLOSE_PAREN, TokenKind::COMMA, [&]() { return parser.patterns().parse_pattern(); });

  if (parameters.is_error()) { return nullptr; }

  if (parameters.is_no_match()) { return nullptr; }

  // -> int
  ast::TypeNode *return_type = nullptr;

  if (tokens.match(TokenKind::ARROW)) {

    return_type = parser.types().parse_type().value();

    if (!return_type) { return nullptr; }
  }

  // { ... }
  ast::BlockStatement *body = nullptr;

  if (tokens.check(TokenKind::OPEN_BRACE)) {

    body = parser.statements().parse_block_statement();

    if (!body) { return nullptr; }

  } else if (require_body) {

    return nullptr;
  }

  return context.get_ast().alloc<ast::FunctionDeclaration>(name, std::move(parameters.value()), return_type, body, specifiers);
}

celestia::ast::Declaration *DeclarationParser::parse_struct_declaration(celestia::ast::IdentifierNode *name, DeclarationSpecifiers specifiers) {
  auto &tokens = context.tokens();

  if (!tokens.match(TokenKind::STRUCT_KEYWORD)) return nullptr;

  std::vector<ast::TypeNode *> compositions;

  // Point: struct Type, Type<Generics>
  if (!tokens.check(TokenKind::OPEN_BRACE)) {

    while (true) {

      auto *type = parser.types().parse_type().value();

      if (!type) return nullptr;

      compositions.push_back(type);

      if (!tokens.match(TokenKind::COMMA)) break;
    }
  }

  if (!tokens.match(TokenKind::OPEN_BRACE)) return nullptr;

  std::vector<ast::FieldDeclaration *> fields;

  while (!tokens.is_end()) {

    tokens.skip_trivial();

    if (tokens.match(TokenKind::CLOSE_BRACE)) break;

    auto *field = _field();

    if (!field) return nullptr;

    fields.push_back(field);

    tokens.skip_trivial();

    tokens.match(TokenKind::COMMA);
  }

  return context.get_ast().alloc<ast::StructDeclaration>(name, std::move(compositions), std::move(fields), specifiers);
}

celestia::ast::Declaration *DeclarationParser::parse_capability_declaration(celestia::ast::IdentifierNode *name, DeclarationSpecifiers specifiers) {
  auto &tokens = context.tokens();

  std::cout << "1: capability\n";

  if (!tokens.match(TokenKind::CAP_KEYWORD)) return nullptr;

  std::cout << "2: cap encontrado\n";

  if (!tokens.match(TokenKind::OPEN_BRACE)) return nullptr;

  std::cout << "3: { encontrado\n";

  std::vector<celestia::ast::FunctionDeclaration *> members;

  tokens.skip_trivial();

  while (!tokens.is_end()) {

    std::cout << "4: inicio membro\n";

    if (tokens.match(TokenKind::CLOSE_BRACE)) {
      std::cout << "5: } encontrado\n";
      break;
    }

    auto *member_name = parser.names().parse_name();

    if (!member_name) {
      std::cout << "ERRO: nome do membro\n";
      return nullptr;
    }

    std::cout << "6: nome encontrado\n";

    if (!tokens.match(TokenKind::COLON)) {
      std::cout << "ERRO: esperado ':'\n";
      return nullptr;
    }

    std::cout << "7: ':' encontrado\n";

    auto *function = parse_function_declaration(member_name, specifiers, false);

    if (!function) {
      std::cout << "ERRO: parse_function_declaration\n";
      return nullptr;
    }

    std::cout << "8: function encontrada\n";

    members.push_back(function);

    tokens.skip_trivial();
  }

  std::cout << "9: criando CapabilityDeclaration\n";

  return context.get_ast().alloc<celestia::ast::CapabilityDeclaration>(name, std::move(members), specifiers);
}

celestia::ast::Declaration *DeclarationParser::parse_impl_declaration(celestia::ast::NamedType *target, DeclarationSpecifiers specifiers) {
  auto &tokens = context.tokens();

  // Point: impl
  if (!tokens.match(TokenKind::IMPL_KEYWORD)) return nullptr;

  // Printable
  auto *capability = parser.types().parse_type().value();

  if (!capability) return nullptr;

  // {
  if (!tokens.match(TokenKind::OPEN_BRACE)) return nullptr;

  std::vector<celestia::ast::FunctionDeclaration *> members;

  tokens.skip_trivial();

  while (!tokens.is_end()) {

    // }
    if (tokens.match(TokenKind::CLOSE_BRACE)) break;

    // foo
    auto *member_name = parser.names().parse_name();

    if (!member_name) return nullptr;

    // :
    if (!tokens.match(TokenKind::COLON)) return nullptr;

    // () -> Void
    auto *function = parse_function_declaration(member_name, specifiers, false);

    if (!function) return nullptr;

    members.push_back(function);

    tokens.skip_trivial();
  }

  return context.get_ast().alloc<celestia::ast::ImplDeclaration>(target, capability, std::move(members));
}

} // namespace celestia::syntax
