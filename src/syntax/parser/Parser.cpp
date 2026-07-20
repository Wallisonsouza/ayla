#include "Parser.hpp"

#include "ParserContext.hpp"

#include "DeclarationParser.hpp"
#include "ExpressionParser.hpp"
#include "NameParser.hpp"
#include "PatternParser.hpp"
#include "StatementParser.hpp"
#include "TypeParser.hpp"
#include "ast/declarations/FunctionDeclarationNode.hpp"
#include "ast/names/QualifiedNameNode.hpp"
#include "ast/patterns/PatternNode.hpp"
#include "ast/statements/BlockStatementNode.hpp"
#include "syntax/parser/ParserUtil.hpp"
#include <vector>

Parser::Parser(ParseContext &context) : context(context) {
  declaration_parser = std::make_unique<DeclarationParser>(context, *this);
  expression_parser = std::make_unique<ExpressionParser>(context, *this);
  statement_parser = std::make_unique<StatementParser>(context, *this);
  pattern_parser = std::make_unique<PatternParser>(context, *this);
  type_parser = std::make_unique<TypeParser>(context, *this);
  name_parser = std::make_unique<NameParser>(context, *this);
}

Parser::~Parser() = default;

void Parser::run() {
  ayla::parser::consume_statement_separators(context);

  auto &tokens = context.tokens();

  auto *body = context.ast().create_node<ayla::ast::node::BlockStatementNode>();

  while (!tokens.is_end()) {
    if (auto *decl = declarations().parse_declaration()) {
      context.ast().add_root(decl);
    } else if (auto *stmt = statements().parse_statement()) {
  
      body->statements.push_back(stmt);
    } else {
      // erro de sintaxe
      tokens.advance();
    }

    ayla::parser::consume_statement_separators(context);
  }

  if (!body->statements.empty()) {
    auto *name = context.ast().create_node<ayla::ast::NameNode>("main");

    auto *main = context.ast().create_node<ayla::ast::node::FunctionDeclarationNode>(name, std::vector<ayla::ast::PatternNode *>{}, nullptr, body);

    context.ast().add_root(main);
  }
}