#include "Resolver.hpp"

void Resolver::resolve_function_declaration(ayla::ast::node::FunctionDeclarationNode *node) {

  // if (!node) return;

  // // --- Bind da função ---
  // if (current_scope->has_symbol_local(node->name->str)) {
  //   //report_error(DiagnosticCode::RedeclaredIdentifier, node->identifier->slice, {{"name", node->identifier->name}});
  //   return;
  // }

  // SymbolId sym_id = unit.context.symbol_manager.create_symbol(node->name->str, SymbolKind::Function, Visibility::Public, false, node);

  // current_scope->symbols.insert(node->name->str, sym_id);
  // node->symbol_id = sym_id;

  // if (node->specifiers.modifiers.has(Modifier::Extern)) return;

  // // --- Escopo da função ---
  // push_scope();

  // // --- Bind dos parâmetros (AGORA PATTERNS) ---
  // for (auto *param : node->parameters) { resolve_pattern(param, node->specifiers.modifiers); }

  // if (node->body) resolve_block(node->body, false);

  // pop_scope();
}
