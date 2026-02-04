#pragma once

#include <cstddef>
#include <string>

enum class Visibility { Private, Public };
enum class SymbolKind { Type, Function, Variable, Field, Module };

struct Type;

namespace core::ast {
struct ASTNode;
}

struct Symbol {
  std::string name;
  SymbolKind kind;
  Visibility visibility;
  bool is_builtin;
  Type *type = nullptr;
  size_t module_id;
  core::ast::ASTNode *declaration = nullptr;

  Symbol(std::string name, SymbolKind kind, Visibility visibility = Visibility::Private, bool is_builtin = false, core::ast::ASTNode *decl = nullptr)
      : name(std::move(name)), kind(kind), visibility(visibility), is_builtin(is_builtin), declaration(decl) {}
};
