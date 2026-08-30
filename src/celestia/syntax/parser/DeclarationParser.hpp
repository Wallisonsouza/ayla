#pragma once

#include "celestia/ast/declarations/CapabilityDeclaration.hpp"
#include "celestia/ast/declarations/Declaration.hpp"
#include "celestia/ast/declarations/ImplementationDeclaration.hpp"
#include "celestia/ast/declarations/ModuleDeclaration.hpp"
#include "celestia/ast/declarations/StructDeclaration.hpp"
#include "celestia/ast/declarations/TypeDeclaration.hpp"
#include "celestia/ast/types/NamedType.hpp"
#include "celestia/syntax/parser/DeclarationSpecifiers.hpp"
#include "celestia/syntax/parser/NameParser.hpp"
#include "celestia/syntax/parser/ParseStatus.hpp"
#include "celestia/syntax/parser/Parser.hpp"
#include "celestia/syntax/parser/ParserContext.hpp"
#include <iostream>

namespace celestia::syntax {
class ParseContext;

class DeclarationParser {

public:
  DeclarationParser(ParseContext &, Parser &);

  DeclarationSpecifiers parse_specifiers();

  celestia::ast::Declaration *parse_variable_declaration(DeclarationSpecifiers specifiers);

  ast::FunctionDeclaration *parse_function_declaration(DeclarationSpecifiers specifiers, bool require_body);
  ast::Declaration *parse_capability_declaration(DeclarationSpecifiers specifiers);
  celestia::ast::Declaration *parse_impl_declaration(DeclarationSpecifiers specifiers);
  ast::ModuleDeclaration *parse_module_declaration();

  ast::Declaration *parse_declaration();

  ast::Declaration *parse_import_declaration();
  ast::Declaration *parse_struct_declaration(DeclarationSpecifiers specifiers);
  ast::Declaration *named(DeclarationSpecifiers specifiers);

  ast::FieldDeclaration *_field();

  void synchronize_declaration() {

    auto &tokens = context.tokens();

    std::cout << token_kind_name(tokens.current()->kind());

    while (!tokens.is_end()) {

      if (tokens.check(TokenKind::IDENTIFIER) && tokens.check(TokenKind::COLON, 1)) { return; }

      if (tokens.check(TokenKind::CLOSE_BRACE)) return;

      tokens.consume();
    }
  }

  ast::TypeDeclaration *parse_type_declaration( DeclarationSpecifiers specifiers);

  ast::CapabilityDeclaration *parse_capability_declaration();

  ParseResult<std::vector<ast::PatternNode *>> parse_function_parameters();
  ast::ImplDeclaration *parse_implementation_declaration();

  ast::FunctionDeclaration *parse_member_function();

  ast::FunctionDeclaration *parse_function_signature(ast::IdentifierNode *name, DeclarationSpecifiers specifiers, bool require_body);

  static void report_expected(ParseContext &context, diagnostic::DiagnosticCode code, TokenKind expected) {

    auto &tokens = context.tokens();

    context.unit.diagnostics.report({
        .severity = diagnostic::Severity::Error,
        .code = code,
        .arguments =
            {
                diagnostic::found(tokens.kind()),
                diagnostic::expected(expected),
            },
        .labels =
            {
                diagnostic::location(tokens.diagnostic_slice()),
            },
    });
  }

  static void synchronize_delimited(core::token::TokenStream &tokens, TokenKind close, TokenKind separator) {

    int depth = 0;

    while (!tokens.is_end()) {

      auto kind = tokens.kind();

      if (kind == TokenKind::OPEN_PAREN) {
        ++depth;
        tokens.consume();
        continue;
      }

      if (kind == TokenKind::CLOSE_PAREN) {

        if (depth == 0) return;

        --depth;
        tokens.consume();
        continue;
      }

      if (depth == 0 && kind == separator) return;

      tokens.consume();
    }
  }

  template <typename T, typename Parser>
  syntax::ParseResult<std::vector<T>> parse_delimited_list(syntax::ParseContext &context, TokenKind open, TokenKind close, TokenKind separator, Parser &&parse_element) {

    auto &tokens = context.tokens();
    std::vector<T> elements;

    if (!tokens.match(open)) return syntax::ParseResult<std::vector<T>>::no_match();

    tokens.skip_trivia();

    if (tokens.match(close)) return syntax::ParseResult<std::vector<T>>::ok(std::move(elements));

    while (!tokens.is_end()) {

      auto result = parse_element();

      if (result.is_error()) {
        synchronize_delimited(tokens, close, separator);
        return syntax::ParseResult<std::vector<T>>::fail();
      }

      if (result.is_no_match()) {
        synchronize_delimited(tokens, close, separator);
        return syntax::ParseResult<std::vector<T>>::fail();
      }

      elements.push_back(result.value());

      tokens.skip_trivia();

      if (tokens.match(close)) return syntax::ParseResult<std::vector<T>>::ok(std::move(elements));

      if (!tokens.match(separator)) {

        report_expected(context, diagnostic::DiagnosticCode::ExpectedToken, separator);

        synchronize_delimited(tokens, close, separator);

        return syntax::ParseResult<std::vector<T>>::fail();
      }

      tokens.skip_trivia();

      // trailing comma
      if (tokens.match(close)) return syntax::ParseResult<std::vector<T>>::ok(std::move(elements));
    }

    report_expected(context, diagnostic::DiagnosticCode::ExpectedToken, close);

    return syntax::ParseResult<std::vector<T>>::fail();
  }

private:
  ParseContext &context;
  Parser &parser;
};

} // namespace celestia::syntax
