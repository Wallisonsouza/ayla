#include "celestia/syntax/parser/DeclarationParser.hpp"
#include "celestia/syntax/parser/ParserContext.hpp"

namespace celestia::syntax {

ast::TypeDeclaration *DeclarationParser::parse_type_declaration(DeclarationSpecifiers specifiers) {

  auto &tokens = context.tokens();

  if (!tokens.match(TokenKind::TYPE_KEYWORD)) { return nullptr; }

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

  return context.get_ast().alloc<ast::TypeDeclaration>(name, std::move(generic_parameters.value()), specifiers);
}

} // namespace celestia::syntax