#include "celestia/core/token/TokenKind.hpp"
#include "celestia/language/LanguageDefinition.hpp"
namespace ayla::language {
void register_tokens(celestia::LanguageDefinition &def) {

  // keywords
  def.descriptors.add(TokenKind::IDENTIFIER, TokenGroup::Name);
  def.descriptors.add(TokenKind::TRUE, "true", TokenGroup::Keyword);
  def.descriptors.add(TokenKind::FALSE, "false", TokenGroup::Keyword);

  def.descriptors.add(TokenKind::IF_KEYWORD, "if", TokenGroup::Keyword);
  def.descriptors.add(TokenKind::EXTERN, "extern", TokenGroup::Keyword);
  def.descriptors.add(TokenKind::ELSE_KEYWORD, "else", TokenGroup::Keyword);
  def.descriptors.add(TokenKind::WHILE_KEYWORD, "while", TokenGroup::Keyword);
  def.descriptors.add(TokenKind::RETURN_KEYWORD, "return", TokenGroup::Keyword);

  // decl
  def.descriptors.add(TokenKind::FUN_KEYWORD, "fun", TokenGroup::Keyword);
  def.descriptors.add(TokenKind::STRUCT_KEYWORD, "struct", TokenGroup::Keyword);
  def.descriptors.add(TokenKind::TYPE_KEYWORD, "type", TokenGroup::Keyword);
  def.descriptors.add(TokenKind::CAP_KEYWORD, "cap", TokenGroup::Keyword);
  def.descriptors.add(TokenKind::IMPL_KEYWORD, "impl", TokenGroup::Keyword);

  def.descriptors.add(TokenKind::PUBLIC, "public", TokenGroup::Keyword);
  def.descriptors.add(TokenKind::PRIVATE, "private", TokenGroup::Keyword);

  // var
  def.descriptors.add(TokenKind::STATIC, "static", TokenGroup::Keyword);
  def.descriptors.add(TokenKind::MUT_KEYWORD, "mut", TokenGroup::Keyword);
  def.descriptors.add(TokenKind::LET_KEYWORD, "let", TokenGroup::Keyword);
  def.descriptors.add(TokenKind::CONST_KEYWORD, "const", TokenGroup::Keyword);

  def.descriptors.add(TokenKind::MODULE_KEYWORD, "module", TokenGroup::Keyword);
  def.descriptors.add(TokenKind::IMPORT_KEYWORD, "import", TokenGroup::Keyword);
  def.descriptors.add(TokenKind::EXPORT_KEYWORD, "export", TokenGroup::Keyword);

  // punctuaction
  def.descriptors.add(TokenKind::OPEN_PAREN, "(", TokenGroup::Punctuation);
  def.descriptors.add(TokenKind::COLON, ":", TokenGroup::Punctuation);
  def.descriptors.add(TokenKind::DOT, ".", TokenGroup::Punctuation);
  def.descriptors.add(TokenKind::CLOSE_PAREN, ")", TokenGroup::Punctuation);
  def.descriptors.add(TokenKind::OPEN_BRACE, "{", TokenGroup::Punctuation);
  def.descriptors.add(TokenKind::CLOSE_BRACE, "}", TokenGroup::Punctuation);
  def.descriptors.add(TokenKind::OPEN_BRACKET, "[", TokenGroup::Punctuation);
  def.descriptors.add(TokenKind::CLOSE_BRACKET, "]", TokenGroup::Punctuation);
  def.descriptors.add(TokenKind::SEMI_COLON, ";", TokenGroup::Punctuation);
  def.descriptors.add(TokenKind::COMMA, ",", TokenGroup::Punctuation);
  def.descriptors.add(TokenKind::SINGLE_QUOTE, "\'", TokenGroup::Punctuation);
  def.descriptors.add(TokenKind::NEW_LINE, "\\n", TokenGroup::Whitespace);

  // literals
  def.descriptors.add(TokenKind::NUMBER_LITERAL, TokenGroup::Literal);
  def.descriptors.add(TokenKind::STRING_LITERAL, TokenGroup::Literal);
  def.descriptors.add(TokenKind::CHAR_LITERAL, TokenGroup::Literal);
  def.descriptors.add(TokenKind::NULL_LITERAL, TokenGroup::Literal);
}
} // namespace ayla::language