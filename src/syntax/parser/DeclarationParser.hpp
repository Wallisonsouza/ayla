#pragma once

#include "ast/StatementNode.hpp"
#include "ast/declarations/DeclarationNode.hpp"
#include "syntax/parser/DeclarationSpecifiers.hpp"

class ParseContext;
class Parser;

namespace ayla::ast {
class PatternNode;
}

class DeclarationParser {

public:
  DeclarationParser(ParseContext &, Parser &);

  DeclarationSpecifiers parse_specifiers();

  ayla::ast::DeclarationNode *parse_variable(DeclarationSpecifiers);

  ayla::ast::DeclarationNode *parse_function(DeclarationSpecifiers);

  ayla::ast::DeclarationNode *parse_module();

  ayla::ast::StatementNode *parse_declaration();

private:
  ParseContext &context;
  Parser &parser;
};