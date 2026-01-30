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

  ExecResult execute_node(CompilationUnit &unit, core::ast::ASTNode *node) {
    if (!node) return ExecResult::make_value(Value::Null());

    switch (node->kind) {
    case core::ast::NodeKind::ExpressionStatement: {
      auto *es = static_cast<core::ast::ExpressionStatementNode *>(node);
      execute_node(unit, es->expr);
      return ExecResult::make_value(Value::Void());
    }

    case core::ast::NodeKind::Assignment: return execute_assignment(unit, static_cast<parser::node::statement::AssignmentNode *>(node));

    case core::ast::NodeKind::Identifier: return ExecResult::make_value(execute_identifier(static_cast<core::ast::IdentifierNode *>(node)->symbol_id));

    case core::ast::NodeKind::NumberLiteral: return ExecResult::make_value(Value::Number(static_cast<parser::node::NumberLiteralNode *>(node)->value));

    case core::ast::NodeKind::StringLiteral: return ExecResult::make_value(Value::String(static_cast<parser::node::StringLiteralNode *>(node)->value));

    case core::ast::NodeKind::BinaryExpression: return execute_binary(unit, static_cast<parser::node::BinaryExpressionNode *>(node));

    case core::ast::NodeKind::PathExpression: return ExecResult::make_value(execute_identifier(static_cast<parser::node::statement::PathExprNode *>(node)->symbol_id));

    case core::ast::NodeKind::FunctionCall: return execute_function_call(unit, static_cast<parser::node::FunctionCallNode *>(node));

    case core::ast::NodeKind::VariableDeclaration: return execute_variable_declaration(unit, static_cast<core::ast::PatternNode *>(node));

    case core::ast::NodeKind::BlockStatement: return execute_block(unit, static_cast<parser::node::BlockStatementNode *>(node));

    case core::ast::NodeKind::IfStatement: return execute_if(unit, static_cast<parser::node::IfStatementNode *>(node));

    case core::ast::NodeKind::WhileStatement: return execute_while(unit, static_cast<parser::node::ASTWhileStatementNode *>(node));

    case core::ast::NodeKind::FunctionDeclaration: return execute_function_declaration(unit, static_cast<parser::node::FunctionDeclarationNode *>(node));

    case core::ast::NodeKind::ReturnStatement: return execute_return(unit, static_cast<parser::node::ReturnStatementNode *>(node));

    default: return ExecResult::make_value(Value::Null());
    }
  }

  // ===================== EXECUTE BLOCK =====================
  ExecResult execute_block(CompilationUnit &unit, parser::node::BlockStatementNode *block) {
    if (!block) return ExecResult::make_value(Value::Void());

    ExecResult last = ExecResult::make_value(Value::Void());
    for (auto *stmt : block->statements) {
      last = execute_node(unit, stmt);
      if (last.is_return()) return last; // propaga return
    }

    return last;
  }

  // ===================== EXECUTE WHILE =====================
  ExecResult execute_while(CompilationUnit &unit, parser::node::ASTWhileStatementNode *node) {
    ExecResult last = ExecResult::make_value(Value::Void());

    while (true) {
      ExecResult cond = execute_node(unit, node->condition);
      if (!cond.value.as_bool()) break;

      last = execute_block(unit, node->block);
      if (last.is_return()) return last;
    }

    return last;
  }

  // ===================== EXECUTE IF =====================
  ExecResult execute_if(CompilationUnit &unit, parser::node::IfStatementNode *node) {
    if (!node || !node->condition) return ExecResult::make_value(Value::Void());

    ExecResult cond = execute_node(unit, node->condition);

    if (cond.value.as_bool()) {
      return execute_block(unit, node->if_block);
    } else {
      if (node->else_block)
        return execute_node(unit, node->else_block);
      else
        return ExecResult::make_value(Value::Void());
    }
  }

  // ===================== EXECUTE RETURN =====================
  ExecResult execute_return(CompilationUnit &unit, parser::node::ReturnStatementNode *node) {
    if (!node->value) return ExecResult::make_return(Value::Void());
    return ExecResult::make_return(execute_node(unit, node->value).value);
  }

  // ===================== EXECUTE IDENTIFIER =====================
  Value execute_identifier(SymbolId id) {
    if (id == INVALID_SYMBOL_ID) return Value::Null();
    return current_scope->get(id);
  }

  // ===================== EXECUTE ASSIGNMENT =====================
  ExecResult execute_assignment(CompilationUnit &unit, parser::node::statement::AssignmentNode *node) {
    Value val = execute_node(unit, node->value).value;

    if (auto *id = dynamic_cast<core::ast::IdentifierNode *>(node->target)) {
      current_scope->set(id->symbol_id, val);
    } else {
      throw std::runtime_error("Invalid assignment target");
    }

    return ExecResult::make_value(val);
  }

  // ===================== EXECUTE VARIABLE DECLARATION =====================
  ExecResult execute_variable_declaration(CompilationUnit &unit, core::ast::PatternNode *node) {
    Value val = node->value ? execute_node(unit, node->value).value : Value::Null();

    if (node->symbol_id == INVALID_SYMBOL_ID) throw std::runtime_error("Variable declaration has invalid symbol id");

    current_scope->set(node->symbol_id, val);
    return ExecResult::make_value(Value::Void());
  }

  // ===================== EXECUTE BINARY =====================
  ExecResult execute_binary(CompilationUnit &unit, parser::node::BinaryExpressionNode *node) {
    
    Value lhs = execute_node(unit, node->left).value;
    
    Value rhs = execute_node(unit, node->right).value;

    switch (node->op) {
    case core::ast::BinaryOperation::Add: return ExecResult::make_value(Value::Number(lhs.get_number() + rhs.get_number()));
    case core::ast::BinaryOperation::Subtract: return ExecResult::make_value(Value::Number(lhs.get_number() - rhs.get_number()));
    case core::ast::BinaryOperation::Multiply: return ExecResult::make_value(Value::Number(lhs.get_number() * rhs.get_number()));
    case core::ast::BinaryOperation::Divide: return ExecResult::make_value(Value::Number(lhs.get_number() / rhs.get_number()));
    case core::ast::BinaryOperation::Equal: return ExecResult::make_value(Value::Boolean(lhs.get_number() == rhs.get_number()));
    case core::ast::BinaryOperation::Less: return ExecResult::make_value(Value::Boolean(lhs.get_number() < rhs.get_number()));
    case core::ast::BinaryOperation::LessEqual: return ExecResult::make_value(Value::Boolean(lhs.get_number() <= rhs.get_number()));
    default: return ExecResult::make_value(Value::Null());
    }
  }

  // ===================== EXECUTE FUNCTION CALL =====================
  ExecResult execute_function_call(CompilationUnit &unit, parser::node::FunctionCallNode *node) {
    SymbolId id = INVALID_SYMBOL_ID;

    if (node->callee->kind == core::ast::NodeKind::Identifier)
      id = static_cast<core::ast::IdentifierNode *>(node->callee)->symbol_id;
    else if (node->callee->kind == core::ast::NodeKind::PathExpression)
      id = static_cast<parser::node::statement::PathExprNode *>(node->callee)->symbol_id;

    if (id == INVALID_SYMBOL_ID) return ExecResult::make_value(Value::Null());

    auto symbol = unit.symbols.get(id);
    if (!symbol) return ExecResult::make_value(Value::Null());

    Value func_val;
    if (symbol->declaration->kind == core::ast::NodeKind::NativeFunctionDeclaration) {
      func_val = Value::Native(static_cast<core::ast::NativeFunctionDeclarationNode *>(symbol->declaration)->callback);
    } else if (symbol->declaration->kind == core::ast::NodeKind::FunctionDeclaration) {
      func_val = Value::User(static_cast<parser::node::FunctionDeclarationNode *>(symbol->declaration), current_scope);
    } else {
      return ExecResult::make_value(Value::Null());
    }

    if (func_val.is_native_function()) {
      std::vector<Value> args;
      for (auto *arg : node->args) args.push_back(execute_node(unit, arg).value);
      return ExecResult::make_value(func_val.get_native()(args));
    }

    if (func_val.is_user_function()) {
      auto &fn = func_val.get_user_function();
      RuntimeScope new_scope(fn.captured_scope);
      for (size_t i = 0; i < node->args.size(); ++i) new_scope.set(fn.node->params[i]->symbol_id, execute_node(unit, node->args[i]).value);

      Executor executor(&new_scope);
      return executor.execute_block(unit, fn.node->body);
    }

    return ExecResult::make_value(Value::Null());
  }

  // ===================== EXECUTE FUNCTION DECLARATION =====================
  ExecResult execute_function_declaration(CompilationUnit &unit, parser::node::FunctionDeclarationNode *node) {
    Value func_val = Value::User(node, current_scope);
    current_scope->set(node->symbol_id, func_val);
    return ExecResult::make_value(Value::Void());
  }

  // ===================== EXECUTE AST =====================
  void execute_ast(CompilationUnit &unit) {
    if (unit.diagns.all().size() > 0) return;
    for (auto &resolved_node : unit.ast.get_nodes()) { execute_node(unit, resolved_node); }
  }
};
