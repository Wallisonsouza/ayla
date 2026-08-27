#include "celestia/semantic/resolver/Resolver.hpp"

#include "celestia/ast/types/FunctionType.hpp"
#include "celestia/ast/types/GenericType.hpp"
#include "celestia/ast/types/NamedType.hpp"

#include <iostream>

namespace celestia::semantic {

void Resolver::type_node(ast::TypeNode *node) {

  if (!node) {
    std::cerr << "[Resolver] type_node: null\n";
    return;
  }

  std::cout << "[Resolver] resolving type: " << ast::node_kind_name(node->kind) << '\n';

  switch (node->kind) {

  case ast::NodeKind::NamedType: resolve_named_type(static_cast<ast::NamedType *>(node)); return;

  case ast::NodeKind::GenericType: resolve_generic_type(static_cast<ast::GenericTypeNode *>(node)); return;


  case ast::NodeKind::FunctionType: resolve_function_type(static_cast<ast::FunctionType *>(node)); return;

  default: std::cerr << "[Resolver] unsupported type node: " << ast::node_kind_name(node->kind) << '\n'; return;
  }
}

// ============================================================
// NAMED TYPE
// ============================================================

void Resolver::resolve_named_type(ast::NamedType *node) {

  if (!node || !node->name) return;

  const auto name = node->name->str;

  std::cout << "[Resolver] NamedType: " << name << '\n';

  auto *scope = context.scopes.current();

  if (!scope) {

    std::cerr << "[Resolver] ERROR: no current scope while resolving '" << name << "'\n";

    return;
  }

  SymbolId symbol_id = scope->symbol(name);

  if (!symbol_id.is_valid()) {

    std::cerr << "[Resolver] ERROR: unknown type '" << name << "'\n";

    return;
  }

  std::cout << "[Resolver] found symbol for '" << name << "' -> " << symbol_id.index() << '\n';

  auto *symbol = context.compiler.symbols.get(symbol_id);

  if (!symbol) {

    std::cerr << "[Resolver] ERROR: invalid symbol for '" << name << "'\n";

    return;
  }

  if (symbol->kind != SymbolKind::Type) {

    std::cerr << "[Resolver] ERROR: '" << name << "' is not a type\n";

    return;
  }

  node->symbol_id = symbol_id;

  std::cout << "[Resolver] SUCCESS: '" << name << "' resolved to SymbolId(" << symbol_id.index() << ")\n";
}

// ============================================================
// GENERIC TYPE
// ============================================================

void Resolver::resolve_generic_type(ast::GenericTypeNode *node) {

  if (!node || !node->name) return;

  const auto name = node->name->str;

  std::cout << "[Resolver] GenericType: " << name << "<" << node->arguments.size() << " arguments>\n";

  auto *scope = context.scopes.current();

  if (!scope) {

    std::cerr << "[Resolver] ERROR: no current scope while resolving generic '" << name << "'\n";

    return;
  }

  SymbolId symbol_id = scope->symbol(name);

  if (!symbol_id.is_valid()) {

    std::cerr << "[Resolver] ERROR: unknown generic type '" << name << "'\n";

    return;
  }

  std::cout << "[Resolver] found generic symbol '" << name << "' -> " << symbol_id.index() << '\n';

  auto *symbol = context.compiler.symbols.get(symbol_id);

  if (!symbol) {

    std::cerr << "[Resolver] ERROR: invalid generic symbol '" << name << "'\n";

    return;
  }

  if (symbol->kind != SymbolKind::Type) {

    std::cerr << "[Resolver] ERROR: '" << name << "' does not refer to a type\n";

    return;
  }

  node->symbol_id = symbol_id;

  std::cout << "[Resolver] SUCCESS: generic '" << name << "' resolved\n";

  // Resolve os argumentos.
  for (auto *argument : node->arguments) {

    if (!argument) continue;

    std::cout << "[Resolver] resolving generic argument\n";

    type_node(argument);
  }
}

void Resolver::resolve_function_type(ast::FunctionType *node) {

  if (!node) return;

  std::cout << "[Resolver] FunctionType: " << node->parameters.size() << " parameters\n";

  for (auto *parameter : node->parameters) {

    if (!parameter) continue;

    type_node(parameter);
  }

  if (node->return_type) {

    std::cout << "[Resolver] resolving function return type\n";

    type_node(node->return_type);
  }

  std::cout << "[Resolver] FunctionType resolved\n";
}

} // namespace celestia::semantic