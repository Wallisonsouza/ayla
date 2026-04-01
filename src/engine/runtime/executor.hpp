#pragma once
#include "ayla-structural/ayla-ast/literal_nodes.hpp"
#include "ayla-structural/ayla-ast/operator_nodes.hpp"
#include "ayla-structural/ayla-ast/statement_nodes.hpp"
#include "ayla-structural/ayla-ast/statements/ImportStatement.hpp"
#include "core/memory/symbol.hpp"
#include "core/memory/value.hpp"
#include "core/module/module.hpp"
#include "core/node/BinaryOp.hpp"
#include "core/node/NodeKind.hpp"
#include "core/node/Type.hpp"
#include "debug/engine/node/ast_debug.hpp"
#include "engine/CompilationUnit.hpp"
#include "runtime_scope.hpp"
#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>

struct Executor {

  struct ScopeGuard {
    Executor *executor;
    RuntimeScope *prev_scope;
    RuntimeScope child_scope;

    ScopeGuard(Executor *ex) : executor(ex), prev_scope(ex->current_scope), child_scope(ex->current_scope) { executor->current_scope = &child_scope; }

    ~ScopeGuard() { executor->current_scope = prev_scope; }
  };

  RuntimeScope *current_scope;

  Executor(RuntimeScope *scope) : current_scope(scope) {}

  ExecResult execute_node(CompilationUnit &unit, core::ast::ASTNode *node) {
    if (!node) return ExecResult::make_value(std::make_shared<Value>(Value::Null()));

    switch (node->kind) {

    case core::ast::NodeKind::ExpressionStatement: return execute_expression_statement(unit, static_cast<core::ast::ExpressionStatementNode *>(node));

    case core::ast::NodeKind::Assignment: return execute_assignment(unit, static_cast<parser::node::statement::AssignmentNode *>(node));

    case core::ast::NodeKind::Identifier: return execute_identifier(static_cast<core::ast::IdentifierNode *>(node));

    case core::ast::NodeKind::NumberLiteral: return ExecResult::make_value(std::make_shared<Value>(Value::Number(static_cast<parser::node::NumberLiteralNode *>(node)->value)));

    case core::ast::NodeKind::StringLiteral: return ExecResult::make_value(std::make_shared<Value>(Value::String(static_cast<parser::node::StringLiteralNode *>(node)->value)));

    case core::ast::NodeKind::BinaryExpression: return execute_binary(unit, static_cast<parser::node::BinaryExpressionNode *>(node));

    case core::ast::NodeKind::MemberAccess: return execute_path(unit, static_cast<parser::node::MemberAccessNode *>(node));

    case core::ast::NodeKind::FunctionCall: return execute_function_call(unit, static_cast<parser::node::FunctionCallNode *>(node));

    case core::ast::NodeKind::VariableDeclaration: return execute_variable_declaration(unit, static_cast<core::ast::PatternNode *>(node));

    case core::ast::NodeKind::BlockStatement: return execute_block(unit, static_cast<parser::node::BlockStatementNode *>(node));

    case core::ast::NodeKind::IfStatement: return execute_if(unit, static_cast<parser::node::IfStatementNode *>(node));

    case core::ast::NodeKind::ArrayLiteral: return execute_array(unit, static_cast<parser::node::ASTArrayLiteralNode *>(node));

    case core::ast::NodeKind::IndexAccess: return execute_index_access(unit, static_cast<parser::node::IndexAccessNode *>(node));

    case core::ast::NodeKind::WhileStatement: return execute_while(unit, static_cast<parser::node::ASTWhileStatementNode *>(node));

    case core::ast::NodeKind::FunctionDeclaration: return execute_function_declaration(unit, static_cast<parser::node::FunctionDeclarationNode *>(node));

    case core::ast::NodeKind::ReturnStatement: return execute_return(unit, static_cast<parser::node::ReturnStatementNode *>(node));

    case core::ast::NodeKind::ModuleDeclaration: return execute_module_declaration(unit, static_cast<parser::node::statement::ModuleDeclarationNode *>(node));

    case core::ast::NodeKind::Import: return execute_import_node(unit, static_cast<parser::node::statement::ImportNode *>(node));

    default: return ExecResult::make_value(std::make_shared<Value>(Value::Null()));
    }
  }

  ExecResult execute_module_declaration(CompilationUnit &unit, parser::node::statement::ModuleDeclarationNode *node) { return ExecResult::make_value(std::make_shared<Value>(Value::Void())); }

  ExecResult execute_import_node(CompilationUnit &unit, parser::node::statement::ImportNode *node) {

    auto module_id = node->resolved_module_id;

    auto module = unit.context.module_manager.get(module_id);

    if (!module) { std::runtime_error("erro ao carregar modulo " + module->name); }

    module->ensure_initialized();

    std::cout << module->name << "\n";

    // auto module = unit.context.module_manager.get(node->resolved_module_id);
    // if (!module) throw std::runtime_error("Invalid module");

    // // Garante que o módulo seja inicializado (executa callbacks nativos)
    // module->ensure_initialized();

    // // Cria um Value do módulo como objeto
    // Value::ObjectFields fields;
    // for (auto &[sym_id, val] : module->runtime_scope.values) { fields[sym_id] = val; }

    // auto module_object = std::make_shared<Value>(Value::Object(std::move(fields)));

    // // Injetar no escopo atual
    // if (node->resolved_symbol_id.is_valid()) { current_scope->set(node->resolved_symbol_id, module_object); }

    // std::cout << "[Executor] Imported module '" << node->path.back()->name << "' as object with " << module_object->get_object_ref().size() << " fields.\n";

    return ExecResult::make_value(std::make_shared<Value>(Value::Void()));
  }

