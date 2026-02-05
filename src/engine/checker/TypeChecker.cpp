#include "TypeChecker.hpp"
#include "core/memory/type.hpp"
#include "core/node/Type.hpp"
#include "engine/parser/node/statement/ImportStatement.hpp"

void TypeChecker::check(ayla::ast::AstNode *node) {
  if (!node || node->inferred_type) return;

  switch (node->kind) {
  case ayla::ast::NodeKind::ExpressionStatement: check_expression_statement(static_cast<ayla::ast::ExpressionStatementNode *>(node)); break;
  case ayla::ast::NodeKind::Identifier: check_identifier(static_cast<ayla::ast::IdentifierNode *>(node)); break;
  case ayla::ast::NodeKind::NumberLiteral: check_number_literal(static_cast<parser::node::NumberLiteralNode *>(node)); break;
  case ayla::ast::NodeKind::StringLiteral: check_string_literal(static_cast<parser::node::StringLiteralNode *>(node)); break;
  case ayla::ast::NodeKind::BooleanLiteral: check_boolean_literal(static_cast<parser::node::BoolLiteralNode *>(node)); break;
  case ayla::ast::NodeKind::ArrayLiteral: check_array_literal(static_cast<parser::node::ASTArrayLiteralNode *>(node)); break;
  case ayla::ast::NodeKind::ObjectLiteral: check_object_literal(static_cast<parser::node::ObjectLiteralNode *>(node)); break;
  case ayla::ast::NodeKind::VariableDeclaration: check_variable_declaration(static_cast<ayla::ast::PatternNode *>(node)); break;
  case ayla::ast::NodeKind::FunctionDeclaration: check_function_declaration(static_cast<parser::node::FunctionDeclarationNode *>(node)); break;
  case ayla::ast::NodeKind::FunctionCall: check_function_call(static_cast<parser::node::FunctionCallNode *>(node)); break;
  case ayla::ast::NodeKind::BinaryExpression: check_binary_expression(static_cast<parser::node::BinaryExpressionNode *>(node)); break;
  case ayla::ast::NodeKind::MemberAccess: check_member_access(static_cast<parser::node::MemberAccessNode *>(node)); break;
  case ayla::ast::NodeKind::IndexAccess: check_index_access(static_cast<parser::node::IndexAccessNode *>(node)); break;
  case ayla::ast::NodeKind::Assignment: check_assignment(dynamic_cast<parser::node::statement::AssignmentNode *>(node)); break;
  case ayla::ast::NodeKind::IfStatement: check_if_statement(static_cast<parser::node::IfStatementNode *>(node)); break;
  case ayla::ast::NodeKind::WhileStatement: check_while_statement(static_cast<parser::node::ASTWhileStatementNode *>(node)); break;
  case ayla::ast::NodeKind::ReturnStatement: check_return_statement(static_cast<parser::node::ReturnStatementNode *>(node)); break;
  case ayla::ast::NodeKind::BlockStatement: check_block(static_cast<parser::node::BlockStatementNode *>(node)); break;
  case ayla::ast::NodeKind::Import: check_import_node(static_cast<parser::node::statement::ImportNode *>(node)); break;
  case ayla::ast::NodeKind::ModuleDeclaration: check_module_declaration(static_cast<parser::node::statement::ModuleDeclarationNode *>(node)); break;

  default: break;
  }
}

void TypeChecker::check_identifier(ayla::ast::IdentifierNode *node) {
  if (!node) return;

  auto *sym = unit.context.symbol_manager.get(node->resolved_symbol_id);

  if (!sym) {
    report_error(DiagnosticCode::UndeclaredSymbol, node->slice, {{"expected", node->name}});
    node->inferred_type = &BuiltinTypes::Unknown;
    return;
  }

  node->inferred_type = sym->type ? sym->type : &BuiltinTypes::Unknown;
}

void TypeChecker::check_expression_statement(ayla::ast::ExpressionStatementNode *node) {
  if (!node || !node->expression) return;
  check(node->expression);
}

void TypeChecker::check_array_literal(parser::node::ASTArrayLiteralNode *node) {
  if (!node) return;

  Type *elementType = nullptr;
  for (auto *el : node->elements) {
    check(el);
    Type *t = el->inferred_type ? el->inferred_type : &BuiltinTypes::Unknown;

    if (!elementType)
      elementType = t;
    else if (elementType != t)
      elementType = &BuiltinTypes::Unknown;
  }

  if (!elementType) elementType = &BuiltinTypes::Unknown;

  node->inferred_type = unit.type_arena.alloc<ArrayType>(elementType);
}

