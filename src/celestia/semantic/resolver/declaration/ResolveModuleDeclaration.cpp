#include "celestia/ast/declarations/ModuleDeclaration.hpp"
#include "celestia/semantic/resolver/Resolver.hpp"
#include <iostream>

namespace celestia::semantic {

void Resolver::resolve_module_declaration(ast::ModuleDeclaration *node) {

  if (!node) return;

  auto  id = context.unit.module;

  if (!id.is_valid()) throw std::runtime_error("Resolver: module not initialized");

  auto *module = context.compiler.modules.get(id);

  context.scopes.push(module->get_scope());

  for (auto *declaration : node->declarations) {

    if (declaration) resolve(declaration);
  }

  context.scopes.pop();
}


void Resolver::resolve_module_init_declaration(ast::ModuleInitDeclaration *node) {

  if (!node || !node->body) return;

  std::cout << "[Resolver] resolving module init\n";
  std::cout << "[Resolver] module init body = " << node->body << '\n';

  resolve(node->body);

  std::cout << "[Resolver] module init body resolved\n";
}


} // namespace celestia::semantic