#include "ayla/semantic/checker/checker.hpp"
#include "base_process.hpp"
#include "core/node/BinaryOp.hpp"

struct BinaryExpressionProcess : NodeProcess<ayla::ast::node::BinaryExpressionNode> {

  static void check(ayla::ast::node::BinaryExpressionNode *node, ProcessContext &ctx) {

    if (!node) return;

    ProcessEngine::run(ProcessEngine::Phase::Check, node->lhs, ctx);
    ProcessEngine::run(ProcessEngine::Phase::Check, node->rhs, ctx);

    Type *l = node->lhs ? node->lhs->inferred_type : &BuiltinTypes::Unknown;
    Type *r = node->rhs ? node->rhs->inferred_type : &BuiltinTypes::Unknown;

    switch (node->op) {

    case ayla::ast::BinaryOperation::Add:
    case ayla::ast::BinaryOperation::Subtract:
    case ayla::ast::BinaryOperation::Multiply:
    case ayla::ast::BinaryOperation::Divide:

      // if (l != &BuiltinTypes::Number || r != &BuiltinTypes::Number) { report_error(DiagnosticCode::TypeMismatch, node->slice); }

      node->inferred_type = &BuiltinTypes::Number;
      break;

    case ayla::ast::BinaryOperation::And:
    case ayla::ast::BinaryOperation::Or:

      // if (l != &BuiltinTypes::Boolean || r != &BuiltinTypes::Boolean) { report_error(DiagnosticCode::TypeMismatch, node->slice); }

      node->inferred_type = &BuiltinTypes::Boolean;
      break;

    case ayla::ast::BinaryOperation::Less:
    case ayla::ast::BinaryOperation::LessEqual:
    case ayla::ast::BinaryOperation::Greater:
    case ayla::ast::BinaryOperation::GreaterEqual:

      // if (l != &BuiltinTypes::Number || r != &BuiltinTypes::Number) { report_error(DiagnosticCode::TypeMismatch, node->slice); }

      node->inferred_type = &BuiltinTypes::Boolean;
      break;

    case ayla::ast::BinaryOperation::Equal:
    case ayla::ast::BinaryOperation::NotEqual:

      // if (l != r) { report_error(DiagnosticCode::TypeMismatch, node->slice); }

      node->inferred_type = &BuiltinTypes::Boolean;
      break;

    default:
      node->inferred_type = &BuiltinTypes::Unknown;
      break;
    }
  }

  static void resolve(ayla::ast::node::BinaryExpressionNode *node, ProcessContext &ctx) {
    if (!node) return;
    ProcessEngine::run(ProcessEngine::Phase::Resolve, node->lhs, ctx);
    ProcessEngine::run(ProcessEngine::Phase::Resolve, node->rhs, ctx);
  }

  static void infer(ayla::ast::node::BinaryExpressionNode *node, ProcessContext &ctx) {
    if (!node) return;
    ProcessEngine::run(ProcessEngine::Phase::Infer, node->lhs, ctx);
    ProcessEngine::run(ProcessEngine::Phase::Infer, node->rhs, ctx);

    node->inferred_type = &BuiltinTypes::Number;
  }
};