void TypeChecker::check_object_literal(parser::node::ObjectLiteralNode *node) {
  if (!node) return;

  auto *objType = unit.type_arena.alloc<ObjectType>();
  for (auto *field : node->field_list->elements) {
    check(field->value);

    if (!field->key || field->key->kind != ayla::ast::NodeKind::Identifier) continue;
    auto *key = static_cast<ayla::ast::IdentifierNode *>(field->key);

    if (objType->has_member(key->name)) {
      report_error(DiagnosticCode::RedeclaredIdentifier, key->slice);
      continue;
    }

    Type *valueType = field->value ? field->value->inferred_type : &BuiltinTypes::Unknown;
    objType->add_member(key->name, valueType);
  }

  node->inferred_type = objType;
}

//---------------------------
// Variáveis
//---------------------------

void TypeChecker::check_variable_declaration(ayla::ast::PatternNode *node) {
  if (!node) return;

  if (node->value) check(node->value);
  if (node->type) check(node->type);

  Type *finalType = node->type ? node->type->inferred_type : node->value ? node->value->inferred_type : &BuiltinTypes::Unknown;

  node->inferred_type = finalType;

  if (auto *sym = unit.context.symbol_manager.get(node->symbol_id)) sym->type = finalType;
}

//---------------------------
// Funções
//---------------------------

inline Type *current_function_return_type = nullptr;

void TypeChecker::check_return_statement(parser::node::ReturnStatementNode *node) {
  if (!node->value) return;

  check(node->value);
  Type *actual = node->value->inferred_type ? node->value->inferred_type : &BuiltinTypes::Unknown;

  if (!current_function_return_type) {
    current_function_return_type = actual;
  } else if (actual != current_function_return_type) {

    report_error(DiagnosticCode::TypeMismatch, node->slice);
  }

  node->inferred_type = actual;
}

void TypeChecker::check_function_declaration(parser::node::FunctionDeclarationNode *node) {
  if (!node) return;

  current_function_return_type = node->return_type ? node->return_type->inferred_type : nullptr;

  for (auto *param : node->params) check_variable_declaration(param);

  if (node->body) check_block(node->body);

  auto *ft = unit.type_arena.alloc<FunctionType>();
  for (auto *param : node->params) ft->params.push_back(param->inferred_type);

  ft->return_type = node->return_type ? node->return_type->inferred_type : (current_function_return_type ? current_function_return_type : &BuiltinTypes::Unknown);

  node->inferred_type = ft;
  if (auto *sym = unit.context.symbol_manager.get(node->symbol_id)) sym->type = ft;

  current_function_return_type = nullptr;
}

void TypeChecker::check_function_call(parser::node::FunctionCallNode *node) {
  if (!node) return;

  check(node->callee);
  for (auto *arg : node->arguments) check(arg);

  Type *funcType = node->callee ? node->callee->inferred_type : nullptr;

  if (!funcType || funcType->kind != TypeKind::Function) {
    // report_error(DiagnosticCode::UndeclaredSymbol, node->callee->slice);
    // node->inferred_type = &BuiltinTypes::Unknown;
    return;
  }

  auto *ft = static_cast<FunctionType *>(funcType);
  if (ft->params.size() != node->arguments.size()) { report_error(DiagnosticCode::InvalidArguments, node->callee->slice); }

  node->inferred_type = ft->return_type;
}

//---------------------------
// Expressões
//---------------------------

void TypeChecker::check_binary_expression(parser::node::BinaryExpressionNode *node) {
  if (!node) return;

  check(node->lhs);
  check(node->rhs);

  Type *l = node->lhs ? node->lhs->inferred_type : &BuiltinTypes::Unknown;
  Type *r = node->rhs ? node->rhs->inferred_type : &BuiltinTypes::Unknown;

  // Simples exemplo: números + números, boolean && boolean
  switch (node->op) {
  case ayla::ast::BinaryOperation::Add:
  case ayla::ast::BinaryOperation::Subtract:
  case ayla::ast::BinaryOperation::Multiply:
  case ayla::ast::BinaryOperation::Divide:
    if (l != &BuiltinTypes::Number || r != &BuiltinTypes::Number) report_error(DiagnosticCode::TypeMismatch, node->slice);
    node->inferred_type = &BuiltinTypes::Number;
    break;
  case ayla::ast::BinaryOperation::And:
  case ayla::ast::BinaryOperation::Or:
    if (l != &BuiltinTypes::Boolean || r != &BuiltinTypes::Boolean) report_error(DiagnosticCode::TypeMismatch, node->slice);
    node->inferred_type = &BuiltinTypes::Boolean;
    break;
  default: node->inferred_type = &BuiltinTypes::Unknown; break;
  }
}

