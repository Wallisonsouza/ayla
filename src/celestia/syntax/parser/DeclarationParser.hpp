#pragma once

#include "celestia/ast/declarations/Declaration.hpp"
#include "celestia/ast/declarations/ModuleDeclaration.hpp"
#include "celestia/syntax/parser/DeclarationSpecifiers.hpp"
#include "celestia/syntax/parser/Parser.hpp"

namespace celestia::syntax {
class ParseContext;

class DeclarationParser {

public:
  DeclarationParser(ParseContext &, Parser &);

  DeclarationSpecifiers parse_specifiers();

  ast::Declaration *parse_variable_declaration(DeclarationSpecifiers);

  ast::Declaration *parse_function_declaration(DeclarationSpecifiers);

  ast::ModuleDeclaration *parse_module_declaration();

  ast::Declaration *parse_declaration();

  ast::Declaration *parse_import_declaration();

private:
  ParseContext &context;
  Parser &parser;
};

} // namespace celestia::syntax
