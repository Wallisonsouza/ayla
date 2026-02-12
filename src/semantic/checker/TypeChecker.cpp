#include "TypeChecker.hpp"
#include "core/node/BinaryOp.hpp"

namespace ayla {
void TypeChecker::check(ast::AstNode *node) {
  if (!node) return;

  switch (node->kind) {
  case ast::NodeKind::ExpressionStatement: check_expression_statement(static_cast<ast::node::ExpressionStatementNode *>(node)); break;
  case ast::NodeKind::Identifier: check_identifier(static_cast<ast::node::IdentifierExpressionNode *>(node)); break;
  case ast::NodeKind::NumberLiteral: check_number_literal(static_cast<ast::node::NumberLiteralNode *>(node)); break;
  case ast::NodeKind::StringLiteral: check_string_literal(static_cast<ast::node::StringLiteralNode *>(node)); break;
  case ast::NodeKind::BooleanLiteral: check_boolean_literal(static_cast<ast::node::BoolLiteralNode *>(node)); break;
  case ast::NodeKind::ArrayLiteral: check_array_literal(static_cast<ast::node::ArrayLiteralNode *>(node)); break;
  case ast::NodeKind::ObjectLiteral: check_object_literal(static_cast<ast::node::ObjectLiteralNode *>(node)); break;
  case ast::NodeKind::VariableDeclaration: check_variable_declaration(static_cast<ast::node::VariableDeclarationNode *>(node)); break;
  case ast::NodeKind::FunctionDeclaration: check_function_declaration(static_cast<ast::node::FunctionDeclarationNode *>(node)); break;
  case ast::NodeKind::FunctionCall: check_function_call(static_cast<ast::node::CallExpressionNode *>(node)); break;
  case ast::NodeKind::BinaryExpression: check_binary_expression(static_cast<ast::node::BinaryExpressionNode *>(node)); break;
  case ast::NodeKind::MemberAccess: check_member_access(static_cast<ast::node::MemberAccessExpressionNode *>(node)); break;
  case ast::NodeKind::IndexAccess: check_index_access(static_cast<ast::node::IndexAccessNode *>(node)); break;
  case ast::NodeKind::Assignment: check_assignment(dynamic_cast<ast::node::AssignmentExpressionNode *>(node)); break;
  case ast::NodeKind::IfStatement: check_if_statement(static_cast<ast::node::IfStatementNode *>(node)); break;
  case ast::NodeKind::WhileStatement: check_while_statement(static_cast<ast::node::WhileStatementNode *>(node)); break;
  case ast::NodeKind::ReturnStatement: check_return_statement(static_cast<ast::node::ReturnStatementNode *>(node)); break;
  case ast::NodeKind::BlockStatement: check_block(static_cast<ast::node::BlockStatementNode *>(node)); break;
  case ast::NodeKind::ImportStatement: check_import_node(static_cast<ast::node::ImportStatementNode *>(node)); break;
  case ast::NodeKind::ModuleDeclaration: check_module_declaration(static_cast<ast::node::ModuleDeclarationNode *>(node)); break;
  case ast::NodeKind::Pattern: check_pattern(static_cast<ast::PatternNode *>(node)); break;
  case ast::NodeKind::UnaryExpression: check_unary_expression(static_cast<ast::node::UnaryExpressionNode *>(node)); break;
  default: break;
  }
}

void TypeChecker::check_identifier(ast::node::IdentifierExpressionNode *node) {
  if (!node) return;

  auto *sym = unit.context.symbol_manager.get(node->resolved_symbol_id);

  if (!sym) {
    report_error(DiagnosticCode::UndeclaredSymbol, node->slice, {{"expected", node->name}});
    node->inferred_type = &BuiltinTypes::Unknown;
    return;
  }

  node->inferred_type = sym->type ? sym->type : &BuiltinTypes::Unknown;
}

void TypeChecker::check_expression_statement(ast::node::ExpressionStatementNode *node) {
  if (!node || !node->expression) return;
  check(node->expression);
}

void TypeChecker::check_array_literal(ast::node::ArrayLiteralNode *node) {
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

  node->inferred_type = unit.context.type_arena.alloc<ArrayType>(elementType);
}

void TypeChecker::check_object_literal(ast::node::ObjectLiteralNode *node) {
  if (!node) return;

  auto *objType = unit.context.type_arena.alloc<ObjectType>();

  for (auto *field : node->fields) {
    check(field->value);

    if (!field->key || field->key->kind != ast::NodeKind::Identifier) continue;
    auto *key = static_cast<ast::node::IdentifierExpressionNode *>(field->key);

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

void TypeChecker::check_variable_declaration(ast::node::VariableDeclarationNode *node) {
  if (!node) return;

  if (node->initializer) { check(node->initializer); }

  check_pattern(node->pattern);

  auto *idPattern = dynamic_cast<ast::IdentifierPatternNode *>(node->pattern);
  if (!idPattern) return;

  if (idPattern->type_annotation) { auto type = unit.context.type_table.find(idPattern->type_annotation->name); }

  Type *finalType = nullptr;

  if (idPattern->type_annotation)
    finalType = idPattern->type_annotation->inferred_type;
  else if (node->initializer)
    finalType = node->initializer->inferred_type;
  else
    finalType = &BuiltinTypes::Unknown;

  idPattern->inferred_type = finalType;

  if (auto *sym = unit.context.symbol_manager.get(idPattern->symbol_id)) sym->type = finalType; // ✅ Atualiza o símbolo com tipo final
}

void TypeChecker::check_pattern(ast::PatternNode *node) {
  if (!node) return;

  if (auto *idPattern = dynamic_cast<ast::IdentifierPatternNode *>(node)) {

    if (idPattern->type_annotation) check(idPattern->type_annotation);

    Type *finalType = nullptr;

    // Se existir type annotation
    if (idPattern->type_annotation)
      finalType = idPattern->type_annotation->inferred_type;
    else if (idPattern->identifier && idPattern->identifier->inferred_type)
      finalType = idPattern->identifier->inferred_type;
    else
      finalType = &BuiltinTypes::Unknown;

    idPattern->inferred_type = finalType;

    // Atualiza o símbolo
    if (auto *sym = unit.context.symbol_manager.get(idPattern->symbol_id)) sym->type = finalType;
  }
}

inline Type *current_function_return_type = nullptr;

void TypeChecker::check_return_statement(ast::node::ReturnStatementNode *node) {
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

void TypeChecker::check_function_declaration(ast::node::FunctionDeclarationNode *node) {
  if (!node) return;

  current_function_return_type = node->return_type ? node->return_type->inferred_type : nullptr;

  for (auto *param : node->parameters) check_pattern(param);

  if (node->body) check_block(node->body);

  auto *ft = unit.context.type_arena.alloc<FunctionType>();
  for (auto *param : node->parameters) ft->params.push_back(param->inferred_type);

  ft->return_type = node->return_type ? node->return_type->inferred_type : (current_function_return_type ? current_function_return_type : &BuiltinTypes::Unknown);

  node->inferred_type = ft;
  if (auto *sym = unit.context.symbol_manager.get(node->symbol_id)) sym->type = ft;

  current_function_return_type = nullptr;
}

void TypeChecker::check_function_call(ast::node::CallExpressionNode *node) {
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

//---------------------------
// Expressões
//---------------------------

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

  default: node->inferred_type = &BuiltinTypes::Unknown; break;
  }
}

void TypeChecker::check_unary_expression(ast::node::UnaryExpressionNode *node) {
  if (!node) return;

  check(node->operand);
}

void TypeChecker::check_index_access(ast::node::IndexAccessNode *node) {
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

void TypeChecker::check_if_statement(ast::node::IfStatementNode *node) {
  check(node->condition);
  if (node->condition->inferred_type != &BuiltinTypes::Boolean) report_error(DiagnosticCode::TypeMismatch, node->condition->slice);

  check(node->then_block);
  if (node->else_block) check(node->else_block);

  node->inferred_type = &BuiltinTypes::Unknown;
}

void TypeChecker::check_while_statement(ast::node::WhileStatementNode *node) {
  check(node->condition);
  if (node->condition->inferred_type != &BuiltinTypes::Boolean) report_error(DiagnosticCode::TypeMismatch, node->condition->slice);

  check(node->body);

  node->inferred_type = &BuiltinTypes::Unknown;
}

void TypeChecker::check_block(ast::node::BlockStatementNode *node) {
  if (!node) return;

  for (auto *stmt : node->statements) check(stmt);

  node->inferred_type = &BuiltinTypes::Unknown;
}

void TypeChecker::check_member_access(ast::node::MemberAccessExpressionNode *node) {
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

void TypeChecker::check_assignment(ast::node::AssignmentExpressionNode *node) {

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

  case ast::NodeKind::MemberAccess: {
    auto *memNode = static_cast<ast::node::MemberAccessExpressionNode *>(node->target);
    targetType = memNode->inferred_type ? memNode->inferred_type : &BuiltinTypes::Unknown;
    break;
  }

  case ast::NodeKind::IndexAccess: {
    auto *idxNode = static_cast<ast::node::IndexAccessNode *>(node->target);
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
} // namespace ayla
