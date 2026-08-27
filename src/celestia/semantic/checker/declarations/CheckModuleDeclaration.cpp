#include "celestia/semantic/checker/TypeChecker.hpp"

namespace celestia::semantic {
void TypeChecker::check_module_declaration(ast::ModuleDeclaration *node) {
  if (!node) return;

  std::cout << "[TypeChecker] checking module";

  if (node->name) std::cout << ": " << node->name->get_name();

  std::cout << '\n';

  for (auto *declaration : node->declarations) {

    if (!declaration) continue;

    check(declaration);
  }

  std::cout << "[TypeChecker] module checked\n";
}

void TypeChecker::check_module_init_declaration(ast::ModuleInitDeclaration *node) {
  if (!node) return;

  std::cout << "[TypeChecker] checking module init\n";

  if (!node->body) return;

  check(node->body);
}
} // namespace celestia::semantic