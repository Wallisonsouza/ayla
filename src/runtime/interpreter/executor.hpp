#pragma once

#include "core/node/BinaryOp.hpp"
#include "engine/CompilationUnit.hpp"

#include "frontend/ast/expressions/AssignmentExpression.hpp"
#include "frontend/ast/expressions/BinaryExpressionNode.hpp"
#include "frontend/ast/expressions/CallExpressionNode.hpp"
#include "frontend/ast/expressions/IndexAcessExpressionNode.hpp"
#include "frontend/ast/expressions/LiteralExpressionNode.hpp"
#include "frontend/ast/expressions/MemberAccessExpressionNode.hpp"
#include "frontend/ast/statements/BlockStatementNode.hpp"
#include "frontend/ast/statements/ExpressionStatementNode.hpp"
#include "frontend/ast/statements/FunctionDeclarationNode.hpp"
#include "frontend/ast/statements/IfStatementNode.hpp"
#include "frontend/ast/statements/ImportStatementNode.hpp"
#include "frontend/ast/statements/ModuleDeclarationNode.hpp"
#include "frontend/ast/statements/ReturnStatementNodes.hpp"
#include "frontend/ast/statements/VariableDeclarationNode.hpp"
#include "frontend/ast/statements/WhileStatementNode.hpp"
#include "runtime/scope/runtime_scope.hpp"

#include <memory>
#include <stdexcept>
#include <vector>

struct Executor {

  RuntimeScope *current_scope;

  Executor(RuntimeScope *scope) : current_scope(scope) {}

  ExecResult execute_module_declaration(CompilationUnit &unit, ayla::ast::node::ModuleDeclarationNode *node);
  ExecResult execute_import_node(CompilationUnit &unit, ayla::ast::node::ImportStatementNode *node);
  ExecResult execute_array(CompilationUnit &unit, ayla::ast::node::ArrayLiteralNode *node);
  ExecResult execute_index_access(CompilationUnit &unit, ayla::ast::node::IndexAccessNode *node);
  ExecResult execute_object(CompilationUnit &unit, ayla::ast::node::ObjectLiteralNode *node);
  ExecResult execute_member_acess(CompilationUnit &unit, ayla::ast::node::MemberAccessExpressionNode *member);

  ExecResult execute_node(CompilationUnit &unit, ayla::ast::AstNode *node) {
    if (!node) return ExecResult::make_value(std::make_shared<Value>(Value::Null()));

    switch (node->kind) {

    case ayla::ast::NodeKind::ExpressionStatement: return execute_expression_statement(unit, static_cast<ayla::ast::node::ExpressionStatementNode *>(node));

    case ayla::ast::NodeKind::Assignment: return execute_assignment(unit, static_cast<ayla::ast::node::AssignmentExpressionNode *>(node));

    case ayla::ast::NodeKind::Identifier: return execute_identifier(static_cast<ayla::ast::node::IdentifierExpressionNode *>(node));

    case ayla::ast::NodeKind::NumberLiteral: return ExecResult::make_value(std::make_shared<Value>(Value::Number(static_cast<ayla::ast::node::NumberLiteralNode *>(node)->value)));

    case ayla::ast::NodeKind::StringLiteral: return ExecResult::make_value(std::make_shared<Value>(Value::String(static_cast<ayla::ast::node::StringLiteralNode *>(node)->value)));

    case ayla::ast::NodeKind::BinaryExpression: return execute_binary(unit, static_cast<ayla::ast::node::BinaryExpressionNode *>(node));

    case ayla::ast::NodeKind::MemberAccess: return execute_member_acess(unit, static_cast<ayla::ast::node::MemberAccessExpressionNode *>(node));

    case ayla::ast::NodeKind::FunctionCall: return execute_function_call(unit, static_cast<ayla::ast::node::CallExpressionNode *>(node));

    case ayla::ast::NodeKind::VariableDeclaration: return execute_variable_declaration(unit, static_cast<ayla::ast::node::VariableDeclarationNode *>(node));

    case ayla::ast::NodeKind::BlockStatement: return execute_block(unit, static_cast<ayla::ast::node::BlockStatementNode *>(node));

    case ayla::ast::NodeKind::IfStatement: return execute_if(unit, static_cast<ayla::ast::node::IfStatementNode *>(node));

    case ayla::ast::NodeKind::ArrayLiteral: return execute_array(unit, static_cast<ayla::ast::node::ArrayLiteralNode *>(node));

    case ayla::ast::NodeKind::IndexAccess: return execute_index_access(unit, static_cast<ayla::ast::node::IndexAccessNode *>(node));

    case ayla::ast::NodeKind::WhileStatement: return execute_while(unit, static_cast<ayla::ast::node::WhileStatementNode *>(node));

    case ayla::ast::NodeKind::FunctionDeclaration: return execute_function_declaration(unit, static_cast<ayla::ast::node::FunctionDeclarationNode *>(node));

    case ayla::ast::NodeKind::ReturnStatement: return execute_return(unit, static_cast<ayla::ast::node::ReturnStatementNode *>(node));

    case ayla::ast::NodeKind::ModuleDeclaration: return execute_module_declaration(unit, static_cast<ayla::ast::node::ModuleDeclarationNode *>(node));

    case ayla::ast::NodeKind::Import: return execute_import_node(unit, static_cast<ayla::ast::node::ImportStatementNode *>(node));

    default: return ExecResult::make_value(std::make_shared<Value>(Value::Null()));
    }
  }