void TypeChecker::check_index_access(parser::node::IndexAccessNode *node) {
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

//---------------------------
// Controle
//---------------------------

void TypeChecker::check_if_statement(parser::node::IfStatementNode *node) {
  check(node->condition);
  if (node->condition->inferred_type != &BuiltinTypes::Boolean) report_error(DiagnosticCode::TypeMismatch, node->condition->slice);

  check_block(node->then_block);
  if (node->else_block) check(node->else_block);

  node->inferred_type = &BuiltinTypes::Unknown;
}

void TypeChecker::check_while_statement(parser::node::ASTWhileStatementNode *node) {
  check(node->condition);
  if (node->condition->inferred_type != &BuiltinTypes::Boolean) report_error(DiagnosticCode::TypeMismatch, node->condition->slice);

  check_block(node->body);

  node->inferred_type = &BuiltinTypes::Unknown;
}

//---------------------------
// Blocos
//---------------------------

void TypeChecker::check_block(parser::node::BlockStatementNode *node) {
  if (!node) return;

  for (auto *stmt : node->statements) check(stmt);

  node->inferred_type = &BuiltinTypes::Unknown;
}

//---------------------------
// Imports
//---------------------------

//---------------------------
// Módulos
//---------------------------

void TypeChecker::check_member_access(parser::node::MemberAccessNode *node) {
  if (!node || !node->base || !node->field) return;

  check(node->base);

  Type *baseType = node->base->inferred_type;

  if (!baseType) {
    report_error(DiagnosticCode::UnknownType, node->base->slice);
    node->inferred_type = &BuiltinTypes::Unknown;
    return;
  }

  if (baseType->kind != TypeKind::Object) {
    report_error(DiagnosticCode::InvalidMemberAccess, node->field->slice, {{"base_type", baseType->to_string()}});
    node->inferred_type = &BuiltinTypes::Unknown;
    return;
  }

  auto *objType = static_cast<ObjectType *>(baseType);

  if (!objType->has_member(node->field->name)) {
    report_error(DiagnosticCode::MemberNotFound, node->field->slice, {{"member", node->field->name}});
    node->inferred_type = &BuiltinTypes::Unknown;
    return;
  }

  node->inferred_type = objType->get_member(node->field->name);
}

void TypeChecker::check_assignment(parser::node::statement::AssignmentNode *node) {

  if (!node || !node->target || !node->value) return;

  // 1) Primeiro, checa os filhos
  check(node->target);
  check(node->value);

  Type *targetType = nullptr;
  Type *valueType = node->value->inferred_type ? node->value->inferred_type : &BuiltinTypes::Unknown;

  switch (node->target->kind) {
  case ayla::ast::NodeKind::Identifier: {
    auto *idNode = static_cast<ayla::ast::IdentifierNode *>(node->target);
    targetType = idNode->inferred_type ? idNode->inferred_type : &BuiltinTypes::Unknown;
    break;
  }

  case ayla::ast::NodeKind::MemberAccess: {
    auto *memNode = static_cast<parser::node::MemberAccessNode *>(node->target);
    targetType = memNode->inferred_type ? memNode->inferred_type : &BuiltinTypes::Unknown;
    break;
  }

  case ayla::ast::NodeKind::IndexAccess: {
    auto *idxNode = static_cast<parser::node::IndexAccessNode *>(node->target);
    targetType = idxNode->inferred_type ? idxNode->inferred_type : &BuiltinTypes::Unknown;
    break;
  }

  default: targetType = &BuiltinTypes::Unknown; break;
  }

  node->inferred_type = targetType;

  if (targetType != &BuiltinTypes::Unknown && valueType != &BuiltinTypes::Unknown) {
    if (targetType != valueType) { report_error(DiagnosticCode::TypeMismatch, node->slice, {{"expected", "targetType->name"}, {"found", "valueType->name"}}); }
  }
}
