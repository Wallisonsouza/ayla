#include "celestia/semantic/checker/TypeChecker.hpp"

namespace celestia::semantic {

void TypeChecker::check_variable_declaration(ast::VariableDeclaration *node) {

  if (!node) return;

  std::cout << "[TypeChecker] checking variable\n";

  if (!node->pattern) {
    error(node, "variable has no pattern");
    return;
  }

  // Initializer
  TypeId initializer_type = TypeId::invalid();

  if (node->initializer) {

    std::cout << "[TypeChecker] checking initializer\n";

    check(node->initializer);

    initializer_type = node->initializer->type_id;

    if (!initializer_type.is_valid()) {
      error(node, "initializer has no valid type");
      return;
    }
  }

  // Pattern
  TypeId variable_type = check_pattern(node->pattern, initializer_type);

  if (!variable_type.is_valid()) return;

  // Resultado
  node->type_id = variable_type;

  std::cout << "[TypeChecker] variable type = " << context.compiler.types.get(variable_type).to_string() << '\n';
}

} // namespace celestia::semantic