  ExecResult execute_function_call(CompilationUnit &unit, parser::node::FunctionCallNode *node) {

    ASTDebug debug;

    auto callee = execute_node(unit, node->callee).value;

    std::vector<Value> args;
    for (auto *arg_node : node->arguments) {

      debug.debug_node(arg_node, true);
      auto v = execute_node(unit, arg_node).value;
      args.push_back(*v);
    }

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
  ExecResult execute_expression_statement(CompilationUnit &unit, core::ast::ExpressionStatementNode *node) {
    execute_node(unit, node->expression);
    return ExecResult::make_value(std::make_shared<Value>(Value::Void()));
  }

  ExecResult execute_block(CompilationUnit &unit, parser::node::BlockStatementNode *block) {

    ScopeGuard guard(this);

    ExecResult last = ExecResult::make_value(std::make_shared<Value>(Value::Void()));

    for (auto *stmt : block->statements) {
      last = execute_node(unit, stmt);
      if (last.is_return()) return last;
    }
    return last;
  }

  ExecResult execute_if(CompilationUnit &unit, parser::node::IfStatementNode *node) {
    auto cond = execute_node(unit, node->condition);
    if (cond.value->as_bool()) return execute_block(unit, node->then_block);

    if (node->else_block) return execute_node(unit, node->else_block);

    return ExecResult::make_value(std::make_shared<Value>(Value::Void()));
  }

  ExecResult execute_while(CompilationUnit &unit, parser::node::ASTWhileStatementNode *node) {

    ExecResult last = ExecResult::make_value(std::make_shared<Value>(Value::Void()));

    while (execute_node(unit, node->condition).value->as_bool()) {
      last = execute_block(unit, node->body);
      if (last.is_return()) return last;
    }
    return last;
  }

  ExecResult execute_return(CompilationUnit &unit, parser::node::ReturnStatementNode *node) {
    if (!node->value) return ExecResult::make_return(std::make_shared<Value>(Value::Void()));

    return ExecResult::make_return(execute_node(unit, node->value).value);
  }

  // ===================== ARRAYS =====================
  ExecResult execute_array(CompilationUnit &unit, parser::node::ASTArrayLiteralNode *node) {
    Value::array elements;

    for (auto *el : node->elements) {
      auto v = execute_node(unit, el);
      if (v.is_return()) return v;
      elements.push_back(v.value);
    }

    return ExecResult::make_value(std::make_shared<Value>(Value::Array(std::move(elements))));
  }

  ExecResult execute_index_access(CompilationUnit &unit, parser::node::IndexAccessNode *node) {
    auto base = execute_node(unit, node->base).value;
    auto index = execute_node(unit, node->index).value;

    if (!base->is_array()) throw std::runtime_error("Index access on non-array");

    size_t i = static_cast<size_t>(index->get_number());
    auto &arr = base->get_array();

    if (i >= arr.size()) return ExecResult::make_value(std::make_shared<Value>(Value::Null()));

    return ExecResult::make_value(arr[i]);
  }

  // ===================== BINARY =====================
  ExecResult execute_binary(CompilationUnit &unit, parser::node::BinaryExpressionNode *node) {
    auto lhs = execute_node(unit, node->lhs).value;
    auto rhs = execute_node(unit, node->rhs).value;

    using BO = core::ast::BinaryOperation;
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
  ExecResult execute_identifier(core::ast::IdentifierNode *Identifier) { return ExecResult::make_value(current_scope->get(Identifier->resolved_symbol_id)); }

  ExecResult execute_path(CompilationUnit &unit, parser::node::MemberAccessNode *member) { return ExecResult::make_value(current_scope->get(member->resolved_symbol_id)); }

  ExecResult execute_variable_declaration(CompilationUnit &unit, core::ast::PatternNode *node) {
    auto val = node->value ? execute_node(unit, node->value).value : std::make_shared<Value>(Value::Null());

    current_scope->set(node->symbol_id, val);
    return ExecResult::make_value(std::make_shared<Value>(Value::Void()));
  }

  ExecResult execute_assignment(CompilationUnit &unit, parser::node::statement::AssignmentNode *node) {
    auto rhs = execute_node(unit, node->value).value;

    // a = ...
    if (node->target->kind == core::ast::NodeKind::Identifier) {
      auto *id = static_cast<core::ast::IdentifierNode *>(node->target);
      current_scope->set(id->resolved_symbol_id, rhs);
      return ExecResult::make_value(rhs);
    }

    // a[i] = ...
    if (node->target->kind == core::ast::NodeKind::IndexAccess) {
      auto *idx = static_cast<parser::node::IndexAccessNode *>(node->target);

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

  ExecResult execute_function_declaration(CompilationUnit &unit, parser::node::FunctionDeclarationNode *node) {

    if (node->native_fn) {
      current_scope->set(node->symbol_id, std::make_shared<Value>(Value::Native(*node->native_fn)));
    } else {
      current_scope->set(node->symbol_id, std::make_shared<Value>(Value::User(node, current_scope)));
    }

    return ExecResult::make_value(std::make_shared<Value>(Value::Void()));
  }
  // ===================== ENTRY =====================
  void execute_ast(CompilationUnit &unit) {
    if (!unit.diagns.all().empty()) return;
    for (auto *n : unit.ast.get_nodes()) execute_node(unit, n);
  }
};