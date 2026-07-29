#pragma once

#include "SymbolId.hpp"
#include "SymbolKind.hpp"
#include "core/modifiers/ModifierSet.hpp"
#include "core/modifiers/Visibility.hpp"
#include <string>

struct Type;

namespace ayla::ast {
struct AstNode;

}

struct Symbol {
  SymbolId id;

  std::string name;

  SymbolKind kind;

  Visibility visibility = Visibility::Private;

  ModifierSet modifiers;

  bool is_builtin = false;

  Type *type = nullptr;

  ayla::ast::AstNode *declaration = nullptr;

  Symbol(SymbolId id, std::string name, SymbolKind kind, Visibility visibility, bool builtin, ayla::ast::AstNode *decl)
      : id(id), name(std::move(name)), kind(kind), visibility(visibility), is_builtin(builtin), declaration(decl) {}
};