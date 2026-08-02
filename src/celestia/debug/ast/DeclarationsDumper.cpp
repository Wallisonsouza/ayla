
#include "celestia/ast/declarations/FunctionDeclaration.hpp"
#include "celestia/ast/declarations/ModuleDeclaration.hpp"
#include "celestia/ast/declarations/VariableDeclaration.hpp"
#include "celestia/debug/ast/AstDumper.hpp"

namespace celestia::debug {
void AstDumper::dump_function_declaration(const ast::FunctionDeclaration *node) {
  auto object = context.object("FunctionDeclaration");

  object.field("Name", node->name);
  object.list("Parameters", node->parameters);
  object.field("ReturnType", node->return_type);
  object.field("Body", node->body);
}

void AstDumper::dump_variable_declaration(const ast::VariableDeclaration *node) {
  auto object = context.object("VariableDeclaration");

  object.field("Pattern", node->pattern);
  object.field("Initializer", node->initializer);
}

void AstDumper::dump_module_declaration(const ast::ModuleDeclaration *node) {
  auto object = context.object("Module");

  object.field("Name", node->name);
  object.list("Declarations", node->declarations);
}

} // namespace celestia::debug
