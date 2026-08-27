#include "celestia/compiler/CompilerEnvironment.hpp"
#include "celestia/semantic/checker/TypeChecker.hpp"
namespace celestia::semantic {

void TypeChecker::number_literal(ast::NumberLiteralNode *node) {

  // if (!node) return;

  // auto *symbol = context.compiler.symbols.get(context.compiler.builtins.int_symbol);

  // if (!symbol || !symbol->type.is_valid()) {
  //   error(node, "int type is not initialized");
  //   return;
  // }

  // node->type_id = symbol->type;
}

void TypeChecker::string_literal(ast::StringLiteralNode *node) {

  // if (!node) return;

  // auto *symbol = context.compiler.symbols.get(context.compiler.builtins.string_symbol);

  // if (!symbol || !symbol->type.is_valid()) {
  //   error(node, "string type is not initialized");
  //   return;
  // }

  // node->type_id = symbol->type;
}

void TypeChecker::boolean_literal(ast::BoolLiteralNode *node) {

  // if (!node) return;

  // auto *symbol = context.compiler.symbols.get(context.compiler.builtins.bool_symbol);

  // if (!symbol || !symbol->type.is_valid()) {
  //   error(node, "bool type is not initialized");
  //   return;
  // }

  // node->type_id = symbol->type;
}

} // namespace celestia::semantic