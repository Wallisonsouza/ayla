#include "AstDumper.hpp"

#include "ast/declarations/FunctionDeclarationNode.hpp"
#include "ast/declarations/ModuleDeclarationNode.hpp"
#include "ast/declarations/VariableDeclarationNode.hpp"

void AstDumper::dump_function_declaration(const ayla::ast::node::FunctionDeclarationNode *node) {
  auto object = context.object("FunctionDeclaration");

  object.field("Name", node->name);
  object.list("Parameters", node->parameters);
  object.field("ReturnType", node->return_type);
  object.field("Body", node->body);
}

void AstDumper::dump_variable_declaration(const ayla::ast::node::VariableDeclarationNode *node) {
  auto object = context.object("VariableDeclaration");

  object.field("Pattern", node->pattern);
  object.field("Initializer", node->initializer);
}

void AstDumper::dump_module_declaration(const ayla::ast::node::ModuleDeclarationNode *node) {
  auto object = context.object("Module");

  object.field("Name", node->name);
  object.list("Declarations", node->declarations);
}