  ExecResult execute_function_call(CompilationUnit &unit, ayla::ast::node::CallExpressionNode *node) {

    auto callee = execute_node(unit, node->callee).value;

    // std::vector<Value> args;
    // for (auto *arg_node : node->arguments) {

    //   debug.debug_node(arg_node, true);
    //   auto v = execute_node(unit, arg_node).value;
    //   args.push_back(*v);
    // }

    // if (callee->is_native_function()) {
    //   auto &fn = callee->get_native();
    //   Value result = fn(args);
    //   return ExecResult::make_value(std::make_shared<Value>(std::move(result)));
    // }

    // if (callee->is_user_function()) {
    //   auto &uf = callee->get_user_function();

    //   // 3️⃣ novo escopo
    //   RuntimeScope local_scope(uf.captured_scope);
    //   RuntimeScope *prev = current_scope;
    //   current_scope = &local_scope;

    //   // 4️⃣ bind parâmetros
    //   for (size_t i = 0; i < uf.node->params.size(); ++i) {
    //     auto param_id = uf.node->params[i]->symbol_id;

    //     std::shared_ptr<Value> val = i < args.size() ? std::make_shared<Value>(args[i]) : std::make_shared<Value>(Value::Null());

    //     local_scope.set(param_id, val);
    //   }

    //   // 5️⃣ executar corpo
    //   auto result = execute_block(unit, uf.node->body);

    //   // 6️⃣ restaurar escopo
    //   current_scope = prev;

    //   if (result.is_return()) return ExecResult::make_value(result.value);

    //   return ExecResult::make_value(std::make_shared<Value>(Value::Void()));
    // }

    // throw std::runtime_error("Trying to call non-function");
    return ExecResult::make_value(std::make_shared<Value>(Value::Void()));
  }

  // ===================== STATEMENTS =====================
  ExecResult execute_expression_statement(CompilationUnit &unit, ayla::ast::node::ExpressionStatementNode *node) {
    execute_node(unit, node->expression);
    return ExecResult::make_value(std::make_shared<Value>(Value::Void()));
  }

  ExecResult execute_block(CompilationUnit &unit, ayla::ast::node::BlockStatementNode *block) {

    ExecResult last = ExecResult::make_value(std::make_shared<Value>(Value::Void()));

    for (auto *stmt : block->statements) {
      last = execute_node(unit, stmt);
      if (last.is_return()) return last;
    }
    return last;
  }

  ExecResult execute_if(CompilationUnit &unit, ayla::ast::node::IfStatementNode *node) {
    auto cond = execute_node(unit, node->condition);
    if (cond.value->as_bool()) return execute_node(unit, node->then_block);

    if (node->else_block) return execute_node(unit, node->else_block);

    return ExecResult::make_value(std::make_shared<Value>(Value::Void()));
  }

  ExecResult execute_while(CompilationUnit &unit, ayla::ast::node::WhileStatementNode *node) {

    ExecResult last = ExecResult::make_value(std::make_shared<Value>(Value::Void()));

    while (execute_node(unit, node->condition).value->as_bool()) {
      last = execute_node(unit, node->body);
      if (last.is_return()) return last;
    }
    return last;
  }

  ExecResult execute_return(CompilationUnit &unit, ayla::ast::node::ReturnStatementNode *node) {
    if (!node->value) return ExecResult::make_return(std::make_shared<Value>(Value::Void()));

    return ExecResult::make_return(execute_node(unit, node->value).value);
  }

