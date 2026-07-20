#include "ast/expressions/MemberAccessExpressionNode.hpp"
#include "diagnostic/diagnostic_code.hpp"
#include "semantic/resolver/Resolver.hpp"

void Resolver::resolve_index_access(ayla::ast::node::IndexAccessExpressionNode *node) {

  if (node->base) resolve(node->base);

  if (node->index) resolve(node->index);
}

void Resolver::resolve_member_access(ayla::ast::node::MemberAccessExpressionNode *node) {
  if (!node || !node->base || !node->member) return;

  resolve(node->base);

  if (!node->base->resolved_symbol_id.is_valid()) {
    report_error(DiagnosticCode::UndeclaredSymbol, node->slice);
    return;
  }
}

void Resolver::resolve_function_call(ayla::ast::node::CallExpressionNode *node) {

  if (node->callee) resolve(node->callee);

  for (auto *arg : node->arguments) { resolve(arg); }
}