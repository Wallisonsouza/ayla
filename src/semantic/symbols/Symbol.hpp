#pragma once

#include "core/node/Modifier.hpp"
#include <cstddef>
#include <string>

enum class Visibility { Private, Public };
enum class SymbolKind { Type, Function, Variable, Field, Module };

struct Type;

namespace ayla::ast {
struct AstNode;
}

struct Symbol {
  std::string name;
  SymbolKind kind;
  Visibility visibility;
  ayla::ast::Modifiers modifiers;
  bool is_builtin;
  Type *type = nullptr;
  size_t module_id;
  ayla::ast::AstNode *declaration = nullptr;

  Symbol(std::string name, SymbolKind kind, Visibility visibility = Visibility::Private, bool is_builtin = false, ayla::ast::AstNode *decl = nullptr)
      : name(std::move(name)), kind(kind), visibility(visibility), is_builtin(is_builtin), declaration(decl) {}
};
