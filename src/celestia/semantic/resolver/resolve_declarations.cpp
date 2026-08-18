#include "Resolver.hpp"
#include "celestia/ast/declarations/ModuleDeclaration.hpp"
#include <iostream>
namespace celestia::semantic {
void Resolver::module_declaration(celestia::ast::ModuleDeclaration *node) {

  auto mod = context.compiler.modules.register_module(node->name->get_name());

  if (!mod) return;

  context.scopes.push(mod->get_scope());

  for (auto &declaration : node->declarations) resolve(declaration);

  context.scopes.pop();
}

void Resolver::import_declaration(celestia::ast::ImportDeclaration *node) {}

void Resolver::field_declaration(celestia::ast::FieldDeclaration *node) {

  if (!node || !node->name) return;

  const std::string &name = node->name->str;

  SymbolId symbol_id = declare_symbol(name, SymbolKind::Field, Visibility::Private, node);

  if (!symbol_id.is_valid()) return;

  if (node->type) resolve(node->type);
}

void Resolver::struct_declaration(celestia::ast::StructDeclaration *node) {

  if (!node || !node->name) return;

  const std::string &name = node->name->str;

  SymbolId symbol_id = declare_symbol(name, SymbolKind::Struct, node->specifiers.visibility, node);

  if (!symbol_id.is_valid()) return;

  auto *scope = context.unit.scopes.create_scope(core::ScopeKind::Struct, context.scopes.current());

  if (!scope) return;

  context.scopes.push(*scope);

  for (auto *composition : node->compositions) {
    if (composition) resolve(composition);
  }

  for (auto *field : node->fields) {
    if (field) resolve(field);
  }

  context.scopes.pop();
}

void Resolver::function_declaration(celestia::ast::FunctionDeclaration *node) {

  if (!node || !node->name) return;

  const std::string &name = node->name->str;

  SymbolId symbol_id = declare_symbol(name, SymbolKind::Function, node->specifiers.visibility, node);

  if (!symbol_id.is_valid()) return;

  if (node->specifiers.modifiers.has(Modifier::Extern)) return;

  auto *fun_scope = context.unit.scopes.create_scope(core::ScopeKind::Function, context.scopes.current());

  if (!fun_scope) {

    std::cout << "ERRO: nao foi possivel criar scope da funcao: " << name << '\n';

    return;
  }

  context.scopes.push(*fun_scope);

  for (auto *param : node->parameters) {

    if (param) pattern(param, Visibility::Private);
  }

  if (node->body) block_statement(node->body);

  context.scopes.pop();
}

void Resolver::variable_declaration(celestia::ast::VariableDeclaration *node) {

  if (node->pattern) { pattern(node->pattern, node->specifiers.visibility); }

  if (node->initializer) { resolve(node->initializer); }
}

void Resolver::capability_declaration(celestia::ast::CapabilityDeclaration *node) {

  if (!node || !node->name) return;

  const std::string &name = node->name->str;

  SymbolId symbol_id = declare_symbol(name, SymbolKind::Capability, node->specifiers.visibility, node);

  if (!symbol_id.is_valid()) return;

  auto *capability_scope = context.unit.scopes.create_scope(core::ScopeKind::Capability, context.scopes.current());

  if (!capability_scope) {

    std::cout << "ERRO: nao foi possivel criar scope da capability: " << name << '\n';

    return;
  }

  context.scopes.push(*capability_scope);

  for (auto *member : node->members) {

    if (!member) continue;

    resolve(member);
  }

  context.scopes.pop();
}

void Resolver::impl_declaration(celestia::ast::ImplDeclaration *node) {

  std::cout << "Resolvendo[impl]";
  auto *impl_scope = context.unit.scopes.create_scope(core::ScopeKind::Impl, context.scopes.current());

  context.scopes.push(*impl_scope);

  for (auto *member : node->members) { resolve(member); }

  context.scopes.pop();
}
}