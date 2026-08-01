
#include "celestia/debug/ast/AstDumper.hpp"
#include "celestia/ast/declarations/FunctionDeclarationNode.hpp"
#include "celestia/ast/declarations/ModuleDeclarationNode.hpp"
#include "celestia/ast/declarations/VariableDeclarationNode.hpp"

void AstDumper::dump_function_declaration(const celestia::ast::FunctionDeclarationNode *node) {
  auto object = context.object("FunctionDeclaration");

  object.field("Name", node->name);
  object.list("Parameters", node->parameters);
  object.field("ReturnType", node->return_type);
  object.field("Body", node->body);
}

void AstDumper::dump_variable_declaration(const celestia::ast::VariableDeclarationNode *node) {
  auto object = context.object("VariableDeclaration");

  object.field("Pattern", node->pattern);
  object.field("Initializer", node->initializer);
}

void AstDumper::dump_module_declaration(const celestia::ast::ModuleDeclaration *node) {
  auto object = context.object("Module");

  object.field("Name", node->name);
  object.list("Declarations", node->declarations);
}

