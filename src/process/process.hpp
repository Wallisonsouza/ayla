#include "ayla/syntax/ast/expressions/IdentifierExpressionNode.hpp"
#include "ayla/syntax/ast/expressions/UnaryExpressionNode.hpp"
#include "base_process.hpp"

struct IdentifierExprProcess : NodeProcess<ayla::ast::node::IdentifierExpressionNode> {
  static void resolve(ayla::ast::node::IdentifierExpressionNode *node, ProcessContext &ctx) {
    if (!node) return;

    SymbolId id = ctx.current_scope->resolve_symbol(node->name);

    if (!id.is_valid()) {
      // report_error(DiagnosticCode::UndeclaredSymbol, node->slice);
      return;
    }

    node->resolved_symbol_id = id;
    node->local_slot = ctx.current_scope->resolve_slot(id).value_or(0);
  }
};

struct AssignmentExprProcess : NodeProcess<ayla::ast::node::AssignmentExpressionNode> {
  static void resolve(ayla::ast::node::AssignmentExpressionNode *node, ProcessContext &ctx) {
    if (!node) return;

    if (node->target) ProcessEngine::run(ProcessEngine::Phase::Resolve, node->target, ctx);

    auto symbol = ctx.unit.context.symbol_manager.get(node->target->resolved_symbol_id);
    if (!symbol) return;

    if (symbol->modifiers.has(ayla::ast::Modifier::Mut)) { std::cout << "Variable is mutable\n"; }

    if (node->value) ProcessEngine::run(ProcessEngine::Phase::Resolve, node->value, ctx);

    node->local_slot = node->target->local_slot;
  }
};

struct IndexAccessExprProcess : NodeProcess<ayla::ast::node::IndexAccessExpressionNode> {
  static void resolve(ayla::ast::node::IndexAccessExpressionNode *node, ProcessContext &ctx) {
    if (!node) return;
    if (node->base) ProcessEngine::run(ProcessEngine::Phase::Resolve, node->base, ctx);
    if (node->index) ProcessEngine::run(ProcessEngine::Phase::Resolve, node->index, ctx);
  }
};

struct MemberAccessExprProcess : NodeProcess<ayla::ast::node::MemberAccessExpressionNode> {
  static void resolve(ayla::ast::node::MemberAccessExpressionNode *node, ProcessContext &ctx) {
    if (!node || !node->base || !node->field) return;

    ProcessEngine::run(ProcessEngine::Phase::Resolve, node->base, ctx);

    if (!node->base->resolved_symbol_id.is_valid()) {
      // report_error(DiagnosticCode::UndeclaredSymbol, node->slice);
      return;
    }
  }
};

struct CallExprProcess : NodeProcess<ayla::ast::node::CallExpressionNode> {
  static void resolve(ayla::ast::node::CallExpressionNode *node, ProcessContext &ctx) {
    if (!node) return;
    if (node->callee) ProcessEngine::run(ProcessEngine::Phase::Resolve, node->callee, ctx);
    for (auto *arg : node->arguments) { ProcessEngine::run(ProcessEngine::Phase::Resolve, arg, ctx); }
  }
};

struct BinaryExprProcess : NodeProcess<ayla::ast::node::BinaryExpressionNode> {
  static void resolve(ayla::ast::node::BinaryExpressionNode *node, ProcessContext &ctx) {
    if (!node) return;
    if (node->lhs) ProcessEngine::run(ProcessEngine::Phase::Resolve, node->lhs, ctx);
    if (node->rhs) ProcessEngine::run(ProcessEngine::Phase::Resolve, node->rhs, ctx);
  }
};

struct UnaryExprProcess : NodeProcess<ayla::ast::node::UnaryExpressionNode> {
  static void resolve(ayla::ast::node::UnaryExpressionNode *node, ProcessContext &ctx) {
    if (!node) return;
    if (node->operand) ProcessEngine::run(ProcessEngine::Phase::Resolve, node->operand, ctx);
  }
};