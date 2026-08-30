#include "celestia/semantic/resolver/Resolver.hpp"
#include <iostream>

namespace celestia::semantic {

void Resolver::resolve_function_declaration(ast::FunctionDeclaration *node) {

  if (!node || !node->name) return;

  const std::string &name = node->name->str;

  SymbolId symbol_id = declare_symbol(name, SymbolKind::Function, node->specifiers.visibility, node);

  if (!symbol_id.is_valid()) return;

  auto *fun_scope = context.scope_manager.create_scope(core::ScopeKind::Function, context.scopes.current());

  if (!fun_scope) {

    std::cout << "ERRO: nao foi possivel criar scope da funcao: " << name << '\n';

    return;
  }

  context.scopes.push(*fun_scope);

  // add<T>

  declare_generics(node->generic_parameters);

  // (a: T, b: T)
  for (auto *param : node->parameters) {

    if (param) pattern(param, Visibility::Private);
  }

  // -> T
  if (node->return_type) resolve(node->return_type);

  // { ... }
  //
  // Extern functions normally have no body.
  if (!node->specifiers.modifiers.has(Modifier::Extern)) {

    if (node->body) block_statement(node->body);
  }

  context.scopes.pop();
}

} // namespace celestia::semantic