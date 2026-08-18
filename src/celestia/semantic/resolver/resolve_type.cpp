#include "celestia/semantic/resolver/Resolver.hpp"
namespace celestia::semantic {
void Resolver::type_node(celestia::ast::TypeNode *node) {
  if (!node) return;

  // SymbolId sym_id = current_scope->symbol(node->name);

  // if (!sym_id.is_valid()) {
  //   //report_error(DiagnosticCode::UndeclaredSymbol, node->slice, {{"name", node->name}});
  //   return;
  // }

  // node->symbol_id = sym_id;

  // for (auto *generic : node->generics) { type_node(generic); }
}
}