#pragma once

#include "celestia/ast/declarations/DeclarationNode.hpp"
#include "celestia/ast/declarations/ModuleDeclarationNode.hpp"
#include "celestia/syntax/parser/DeclarationSpecifiers.hpp"
#include "celestia/syntax/parser/Parser.hpp"



class ParseContext;


class DeclarationParser {

public:
  DeclarationParser(ParseContext &, celestia::Parser &);

  DeclarationSpecifiers parse_specifiers();

  celestia::ast::Declaration *parse_variable_declaration(DeclarationSpecifiers);

  celestia::ast::Declaration *parse_function_declaration(DeclarationSpecifiers);

  celestia::ast::ModuleDeclaration *parse_module_declaration();

  celestia::ast::Declaration *parse_declaration();

  celestia::ast::Declaration *parse_import_declaration();

private:
  ParseContext &context;
  celestia::Parser &parser;
};

