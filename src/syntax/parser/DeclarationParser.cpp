#include "DeclarationParser.hpp"
#include "ExpressionParser.hpp"
#include "NameParser.hpp"
#include "Parser.hpp"
#include "ParserContext.hpp"
#include "PatternParser.hpp"
#include "StatementParser.hpp"
#include "TypeParser.hpp"

#include "ast/AstNode.hpp"
#include "ast/StatementNode.hpp"
#include "ast/declarations/FunctionDeclarationNode.hpp"
#include "ast/declarations/ModuleDeclarationNode.hpp"
#include "ast/declarations/VariableDeclarationNode.hpp"
#include "ast/statements/BlockStatementNode.hpp"
#include "core/token/Token.hpp"
#include "core/token/token_stream.hpp"
#include "syntax/parser/ParserUtil.hpp"

DeclarationParser::DeclarationParser(ParseContext &context, Parser &parser) : context(context), parser(parser) {}

ayla::ast::StatementNode *DeclarationParser::parse_declaration() {
  auto specifiers = parse_specifiers();

  auto &tokens = context.tokens();

  switch (tokens.peek()->descriptor->kind) {
  case TokenKind::MODULE_KEYWORD:
    return parse_module();

    // case TokenKind::FUNCTION_KEYWORD: return parse_function(specifiers);

  case TokenKind::VALUE_KEYWORD: return parse_variable(specifiers);

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

ayla::ast::DeclarationNode *DeclarationParser::parse_variable(DeclarationSpecifiers specifiers) {

  auto &tokens = context.tokens();

  if (!tokens.match(TokenKind::VALUE_KEYWORD)) return nullptr;

  auto *pattern = parser.patterns().parse_pattern();

  if (!pattern) return nullptr;

  ayla::ast::ExpressionNode *initializer = nullptr;

  if (tokens.match(TokenKind::ASSIGN)) { initializer = parser.expressions().parse_expression(); }

  return context.ast().create_node<ayla::ast::node::VariableDeclarationNode>(pattern, initializer, specifiers);

  return nullptr;
}

ayla::ast::DeclarationNode *DeclarationParser::parse_function(DeclarationSpecifiers specifiers) {

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
      // context.report_error(DiagnosticCode::ExpectedType, "return type");

      return nullptr;
    }
  }

  ayla::ast::node::BlockStatementNode *body = nullptr;

  if (!specifiers.modifiers.has(Modifier::Extern)) {
    body = parser.statements().parse_block();

    if (body && body->flags.has(NodeFlags::HasError)) { return nullptr; }
  }

  return context.ast().create_node<ayla::ast::node::FunctionDeclarationNode>(name, std::move(params), return_type, body, specifiers);
}

ayla::ast::DeclarationNode *DeclarationParser::parse_module() {

  auto &tokens = context.tokens();

  if (!tokens.match(TokenKind::MODULE_KEYWORD)) return nullptr;

  auto *name = parser.names().parse_qualified_name();

  if (!name) return nullptr;

  if (!tokens.match(TokenKind::OPEN_BRACE)) return nullptr;

  std::vector<ayla::ast::AstNode *> body;

  while (!tokens.is_end() && !tokens.match(TokenKind::CLOSE_BRACE)) {
    auto *node = parser.declarations().parse_declaration();

    if (node) body.push_back(node);
  }

  return context.ast().create_node<ayla::ast::node::ModuleDeclarationNode>(name, std::move(body));
}
