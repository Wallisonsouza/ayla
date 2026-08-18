
#include "celestia/ast/declarations/CapabilityDeclaration.hpp"
#include "celestia/ast/declarations/FunctionDeclaration.hpp"
#include "celestia/ast/declarations/ModuleDeclaration.hpp"
#include "celestia/ast/declarations/StructDeclaration.hpp"
#include "celestia/ast/declarations/VariableDeclaration.hpp"
#include "celestia/debug/ast/AstDumper.hpp"

namespace celestia::debug {

void AstDumper::dump_impl_declaration(const ast::ImplDeclaration *node) {
  auto object = context.object("ImplDeclaration");

  object.field("Target", node->target);
  object.field("Capability", node->capability);
  object.list("Members", node->members);
}

void AstDumper::dump_capability_declaration(const ast::CapabilityDeclaration *node) {

  auto object = context.object("CapabilityDeclaration");

  object.field("Name", node->name);
  object.list("Members", node->members);
}

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
  auto object = context.object("ModuleDeclaration");

  object.field("Name", node->name);
  object.list("Declarations", node->declarations);
}

void AstDumper::dump_field_declaration(const ast::FieldDeclaration *node) {

  auto object = context.object("FieldDeclaration");

  object.field("Name", node->name);
  object.field("Type", node->type);
}

void AstDumper::dump_struct_declaration(const ast::StructDeclaration *node) {

  auto object = context.object("StructDeclaration");

  object.field("Name", node->name);
  object.list("Compositions", node->compositions);
  object.list("Fields", node->fields);
}

} // namespace celestia::debug
