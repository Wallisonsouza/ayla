#include "Resolver.hpp"
#include "core/node/Modifier.hpp"
#include "engine/parser/node/statement_nodes.hpp"

void Resolver::resolve_function_declaration(parser::node::FunctionDeclarationNode *node) {
  if (!node) return;

  if (current_scope->has_symbol_local(node->identifier->name)) {
    report_error(DiagnosticCode::RedeclaredIdentifier, node->identifier->slice, {{"name", node->identifier->name}});
    return;
  }

  SymbolId sym_id = unit.symbols.create_symbol(node->identifier->name, SymbolKind::Function, Visibility::Public, false, node);

  current_scope->declare(node->identifier->name, sym_id);

  node->symbol_id = sym_id;

  if (node->modifiers.has(core::ast::Modifier::Extern)) return;

  push_scope();

  for (auto *param : node->params) {
    auto name = param->identifier->name;

    SymbolId pid = unit.symbols.create_symbol(name, SymbolKind::Variable, Visibility::Private, false, param);

    current_scope->declare(name, pid);
    param->symbol_id = pid;
  }

  if (node->body) resolve_block(node->body, false);

  pop_scope();
}
