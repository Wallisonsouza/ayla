#include "celestia/semantic/resolver/Resolver.hpp"
#include <iostream>

namespace celestia::semantic {

void Resolver::resolve_import_declaration(ast::ImportDeclaration *node) {

  auto module_id = context.compiler.modules.find(node->name->get_name());

  if (!module_id.is_valid()) { throw std::runtime_error("module not found: " + node->name->get_name()); }

  auto *module = context.compiler.modules.get(module_id);


  // módulo encontrado
}

} // namespace celestia::semantic