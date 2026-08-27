#include "celestia/syntax/parser/DeclarationParser.hpp"
#include "celestia/syntax/parser/ParserContext.hpp"
#include "celestia/syntax/parser/ParserUtil.hpp"

namespace celestia::syntax {

ast::TypeDeclaration *DeclarationParser::parse_type_declaration(ast::IdentifierNode *name, DeclarationSpecifiers specifiers) {

  auto &tokens = context.tokens();

  if (!tokens.match(TokenKind::TYPE_KEYWORD)) return nullptr;

  auto generic_parameters = parse_generic_parameters();

  return context.get_ast().alloc<ast::TypeDeclaration>(name, std::move(generic_parameters), specifiers);
}

} // namespace celestia::syntax