  // ===================== BINARY =====================
  ExecResult execute_binary(CompilationUnit &unit, ayla::ast::node::BinaryExpressionNode *node) {
    auto lhs = execute_node(unit, node->lhs).value;
    auto rhs = execute_node(unit, node->rhs).value;

    using BO = ayla::ast::BinaryOperation;
    switch (node->op) {
    case BO::Add: return ExecResult::make_value(std::make_shared<Value>(Value::Number(lhs->get_number() + rhs->get_number())));
    case BO::Subtract: return ExecResult::make_value(std::make_shared<Value>(Value::Number(lhs->get_number() - rhs->get_number())));
    case BO::Multiply: return ExecResult::make_value(std::make_shared<Value>(Value::Number(lhs->get_number() * rhs->get_number())));
    case BO::Divide: return ExecResult::make_value(std::make_shared<Value>(Value::Number(lhs->get_number() / rhs->get_number())));
    case BO::Equal: return ExecResult::make_value(std::make_shared<Value>(Value::Boolean(lhs->get_number() == rhs->get_number())));
    case BO::Less: return ExecResult::make_value(std::make_shared<Value>(Value::Boolean(lhs->get_number() < rhs->get_number())));
    case BO::LessEqual: return ExecResult::make_value(std::make_shared<Value>(Value::Boolean(lhs->get_number() <= rhs->get_number())));
    case BO::Greater: return ExecResult::make_value(std::make_shared<Value>(Value::Boolean(lhs->get_number() > rhs->get_number())));
    case BO::GreaterEqual: return ExecResult::make_value(std::make_shared<Value>(Value::Boolean(lhs->get_number() >= rhs->get_number())));
    default: return ExecResult::make_value(std::make_shared<Value>(Value::Null()));
    }
  }

  // ===================== VARIABLES =====================
  ExecResult execute_identifier(ayla::ast::node::IdentifierExpressionNode *Identifier) { return ExecResult::make_value(current_scope->get(Identifier->resolved_symbol_id)); }

  ExecResult execute_variable_declaration(CompilationUnit &unit, ayla::ast::node::VariableDeclarationNode *node) {

    std::shared_ptr<Value> val;

    if (node->initializer) {
      val = execute_node(unit, node->initializer).value;
    } else {
      val = std::make_shared<Value>(Value::Null());
    }

    auto *id_pattern = static_cast<ayla::ast::IdentifierPatternNode *>(node->pattern);

    current_scope->set(id_pattern->symbol_id, val);

    return ExecResult::make_value(std::make_shared<Value>(Value::Void()));
  }

  ExecResult execute_assignment(CompilationUnit &unit, ayla::ast::node::AssignmentExpressionNode *node) {
    auto rhs = execute_node(unit, node->value).value;

    // a = ...
    if (node->target->kind == ayla::ast::NodeKind::Identifier) {
      auto *id = static_cast<ayla::ast::node::IdentifierExpressionNode *>(node->target);
      current_scope->set(id->resolved_symbol_id, rhs);
      return ExecResult::make_value(rhs);
    }

    // a[i] = ...
    if (node->target->kind == ayla::ast::NodeKind::IndexAccess) {
      auto *idx = static_cast<ayla::ast::node::IndexAccessNode *>(node->target);

      auto base = execute_node(unit, idx->base).value;
      auto index = execute_node(unit, idx->index).value;

      if (!base->is_array()) throw std::runtime_error("Index assignment on non-array");

      size_t i = static_cast<size_t>(index->get_number());
      auto &arr = base->get_array();

      if (i >= arr.size()) throw std::runtime_error("Array index out of bounds");

      arr[i] = rhs;
      return ExecResult::make_value(rhs);
    }

    throw std::runtime_error("Invalid assignment target");
  }

  ExecResult execute_function_declaration(CompilationUnit &unit, ayla::ast::node::FunctionDeclarationNode *node) {

    current_scope->set(node->symbol_id, std::make_shared<Value>(Value::User(node, current_scope)));

    return ExecResult::make_value(std::make_shared<Value>(Value::Void()));
  }
  // ===================== ENTRY =====================
  void execute_ast(CompilationUnit &unit) {
    if (!unit.diagns.all().empty()) return;
    for (auto *n : unit.ast.get_nodes()) execute_node(unit, n);
  }
};