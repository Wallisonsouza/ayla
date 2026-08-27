#pragma once

#include "SymbolKind.hpp"
#include "celestia/core/ids/Ids.hpp"
#include "celestia/core/modifiers/ModifierSet.hpp"
#include "celestia/core/modifiers/Visibility.hpp"

#include <string>

namespace celestia::ast {
struct Node;

}

struct Symbol {

  SymbolId id;
  ModuleId module;
  TypeId type;
  SymbolKind kind;

  std::string name;

  Visibility visibility = Visibility::Private;

  ModifierSet modifiers;

  celestia::ast::Node *declaration = nullptr;

  Symbol(SymbolId id, std::string name, SymbolKind kind, Visibility visibility, bool builtin, celestia::ast::Node *decl)
      : id(id), name(std::move(name)), kind(kind), visibility(visibility), declaration(decl) {}
};