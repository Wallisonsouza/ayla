
#include "celestia/core/operators/Associativity.hpp"
#include "celestia/language/LanguageDefinition.hpp"
namespace ayla::language {
void register_operators(celestia::LanguageDefinition &def) {
  // prefix
  def.add_prefix_operator(TokenKind::NOT, "!", 30, UnaryOperation::Not);

  // infix
  def.add_infix_operator(TokenKind::PLUS, "+", 10, core::Associativity::Left, BinaryOperation::Add);
  def.add_infix_operator(TokenKind::MINUS, "-", 10, core::Associativity::Left, BinaryOperation::Subtract);
  def.add_infix_operator(TokenKind::STAR, "*", 20, core::Associativity::Left, BinaryOperation::Multiply);
  def.add_infix_operator(TokenKind::SLASH, "/", 20, core::Associativity::Left, BinaryOperation::Divide);
  def.add_infix_operator(TokenKind::ASSIGN, "=", 1, core::Associativity::Right, BinaryOperation::Assign);
  def.add_infix_operator(TokenKind::ARROW, "->", 2, core::Associativity::Right, BinaryOperation::Arrow);
  def.add_infix_operator(TokenKind::EQUAL, "==", 5, core::Associativity::Left, BinaryOperation::Equal);
  def.add_infix_operator(TokenKind::NOT_EQUAL, "!=", 5, core::Associativity::Left, BinaryOperation::NotEqual);
  def.add_infix_operator(TokenKind::LESS, "<", 6, core::Associativity::Left, BinaryOperation::Less);
  def.add_infix_operator(TokenKind::LESS_EQUAL, "<=", 6, core::Associativity::Left, BinaryOperation::LessEqual);
  def.add_infix_operator(TokenKind::GREATER, ">", 6, core::Associativity::Left, BinaryOperation::Greater);
  def.add_infix_operator(TokenKind::GREATER_EQUAL, ">=", 6, core::Associativity::Left, BinaryOperation::GreaterEqual);

  // postfix
  def.add_postfix_operator(TokenKind::OPEN_PAREN, "(", 100, PostfixOperation::Call);
  def.add_postfix_operator(TokenKind::OPEN_BRACKET, "[", 100, PostfixOperation::IndexAccess);
  def.add_postfix_operator(TokenKind::DOT, ".", 100, PostfixOperation::MemberAccess);
}
}