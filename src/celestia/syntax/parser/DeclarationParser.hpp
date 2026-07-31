#pragma once

#include "celestia/ast/declarations/DeclarationNode.hpp"
#include "celestia/ast/declarations/ModuleDeclarationNode.hpp"
#include "celestia/syntax/parser/DeclarationSpecifiers.hpp"

class ParseContext;
class Parser;

namespace celestia::ast {
class PatternNode;
}

class DeclarationParser {

public:
  DeclarationParser(ParseContext &, Parser &);

  DeclarationSpecifiers parse_specifiers();

  celestia::ast::DeclarationNode *parse_variable_declaration(DeclarationSpecifiers);

  celestia::ast::DeclarationNode *parse_function_declaration(DeclarationSpecifiers);

  celestia::ast::node::ModuleDeclarationNode *parse_module_declaration();

  celestia::ast::DeclarationNode *parse_declaration();

  celestia::ast::DeclarationNode *parse_import_declaration();

private:
  ParseContext &context;
  Parser &parser;
};