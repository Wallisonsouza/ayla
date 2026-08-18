#pragma once

#include "celestia/ast/declarations/CapabilityDeclaration.hpp"
#include "celestia/ast/declarations/Declaration.hpp"
#include "celestia/ast/declarations/ImplementationDeclaration.hpp"
#include "celestia/ast/declarations/ModuleDeclaration.hpp"
#include "celestia/ast/declarations/StructDeclaration.hpp"
#include "celestia/ast/types/NamedType.hpp"
#include "celestia/syntax/parser/DeclarationSpecifiers.hpp"
#include "celestia/syntax/parser/Parser.hpp"

namespace celestia::syntax {
class ParseContext;

class DeclarationParser {

public:
  DeclarationParser(ParseContext &, Parser &);

  DeclarationSpecifiers parse_specifiers();

  celestia::ast::Declaration *parse_variable_declaration(ast::IdentifierNode *name, DeclarationSpecifiers specifiers);

  ast::FunctionDeclaration *parse_function_declaration(ast::IdentifierNode *name, DeclarationSpecifiers specifiers, bool require_body);
  ast::Declaration *parser_capability_declaration(ast::IdentifierNode *name, DeclarationSpecifiers specifiers);
  celestia::ast::Declaration *parse_impl_declaration(celestia::ast::NamedType *target, DeclarationSpecifiers specifiers);
  ast::ModuleDeclaration *parse_module_declaration();

  ast::Declaration *parse_declaration();

  ast::Declaration *parse_import_declaration();
  ast::Declaration *parser_struct_declaration(ast::IdentifierNode *name, DeclarationSpecifiers specifiers);
  ast::Declaration *named(DeclarationSpecifiers specifiers);

  ast::FieldDeclaration *_field();

  ast::CapabilityDeclaration *parse_capability_declaration();

  ast::ImplDeclaration *parse_implementation_declaration();

  ast::FunctionDeclaration *parse_member_function();

  ast::FunctionDeclaration *parse_function_signature(ast::IdentifierNode *name, DeclarationSpecifiers specifiers, bool require_body);

private:
  ParseContext &context;
  Parser &parser;
};

} // namespace celestia::syntax
