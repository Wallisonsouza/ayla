#pragma once

#include "ast/StatementNode.hpp"
#include "ast/declarations/DeclarationNode.hpp"
#include "ast/declarations/ModuleDeclarationNode.hpp"
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

  ayla::ast::DeclarationNode *parse_variable_declaration(DeclarationSpecifiers);

  ayla::ast::DeclarationNode *parse_function_declaration(DeclarationSpecifiers);

  ayla::ast::node::ModuleDeclarationNode *parse_module_declaration();

  ayla::ast::DeclarationNode *parse_declaration();

  ayla::ast::DeclarationNode *parse_import_declaration();

private:
  ParseContext &context;
  Parser &parser;
};