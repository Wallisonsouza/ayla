#include "Resolver.hpp"
#include "celestia/ast/NodeKind.hpp"

#include <iostream>

#include "Resolver.hpp"
#include "celestia/ast/NodeKind.hpp"

#include <iostream>
namespace celestia::semantic {
bool Resolver::can_have_visibility(core::ScopeKind kind, Visibility visibility) {

  if (visibility != Visibility::Public) return true;

  switch (kind) {

  case core::ScopeKind::Module: return true;

  case core::ScopeKind::Capability: return true;

  case core::ScopeKind::Function:
  case core::ScopeKind::Block: return false;

  default: return false;
  }
}
SymbolId Resolver::declare_symbol(const std::string &name, SymbolKind kind, Visibility visibility, celestia::ast::Node *node) {

  auto *scope = context.scopes.current();

  if (!scope) {

    std::cout << "ERRO: nenhum scope ativo ao declarar '" << name << "'\n";

    return SymbolId::invalid();
  }

  if (!can_have_visibility(scope->kind, visibility)) {

    std::cout << "ERRO: simbolo publico '" << name << "' nao permitido neste escopo\n";

    return SymbolId::invalid();
  }

  if (scope->symbols.contains(name)) {

    std::cout << "ERRO: simbolo redeclarado: " << name << '\n';

    return SymbolId::invalid();
  }

  SymbolId id = context.compiler.symbols.create_symbol(name, kind, visibility, false, node);

  if (!id.is_valid()) {

    std::cout << "ERRO: nao foi possivel criar simbolo: " << name << '\n';

    return SymbolId::invalid();
  }

  scope->symbols.insert(name, id);

  if (node) node->symbol_id = id;

  return id;
}

void Resolver::named_pattern(celestia::ast::NamedPattern *pattern, Visibility visibility) {

  if (!pattern || !pattern->name) return;

  const std::string &name = pattern->name->str;

  SymbolId symbol_id = declare_symbol(name, SymbolKind::Variable, visibility, pattern);

  if (!symbol_id.is_valid()) return;

  pattern->symbol_id = symbol_id;

  std::cout << "Resolver: declarou '" << name << "'\n";

  if (pattern->type_annotation) { type_node(pattern->type_annotation); }
}

void Resolver::pattern(celestia::ast::PatternNode *pat, Visibility visibility) {

  if (!pat) return;

  switch (pat->kind) {

  case celestia::ast::NodeKind::NamedPattern: named_pattern(static_cast<celestia::ast::NamedPattern *>(pat), visibility); break;

  default: std::cout << "Pattern nao suportado\n"; break;
  }
}
}