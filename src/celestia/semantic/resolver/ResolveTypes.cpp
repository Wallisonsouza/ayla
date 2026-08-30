#include "celestia/semantic/resolver/Resolver.hpp"

#include "celestia/ast/types/FunctionType.hpp"
#include "celestia/ast/types/GenericType.hpp"
#include "celestia/ast/types/NamedType.hpp"
#include "celestia/semantic/resolver/Trace.hpp"

#include <cassert>

namespace celestia::semantic {

void Resolver::type_node(ast::TypeNode *node) {

  assert(node && "Resolver::type_node received null");

  debug::trace(debug::Category::Resolver, "resolving type node '{}'", ast::node_kind_name(node->kind));

  switch (node->kind) {

  case ast::NodeKind::NamedType: resolve_named_type(static_cast<ast::NamedType *>(node)); return;

  case ast::NodeKind::GenericType: resolve_generic_type(static_cast<ast::GenericTypeNode *>(node)); return;

  case ast::NodeKind::FunctionType: resolve_function_type(static_cast<ast::FunctionType *>(node)); return;

  default: assert(false && "Resolver::type_node received unsupported NodeKind"); return;
  }
}

SymbolId Resolver::lookup_symbol(std::string_view name) const {

  auto *scope = context.scopes.current();

  assert(scope && "Resolver has no active scope");

  if (!scope) return SymbolId::invalid();

  SymbolId symbol_id = scope->symbol(name);

  debug::trace(debug::Category::Resolver, "lookup '{}' -> {}", name, symbol_id.is_valid() ? std::to_string(symbol_id.index()) : "invalid");

  return symbol_id;
}

void Resolver::resolve_named_type(ast::NamedType *node) {

  assert(node && "Resolver::resolve_named_type received null");
  assert(node->name && "NamedType has no name");

  const auto &name = node->name->str;

  SymbolId symbol_id = lookup_symbol(name);

  if (!symbol_id.is_valid()) {

    context.unit.diagnostics.report({
        .severity = diagnostic::Severity::Error,
        .code = diagnostic::DiagnosticCode::UnknownType,
        .arguments =
            {
                diagnostic::name(name),
            },
    });

    return;
  }

  auto *symbol = context.compiler.symbols.get(symbol_id);

  assert(symbol && "Resolver found an invalid SymbolId");

  if (!symbol) return;

  if (symbol->kind != SymbolKind::Type) {

    context.unit.diagnostics.report({
        .severity = diagnostic::Severity::Error,
        .code = diagnostic::DiagnosticCode::NotAType,
        .arguments =
            {
                diagnostic::name(name),
                diagnostic::symbol(symbol_id),
            },
    });

    return;
  }

  node->symbol_id = symbol_id;

  debug::trace(debug::Category::Resolver, "resolved named type '{}' -> SymbolId({})", name, symbol_id.index());
}

void Resolver::resolve_generic_type(ast::GenericTypeNode *node) {

  assert(node && "Resolver::resolve_generic_type received null");
  assert(node->name && "GenericType has no name");

  const auto &name = node->name->str;

  debug::trace(debug::Category::Resolver, "resolving generic type '{}<{} arguments>'", name, node->arguments.size());

  SymbolId symbol_id = lookup_symbol(name);

  if (!symbol_id.is_valid()) {

    context.unit.diagnostics.report({
        .severity = diagnostic::Severity::Error,
        .code = diagnostic::DiagnosticCode::UnknownType,
        .arguments =
            {
                diagnostic::name(name),
            },
    });

    return;
  }

  auto *symbol = context.compiler.symbols.get(symbol_id);

  assert(symbol && "Resolver found an invalid SymbolId");

  if (!symbol) return;

  if (symbol->kind != SymbolKind::Type) {

    context.unit.diagnostics.report({
        .severity = diagnostic::Severity::Error,
        .code = diagnostic::DiagnosticCode::NotAType,
        .arguments =
            {
                diagnostic::name(name),
                diagnostic::symbol(symbol_id),
            },
    });

    return;
  }

  node->symbol_id = symbol_id;

  debug::trace(debug::Category::Resolver, "resolved generic constructor '{}' -> SymbolId({})", name, symbol_id.index());

  for (auto *argument : node->arguments) {

    assert(argument && "GenericType contains null argument");

    type_node(argument);
  }
}

void Resolver::resolve_function_type(ast::FunctionType *node) {

  assert(node && "Resolver::resolve_function_type received null");

  debug::trace(debug::Category::Resolver, "resolving function type with {} parameters", node->parameters.size());

  for (auto *parameter : node->parameters) {

    assert(parameter && "FunctionType contains null parameter");

    type_node(parameter);
  }

  if (node->return_type) {

    debug::trace(debug::Category::Resolver, "resolving function return type");

    type_node(node->return_type);
  }

  debug::trace(debug::Category::Resolver, "function type resolved");
}

} // namespace celestia::semantic
