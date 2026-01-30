#pragma once
#include "core/memory/symbol.hpp"
#include "core/memory/value.hpp"
#include "core/node/BinaryOp.hpp"
#include "core/node/NodeKind.hpp"
#include "core/node/Type.hpp"
#include "engine/CompilationUnit.hpp"
#include "engine/parser/node/literal_nodes.hpp"
#include "engine/parser/node/operator_nodes.hpp"
#include "engine/parser/node/statement/ImportStatement.hpp"
#include "engine/parser/node/statement_nodes.hpp"
#include "runtime_scope.hpp"

struct Executor {

  RuntimeScope *current_scope;

  Executor(RuntimeScope *scope) : current_scope(scope) {}

  // Value execute_assignment(CompilationUnit &unit, parser::node::statement::AssignmentNode *node) {

  //   Value val = execute_node(unit, node->value);

  //   if (auto *id = dynamic_cast<core::ast::IdentifierNode *>(node->target)) {
  //     Value *ref = current_scope->get_ref(id->symbol_id);
  //     if (!ref) throw std::runtime_error("Assignment to undefined variable");

  //     *ref = std::move(val);
  //     return *ref;
  //   }

  //   throw std::runtime_error("Invalid assignment target");
  // }

  Value execute_while(CompilationUnit &unit, parser::node::ASTWhileStatementNode *node) {

    Value last = Value::Void();

    while (true) {
      Value cond = execute_node(unit, node->condition);

      if (!cond.as_bool()) { break; }

      last = execute_block(unit, node->block);
    }

    return last;
  }

  Value execute_assignment(CompilationUnit &unit, parser::node::statement::AssignmentNode *node) {
    // 1. Executa o valor da atribuição
    Value val = execute_node(unit, node->value);

    if (auto *id = dynamic_cast<core::ast::IdentifierNode *>(node->target)) {
      current_scope->set(id->symbol_id, val);
    } else {
      throw std::runtime_error("Invalid assignment target");
    }

    return val; // ou Void()
  }

  Value execute_node(CompilationUnit &unit, core::ast::ASTNode *node) {
    if (!node) return Value::Null();

    switch (node->kind) {

    case core::ast::NodeKind::ExpressionStatement: {
      auto *es = static_cast<core::ast::ExpressionStatementNode *>(node);
      execute_node(unit, es->expr);
      return Value::Void();
    }

    case core::ast::NodeKind::Assignment: return execute_assignment(unit, static_cast<parser::node::statement::AssignmentNode *>(node));

    case core::ast::NodeKind::Identifier: return execute_identifier(static_cast<core::ast::IdentifierNode *>(node)->symbol_id);

    case core::ast::NodeKind::NumberLiteral: return Value::Number(static_cast<parser::node::NumberLiteralNode *>(node)->value);

    case core::ast::NodeKind::StringLiteral: return Value::String(static_cast<parser::node::StringLiteralNode *>(node)->value);

    case core::ast::NodeKind::BinaryExpression: return execute_binary(unit, static_cast<parser::node::BinaryExpressionNode *>(node));

    case core::ast::NodeKind::PathExpression: return execute_identifier(static_cast<parser::node::statement::PathExprNode *>(node)->symbol_id);

    case core::ast::NodeKind::FunctionCall: return execute_function_call(unit, static_cast<parser::node::FunctionCallNode *>(node));

    case core::ast::NodeKind::VariableDeclaration: return execute_variable_declaration(unit, static_cast<core::ast::PatternNode *>(node));

    case core::ast::NodeKind::BlockStatement: return execute_block(unit, static_cast<parser::node::BlockStatementNode *>(node));

    case core::ast::NodeKind::IfStatement: return execute_if(unit, static_cast<parser::node::IfStatementNode *>(node));

    case core::ast::NodeKind::WhileStatement: return execute_while(unit, static_cast<parser::node::ASTWhileStatementNode *>(node));

    case core::ast::NodeKind::FunctionDeclaration: return execute_function_declaration(unit, static_cast<parser::node::FunctionDeclarationNode *>(node));

    case core::ast::NodeKind::ReturnStatement: return execute_return(unit, static_cast<parser::node::ReturnStatementNode *>(node));

    default: return Value::Null();
    }
  }

  // Value execute_array_literal(CompilationUnit &unit, parser::node::ASTArrayLiteralNode *node) {
  //   std::vector<Value *> elements;
  //   elements.reserve(node->elements.size());

  //   for (auto *expr : node->elements) {
  //     Value val = execute_node(unit, expr);

  //     Value *stored = current_scope->arena.create<Value>(std::move(val));
  //     elements.push_back(stored);
  //   }

