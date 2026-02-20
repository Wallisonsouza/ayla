#include "semantic/checker/TypeChecker.hpp"
namespace ayla {

void TypeChecker::check_binary_expression(ast::node::BinaryExpressionNode *node) {

  if (!node) return;

  check(node->lhs);
  check(node->rhs);

  Type *l = node->lhs ? node->lhs->inferred_type : &BuiltinTypes::Unknown;
  Type *r = node->rhs ? node->rhs->inferred_type : &BuiltinTypes::Unknown;

  switch (node->op) {

  // ------------------
  // Aritméticos
  // ------------------
  case ast::BinaryOperation::Add:
  case ast::BinaryOperation::Subtract:
  case ast::BinaryOperation::Multiply:
  case ast::BinaryOperation::Divide:

    if (l != &BuiltinTypes::Number || r != &BuiltinTypes::Number) { report_error(DiagnosticCode::TypeMismatch, node->slice); }

    node->inferred_type = &BuiltinTypes::Number;
    break;

  // ------------------
  // Lógicos
  // ------------------
  case ast::BinaryOperation::And:
  case ast::BinaryOperation::Or:

    if (l != &BuiltinTypes::Boolean || r != &BuiltinTypes::Boolean) { report_error(DiagnosticCode::TypeMismatch, node->slice); }

    node->inferred_type = &BuiltinTypes::Boolean;
    break;

  // ------------------
  // Comparação
  // ------------------
  case ast::BinaryOperation::Less:
  case ast::BinaryOperation::LessEqual:
  case ast::BinaryOperation::Greater:
  case ast::BinaryOperation::GreaterEqual:

    if (l != &BuiltinTypes::Number || r != &BuiltinTypes::Number) { report_error(DiagnosticCode::TypeMismatch, node->slice); }

    node->inferred_type = &BuiltinTypes::Boolean;
    break;

  // ------------------
  // Igualdade
  // ------------------
  case ast::BinaryOperation::Equal:
  case ast::BinaryOperation::NotEqual:

    if (l != r) { report_error(DiagnosticCode::TypeMismatch, node->slice); }

    node->inferred_type = &BuiltinTypes::Boolean;
    break;

  default:
    node->inferred_type = &BuiltinTypes::Unknown;
    break;
  }
}

void TypeChecker::check_unary_expression(ast::node::UnaryExpressionNode *node) {
  if (!node) return;

  check(node->operand);
}

void TypeChecker::check_index_expression(ast::node::IndexAccessExpressionNode *node) {
  if (!node || !node->base || !node->index) return;

  check(node->base);
  check(node->index);

  Type *baseType = node->base->inferred_type;
  Type *indexType = node->index->inferred_type;

  if (!baseType || baseType->kind != TypeKind::Array) {
    report_error(DiagnosticCode::TypeMismatch, node->slice);
    node->inferred_type = &BuiltinTypes::Unknown;
    return;
  }

  if (indexType != &BuiltinTypes::Number) { report_error(DiagnosticCode::TypeMismatch, node->index->slice); }

  auto *arrType = static_cast<ArrayType *>(baseType);
  node->inferred_type = arrType->element_type;
}

void TypeChecker::check_member_expression(ast::node::MemberAccessExpressionNode *node) {
  check(node->base);
  Type *baseType = node->base->inferred_type;

  if (!baseType || baseType->kind != TypeKind::Object) {
    report_error(DiagnosticCode::InvalidMemberAccess, node->field->slice);
    node->inferred_type = &BuiltinTypes::Unknown;
    return;
  }

  auto *objType = static_cast<ObjectType *>(baseType);

  Type *fieldType = objType->get_member(node->field->name);

  if (!fieldType) {
    report_error(DiagnosticCode::MemberNotFound, node->field->slice, {{"member", node->field->name}});
    node->inferred_type = &BuiltinTypes::Unknown;
    return;
  }

  node->inferred_type = fieldType;
}

void TypeChecker::check_assign_expression(ast::node::AssignmentExpressionNode *node) {

  if (!node || !node->target || !node->value) return;

  check(node->target);
  check(node->value);

  Type *targetType = nullptr;
  Type *valueType = node->value->inferred_type ? node->value->inferred_type : &BuiltinTypes::Unknown;

  switch (node->target->kind) {
  case ast::NodeKind::Identifier: {

    auto *id_node = static_cast<ast::node::IdentifierExpressionNode *>(node->target);
    targetType = id_node->inferred_type ? id_node->inferred_type : &BuiltinTypes::Unknown;
    break;
  }

  case ast::NodeKind::MemberAccessExpression: {
    auto *memNode = static_cast<ast::node::MemberAccessExpressionNode *>(node->target);
    targetType = memNode->inferred_type ? memNode->inferred_type : &BuiltinTypes::Unknown;
    break;
  }

  case ast::NodeKind::IndexAccess: {
    auto *idxNode = static_cast<ast::node::IndexAccessExpressionNode *>(node->target);
    targetType = idxNode->inferred_type ? idxNode->inferred_type : &BuiltinTypes::Unknown;
    break;
  }

  default:
    targetType = &BuiltinTypes::Unknown;
    break;
  }

  node->inferred_type = targetType;

  if (targetType != &BuiltinTypes::Unknown && valueType != &BuiltinTypes::Unknown) {
    if (targetType != valueType) { report_error(DiagnosticCode::TypeMismatch, node->slice, {{"expected", "targetType->name"}, {"found", "valueType->name"}}); }
  }
}

void TypeChecker::check_call_expression(ast::node::CallExpressionNode *node) {
  if (!node) return;

  check(node->callee);
  for (auto *arg : node->arguments) { check(arg); }

  Type *funcType = node->callee ? node->callee->inferred_type : nullptr;

  if (!funcType || funcType->kind != TypeKind::Function) {
    report_error(DiagnosticCode::UndeclaredSymbol, node->callee->slice);
    node->inferred_type = &BuiltinTypes::Unknown;
    return;
  }

  auto *ft = static_cast<FunctionType *>(funcType);
  if (ft->params.size() != node->arguments.size()) { report_error(DiagnosticCode::InvalidArguments, node->callee->slice); }

  node->inferred_type = ft->return_type;
}

void TypeChecker::check_id_expression(ast::node::IdentifierExpressionNode *node) {
  if (!node) return;

  auto *sym = unit.context.symbol_manager.get(node->resolved_symbol_id);

  if (!sym) {
    report_error(DiagnosticCode::UndeclaredSymbol, node->slice, {{"expected", node->name}});
    node->inferred_type = &BuiltinTypes::Unknown;
    return;
  }

  node->inferred_type = sym->type ? sym->type : &BuiltinTypes::Unknown;
}

} // namespace ayla
