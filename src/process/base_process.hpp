
#include "ayla/syntax/ast/NodeKind.hpp"
#include "ayla/syntax/ast/expressions/BinaryExpressionNode.hpp"
#include "ayla/syntax/ast/expressions/LiteralExpressionNode.hpp"
#include "engine/CompilationUnit.hpp"
#include "semantic/scope/scope.hpp"

struct ProcessContext {
  core::ParserScope *current_scope = nullptr;
  CompilationUnit &unit;

  ProcessContext(CompilationUnit &u) : unit(u) {}

  void push_scope() { current_scope = unit.scope_manager.create_scope(current_scope); }
  void pop_scope() { current_scope = current_scope->parent; }
};

template <typename NodeT> struct NodeProcess {
  static void check(NodeT *node, ProcessContext &ctx) {}
  static void resolve(NodeT *node, ProcessContext &ctx) {}
  static void infer(NodeT *node, ProcessContext &ctx) {}
};

class ProcessEngine {
public:
  enum class Phase { Check, Resolve, Infer };

  static void run(Phase phase, ayla::ast::AstNode *node, ProcessContext &ctx) {
    if (!node) return;

    switch (node->kind) {
    case ayla::ast::NodeKind::BinaryExpression:
      dispatch<ayla::ast::node::BinaryExpressionNode>(phase, static_cast<ayla::ast::node::BinaryExpressionNode *>(node), ctx);
      break;
    case ayla::ast::NodeKind::NumberLiteral:
      dispatch<ayla::ast::node::NumberLiteralNode>(phase, static_cast<ayla::ast::node::NumberLiteralNode *>(node), ctx);
      break;
    default:
      break;
    }
  }

private:
  template <typename NodeT> static void dispatch(Phase phase, NodeT *node, ProcessContext &ctx) {
    switch (phase) {
    case Phase::Check:
      NodeProcess<NodeT>::check(node, ctx);
      break;
    case Phase::Resolve:
      NodeProcess<NodeT>::resolve(node, ctx);
      break;
    case Phase::Infer:
      NodeProcess<NodeT>::infer(node, ctx);
      break;
    }
  }
};