  //   return Value::Array(std::move(elements));
  // }

  Value execute_return(CompilationUnit &unit, parser::node::ReturnStatementNode *node) {
    if (!node->value) return Value::Void();
    return execute_node(unit, node->value);
  }

  Value execute_block(CompilationUnit &unit, parser::node::BlockStatementNode *block) {
    if (!block) return Value::Void();

    Value last_value = Value::Void();
    for (auto *stmt : block->statements) { last_value = execute_node(unit, stmt); }

    return last_value;
  }

  Value execute_if(CompilationUnit &unit, parser::node::IfStatementNode *node) {

    if (!node || !node->condition) return Value::Void();

    Value cond = execute_node(unit, node->condition);
    bool cond_truthy = cond.as_bool();

    if (cond_truthy) {
      return execute_block(unit, node->if_block);
    } else {
      return execute_node(unit, node->else_block);
    }
  }

  Value execute_identifier(SymbolId id) {
    if (id == INVALID_SYMBOL_ID) return Value::Null();
    return current_scope->get(id);
  }

  Value execute_binary(CompilationUnit &unit, parser::node::BinaryExpressionNode *node) {
    Value lhs = execute_node(unit, node->left);
    Value rhs = execute_node(unit, node->right);

    switch (node->op) {
    case core::ast::BinaryOperation::Add: return Value::Number(lhs.get_number() + rhs.get_number());
    case core::ast::BinaryOperation::Subtract: return Value::Number(lhs.get_number() - rhs.get_number());
    case core::ast::BinaryOperation::Multiply: return Value::Number(lhs.get_number() * rhs.get_number());
    case core::ast::BinaryOperation::Divide: return Value::Number(lhs.get_number() / rhs.get_number());
    case core::ast::BinaryOperation::Equal: return Value::Boolean(lhs.get_number() == rhs.get_number());
    case core::ast::BinaryOperation::Less: return Value::Boolean(lhs.get_number() < rhs.get_number());
    default: return Value::Null();
    }
  }

  Value execute_variable_declaration(CompilationUnit &unit, core::ast::PatternNode *node) {

    Value value = Value::Null();

    if (node->value) { value = execute_node(unit, node->value); }

    if (node->symbol_id == INVALID_SYMBOL_ID) { throw std::runtime_error("Variable declaration has invalid symbol id"); }

    current_scope->set(node->symbol_id, value);

    return Value::Void();
  }

  Value execute_function_call(CompilationUnit &unit, parser::node::FunctionCallNode *node) {
    SymbolId id = INVALID_SYMBOL_ID;

    if (node->callee->kind == core::ast::NodeKind::Identifier)
      id = static_cast<core::ast::IdentifierNode *>(node->callee)->symbol_id;
    else if (node->callee->kind == core::ast::NodeKind::PathExpression)
      id = static_cast<parser::node::statement::PathExprNode *>(node->callee)->symbol_id;

    if (id == INVALID_SYMBOL_ID) return Value::Null();

    auto symbol = unit.symbols.get(id);
    if (!symbol) return Value::Null();

    Value func_val;
    if (symbol->declaration->kind == core::ast::NodeKind::NativeFunctionDeclaration) {
      func_val = Value::Native(static_cast<core::ast::NativeFunctionDeclarationNode *>(symbol->declaration)->callback);
    } else if (symbol->declaration->kind == core::ast::NodeKind::FunctionDeclaration) {
      func_val = Value::User(static_cast<parser::node::FunctionDeclarationNode *>(symbol->declaration), current_scope);
    } else {
      return Value::Null();
    }

    if (func_val.is_native_function()) {
      std::vector<Value> args;
      for (auto *arg : node->args) args.push_back(execute_node(unit, arg));
      return func_val.get_native()(args);
    }

    if (func_val.is_user_function()) {
      auto &fn = func_val.get_user_function();
      RuntimeScope new_scope(fn.captured_scope);
      for (size_t i = 0; i < node->args.size(); ++i) new_scope.set(fn.node->params[i]->symbol_id, execute_node(unit, node->args[i]));
      Executor executor(&new_scope);
      return executor.execute_block(unit, fn.node->body);
    }

    return Value::Null();
  }

  Value execute_function_declaration(CompilationUnit &unit, parser::node::FunctionDeclarationNode *node) {

    Value func_value = Value::User(node, current_scope);

    current_scope->set(node->symbol_id, func_value);

    return Value::Void();
  }

  void execute_ast(CompilationUnit &unit) {

    if (unit.diagns.all().size() > 0) { return; }
    for (auto &resolved_node : unit.ast.get_nodes()) { execute_node(unit, resolved_node); }
  }
};