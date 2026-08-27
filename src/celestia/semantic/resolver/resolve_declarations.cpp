#include "Resolver.hpp"
#include "celestia/ast/declarations/ModuleDeclaration.hpp"

#include <iostream>

namespace celestia::semantic {

void Resolver::resolve_module_declaration(ast::ModuleDeclaration *node) {

  if (!node) return;

  Module *module = context.unit.module;

  if (!module) throw std::runtime_error("Resolver: module not initialized");

  context.scopes.push(module->get_scope());

  for (auto *declaration : node->declarations) {

    if (declaration) resolve(declaration);
  }

  context.scopes.pop();
}

void Resolver::resolve_module_init_declaration(ast::ModuleInitDeclaration *node) {

  if (!node || !node->body) return;

  std::cout << "[Resolver] resolving module init\n";
  std::cout << "[Resolver] module init body = " << node->body << '\n';

  resolve(node->body);

  std::cout << "[Resolver] module init body resolved\n";
}

void Resolver::resolve_import_declaration(ast::ImportDeclaration *node) {

  // TODO
}

void Resolver::resolve_field_declaration(ast::FieldDeclaration *node) {

  if (!node || !node->name) return;

  const std::string &name = node->name->str;

  SymbolId symbol_id = declare_symbol(name, SymbolKind::Field, Visibility::Private, node);

  if (!symbol_id.is_valid()) return;

  if (node->type) resolve(node->type);
}

void Resolver::resolve_struct_declaration(ast::StructDeclaration *node) {

  if (!node || !node->name) return;

  const std::string &name = node->name->str;

  // Foo
  SymbolId symbol_id = declare_symbol(name, SymbolKind::Type, node->specifiers.visibility, node);

  if (!symbol_id.is_valid()) return;

  // Foo's scope
  auto *struct_scope = context.unit.module->scopes.create_scope(core::ScopeKind::Struct, context.scopes.current());

  if (!struct_scope) return;

  context.scopes.push(*struct_scope);

  // Foo<T>
  for (auto *generic : node->generic_parameters) {

    if (!generic) continue;

    declare_symbol(generic->str, SymbolKind::Type, Visibility::Private, generic);
  }

  // struct Foo<T> : Base<T>, Other<T>
  for (auto *composition : node->compositions) {

    if (composition) resolve(composition);
  }

  // struct Foo<T> { value: T }
  for (auto *field : node->fields) {

    if (field) resolve(field);
  }

  context.scopes.pop();
}

void Resolver::resolve_function_declaration(ast::FunctionDeclaration *node) {

  if (!node || !node->name) return;

  const std::string &name = node->name->str;

  // add
  SymbolId symbol_id = declare_symbol(name, SymbolKind::Function, node->specifiers.visibility, node);

  if (!symbol_id.is_valid()) return;

  // add's scope
  auto *fun_scope = context.unit.module->scopes.create_scope(core::ScopeKind::Function, context.scopes.current());

  if (!fun_scope) {

    std::cout << "ERRO: nao foi possivel criar scope da funcao: " << name << '\n';

    return;
  }

  context.scopes.push(*fun_scope);

  // add<T>
  for (auto *generic : node->generic_parameters) {

    if (!generic) continue;

    declare_symbol(generic->str, SymbolKind::Type, Visibility::Private, generic);
  }

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

void Resolver::resolve_variable_declaration(ast::VariableDeclaration *node) {

  if (!node) return;

  if (node->pattern) pattern(node->pattern, node->specifiers.visibility);

  if (node->initializer) resolve(node->initializer);
}

void Resolver::resolve_capability_declaration(ast::CapabilityDeclaration *node) {

  if (!node || !node->name) return;

  const std::string &name = node->name->str;

  // Comparable
  SymbolId symbol_id = declare_symbol(name, SymbolKind::Capability, node->specifiers.visibility, node);

  if (!symbol_id.is_valid()) return;

  auto *capability_scope = context.unit.module->scopes.create_scope(core::ScopeKind::Capability, context.scopes.current());

  if (!capability_scope) {

    std::cout << "ERRO: nao foi possivel criar scope da capability: " << name << '\n';

    return;
  }

  context.scopes.push(*capability_scope);

  // Comparable<T>
  for (auto *generic : node->generic_parameters) {

    if (!generic) continue;

    declare_symbol(generic->str, SymbolKind::Type, Visibility::Private, generic);
  }

  // Members
  for (auto *member : node->members) {

    if (member) resolve(member);
  }

  context.scopes.pop();
}

void Resolver::resolve_impl_declaration(ast::ImplDeclaration *node) {

  if (!node) return;

  std::cout << "Resolvendo[impl]\n";

  auto *impl_scope = context.unit.module->scopes.create_scope(core::ScopeKind::Impl, context.scopes.current());

  if (!impl_scope) return;

  context.scopes.push(*impl_scope);

  // impl<T> Drawable<T>
  for (auto *generic : node->generic_parameters) {

    if (!generic) continue;

    declare_symbol(generic->str, SymbolKind::Type, Visibility::Private, generic);
  }

   resolve(node->target);
   resolve(node->capability);

 
  for (auto *member : node->members) {

    if (member) resolve(member);
  }

  context.scopes.pop();
}

void Resolver::resolve_type_declaration(ast::TypeDeclaration *node) {

  if (!node || !node->name) return;

  const std::string &name = node->name->str;

  // array
  SymbolId symbol_id = declare_symbol(name, SymbolKind::Type, node->specifiers.visibility, node);

  if (!symbol_id.is_valid()) return;

  auto *type_scope = context.unit.module->scopes.create_scope(core::ScopeKind::Type, context.scopes.current());

  if (!type_scope) return;

  context.scopes.push(*type_scope);

 
  // type<K, V...>
  for (auto *generic : node->generic_parameters) {

    if (!generic) continue;

    declare_symbol(generic->str, SymbolKind::Type, Visibility::Private, generic);
  }

  context.scopes.pop();
}

} // namespace celestia::semantic