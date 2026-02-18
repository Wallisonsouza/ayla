#pragma once

#include "ast/PatternNode.hpp"
#include "ast/expressions/AssignmentExpression.hpp"
#include "ast/expressions/BinaryExpressionNode.hpp"
#include "ast/expressions/CallExpressionNode.hpp"
#include "ast/expressions/LiteralExpressionNode.hpp"
#include "ast/expressions/MemberAccessExpressionNode.hpp"
#include "ast/statements/BlockStatementNode.hpp"
#include "ast/statements/ExpressionStatementNode.hpp"
#include "ast/statements/FunctionDeclarationNode.hpp"
#include "ast/statements/ImportStatementNode.hpp"
#include "ast/statements/VariableDeclarationNode.hpp"

#include "core/node/BinaryOp.hpp"
#include "runtime/Instruction.hpp"
#include "runtime/value/value.hpp"
#include "semantic/symbols/SymbolId.hpp"

struct BytecodeGenerator {
  std::vector<Instruction> code;
  std::vector<Value> constant_pool;
  std::vector<std::vector<Instruction>> function_pool;

  // ================= Pools =================

  size_t add_constant(const Value &v) {
    constant_pool.push_back(v);
    return constant_pool.size() - 1;
  }

  size_t add_function(std::vector<Instruction> &&fn_code) {
    function_pool.push_back(std::move(fn_code));
    return function_pool.size() - 1;
  }

  void emit(const Instruction &i) { code.push_back(i); }

  // ================= AST =================

  template <typename T> void generate_ast(const std::vector<T *> &nodes) {
    for (auto *n : nodes) generate_node(static_cast<ayla::ast::AstNode *>(n));
  }

  void generate_node(ayla::ast::AstNode *node) {
    if (!node) return;

    using NK = ayla::ast::NodeKind;

    switch (node->kind) {

      // ---------- Literais ----------

    case NK::NumberLiteral: {
      auto *n = static_cast<ayla::ast::node::NumberLiteralNode *>(node);
      size_t idx = add_constant(Value::Number(n->value));
      emit({OpCode::PUSH_NUMBER, idx, true});
      break;
    }

    case NK::StringLiteral: {
      auto *s = static_cast<ayla::ast::node::StringLiteralNode *>(node);
      size_t idx = add_constant(Value::String(s->value));
      emit({OpCode::PUSH_STRING, idx, true});
      break;
    }

      // ---------- Identifiers ----------

    case NK::Identifier: {
      auto *id = static_cast<ayla::ast::node::IdentifierExpressionNode *>(node);
      emit({OpCode::LOAD, id->resolved_symbol_id});
      break;
    }

      // ---------- Variable Declaration ----------

    case NK::VariableDeclaration: {
      auto *var = static_cast<ayla::ast::node::VariableDeclarationNode *>(node);

      if (var->initializer)
        generate_node(var->initializer);
      else
        emit({OpCode::PUSH_NULL});

      if (auto *id = dynamic_cast<ayla::ast::IdentifierPatternNode *>(var->pattern)) { emit({OpCode::STORE, id->symbol_id}); }
      break;
    }

      // ---------- Assignment ----------

    case NK::AssignmentExpression: {
      auto *asg = static_cast<ayla::ast::node::AssignmentExpressionNode *>(node);

      generate_node(asg->value);

      if (auto *id = dynamic_cast<ayla::ast::node::IdentifierExpressionNode *>(asg->target)) { emit({OpCode::STORE, id->resolved_symbol_id}); }
      break;
    }

      // ---------- Binary ----------

    case NK::BinaryExpression: {
      auto *bin = static_cast<ayla::ast::node::BinaryExpressionNode *>(node);

      generate_node(bin->lhs);
      generate_node(bin->rhs);

      switch (bin->op) {
      case ayla::ast::BinaryOperation::Add: emit({OpCode::ADD}); break;
      case ayla::ast::BinaryOperation::Subtract: emit({OpCode::SUB}); break;
      case ayla::ast::BinaryOperation::Multiply: emit({OpCode::MUL}); break;
      case ayla::ast::BinaryOperation::Divide: emit({OpCode::DIV}); break;
      default: break;
      }
      break;
    }

      // ---------- Call ----------

    case NK::CallExpression: {
      auto *call = static_cast<ayla::ast::node::CallExpressionNode *>(node);

      generate_node(call->callee);
      for (auto *a : call->arguments) generate_node(a);

      emit({OpCode::CALL, call->arguments.size()});
      break;
    }

      // ---------- Function ----------

    case NK::FunctionDeclaration: {
      auto *fn = static_cast<ayla::ast::node::FunctionDeclarationNode *>(node);

      BytecodeGenerator fn_gen;
      fn_gen.generate_ast(fn->body->statements);

      // RETURN implícito
      fn_gen.emit({OpCode::PUSH_NULL});
      fn_gen.emit({OpCode::RETURN});

      std::vector<SymbolId> params;
      for (auto *p : fn->parameters)
        if (auto *id = dynamic_cast<ayla::ast::IdentifierPatternNode *>(p)) params.push_back(id->symbol_id);

      size_t fn_idx = add_function(std::move(fn_gen.code));

      size_t cidx = add_constant(Value::User(fn_idx, std::move(params), nullptr));

      emit({OpCode::PUSH_OBJECT, cidx, true});
      emit({OpCode::STORE, fn->symbol_id});
      break;
    }

      // ---------- Block ----------

    case NK::BlockStatement: {
      auto *b = static_cast<ayla::ast::node::BlockStatementNode *>(node);
      generate_ast(b->statements);
      break;
    }

    // ---------- Expression stmt ----------
    case NK::ExpressionStatement: {
      auto *s = static_cast<ayla::ast::node::ExpressionStatementNode *>(node);
      generate_node(s->expression);
      emit({OpCode::POP});
      break;
    }

    // ---------- Member access ----------
    case NK::MemberAccessExpression: {
      auto *m = static_cast<ayla::ast::node::MemberAccessExpressionNode *>(node);

      generate_node(m->base);

      size_t idx = add_constant(Value::String(m->field->name));
      emit({OpCode::LOAD_FIELD, idx, true});
      break;
    }

    // ---------- Import ----------
    case NK::ImportStatement: {
      auto *imp = static_cast<ayla::ast::node::ImportStatementNode *>(node);

      size_t idx = add_constant(Value::Module(imp->resolved_module_id));

      emit({OpCode::IMPORT, idx, true});
      emit({OpCode::STORE, imp->resolved_symbol_id});
      break;
    }

    default: break;
    }
  }
};
