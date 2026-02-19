#pragma once

#include <cstdint>
#include <optional>
#include <stdexcept>
#include <vector>

#include "ast/PatternNode.hpp"
#include "ast/expressions/AssignmentExpression.hpp"
#include "ast/expressions/BinaryExpressionNode.hpp"
#include "ast/expressions/CallExpressionNode.hpp"
#include "ast/expressions/LiteralExpressionNode.hpp"
#include "ast/expressions/MemberAccessExpressionNode.hpp"

#include "ast/statements/BlockStatementNode.hpp"

#include "ast/statements/ExpressionStatementNode.hpp"
#include "ast/statements/ImportStatementNode.hpp"
#include "ast/statements/ReturnStatementNodes.hpp"
#include "ast/statements/VariableDeclarationNode.hpp"

#include "debug/engine/node/ast_debug.hpp"
#include "runtime/Instruction.hpp"
#include "runtime/value/value.hpp"
#include "semantic/symbols/SymbolId.hpp"

//////////////////////////////////////////////////////
// LOCALS
//////////////////////////////////////////////////////

struct Local {
  SymbolId symbol;
  uint16_t reg;
  uint32_t depth; // scope depth
};

//////////////////////////////////////////////////////
// FUNCTION
//////////////////////////////////////////////////////

struct CodeFunction {
  uint32_t arity = 0;
  uint32_t local_count = 0;
  std::vector<Instruction> code;
  std::vector<Local> locals; // locals da função
  uint16_t next_reg = 0;     // próximo registrador disponível
};

//////////////////////////////////////////////////////
// MODULE
//////////////////////////////////////////////////////

struct GenModule {
  std::vector<Value> constants;
  std::vector<CodeFunction> functions;
};

//////////////////////////////////////////////////////
// BYTECODE GENERATOR
//////////////////////////////////////////////////////

struct BytecodeGenerator {
  GenModule *module;

  CodeFunction main_function;     // função top-level
  CodeFunction *current_function; // ponteiro para função atual (main ou interna)
  uint32_t scope_depth = 0;       // depth para blocos

  BytecodeGenerator(GenModule *m) : module(m) {
    current_function = &main_function; // top-level ativo desde o início
  }

  //////////////////////////////////////////////////////
  // CONSTANTS
  //////////////////////////////////////////////////////

  uint32_t add_constant(const Value &v) {
    module->constants.push_back(v);
    return module->constants.size() - 1;
  }

  //////////////////////////////////////////////////////
  // REGISTERS / LOCALS
  //////////////////////////////////////////////////////

  uint16_t alloc_reg() { return current_function->next_reg++; }

  uint16_t declare_local(SymbolId sym) {
    uint16_t r = alloc_reg();
    current_function->locals.push_back({sym, r, scope_depth});
    return r;
  }

  std::optional<uint16_t> resolve_local(SymbolId sym) {
    for (int i = (int)current_function->locals.size() - 1; i >= 0; --i)
      if (current_function->locals[i].symbol == sym) return current_function->locals[i].reg;
    return std::nullopt;
  }

  //////////////////////////////////////////////////////
  // SCOPE
  //////////////////////////////////////////////////////

  void enter_scope() { scope_depth++; }

  void leave_scope() {
    scope_depth--;
    while (!current_function->locals.empty() && current_function->locals.back().depth > scope_depth) current_function->locals.pop_back();
  }

  //////////////////////////////////////////////////////
  // EMIT
  //////////////////////////////////////////////////////

  void emit(const Instruction &i) { current_function->code.push_back(i); }

  //////////////////////////////////////////////////////
  // EXPRESSIONS
  //////////////////////////////////////////////////////

  uint16_t gen_expr(ayla::ast::AstNode *node) {
    using NK = ayla::ast::NodeKind;

    switch (node->kind) {
    case NK::NumberLiteral: {
      auto *n = static_cast<ayla::ast::node::NumberLiteralNode *>(node);
      uint16_t r = alloc_reg();
      uint32_t k = add_constant(Value::Number(n->value));
      emit(Instruction::LoadK(r, k));
      return r;
    }
    case NK::StringLiteral: {
      auto *s = static_cast<ayla::ast::node::StringLiteralNode *>(node);
      uint16_t r = alloc_reg();
      uint32_t k = add_constant(Value::String(s->value));
      emit(Instruction::LoadK(r, k));
      return r;
    }
    case NK::BooleanLiteral: {
      auto *b = static_cast<ayla::ast::node::BoolLiteralNode *>(node);
      uint16_t r = alloc_reg();
      uint32_t k = add_constant(Value::Boolean(b->value));
      emit(Instruction::LoadK(r, k));
      return r;
    }
    case NK::Identifier: {
      auto *id = static_cast<ayla::ast::node::IdentifierExpressionNode *>(node);
      auto reg = resolve_local(id->resolved_symbol_id);
      if (!reg) throw std::runtime_error("Unresolved local identifier");
      return *reg;
    }
    case NK::BinaryExpression: {
      auto *bin = static_cast<ayla::ast::node::BinaryExpressionNode *>(node);
      uint16_t L = gen_expr(bin->lhs);
      uint16_t R = gen_expr(bin->rhs);
      uint16_t D = alloc_reg();
      OpCode op = OpCode::ADD;
      switch (bin->op) {
      case ayla::ast::BinaryOperation::Add:
        op = OpCode::ADD;
        break;
      case ayla::ast::BinaryOperation::Subtract:
        op = OpCode::SUB;
        break;
      case ayla::ast::BinaryOperation::Multiply:
        op = OpCode::MUL;
        break;
      case ayla::ast::BinaryOperation::Divide:
        op = OpCode::DIV;
        break;
      default:
        break;
      }
      emit(Instruction::ABC(op, D, L, R));
      return D;
    }
    case NK::CallExpression: {
      auto *call = static_cast<ayla::ast::node::CallExpressionNode *>(node);
      uint16_t fn = gen_expr(call->callee);
      std::vector<uint16_t> args;
      for (auto *a : call->arguments) args.push_back(gen_expr(a));
      uint16_t dst = alloc_reg();
      emit(Instruction::ABC(OpCode::CALL, dst, fn, args.size()));
      return dst;
    }
    case NK::MemberAccessExpression: {
      auto *m = static_cast<ayla::ast::node::MemberAccessExpressionNode *>(node);
      uint16_t base = gen_expr(m->base);
      uint16_t dst = alloc_reg();
      uint32_t k = add_constant(Value::String(m->field->name));
      emit(Instruction::ABC(OpCode::LOAD_FIELD, dst, base, 0));
      emit(Instruction::AB(OpCode::LOADK, dst, k));
      return dst;
    }
    default:
      throw std::runtime_error("Unhandled expression node kind");
    }
  }

  //////////////////////////////////////////////////////
  // STATEMENTS
  //////////////////////////////////////////////////////

  void generate(ayla::ast::AstNode *node) {
    using NK = ayla::ast::NodeKind;

    switch (node->kind) {
    case NK::VariableDeclaration: {
      auto *var = static_cast<ayla::ast::node::VariableDeclarationNode *>(node);
      auto *id = static_cast<ayla::ast::IdentifierPatternNode *>(var->pattern);
      uint16_t r = declare_local(id->symbol_id);
      if (var->initializer) {
        uint16_t val = gen_expr(var->initializer);
        emit(Instruction::AB(OpCode::MOVE, r, val));
      }
      break;
    }
    case NK::AssignmentExpression: {
      auto *asg = static_cast<ayla::ast::node::AssignmentExpressionNode *>(node);
      uint16_t val = gen_expr(asg->value);
      auto *id = static_cast<ayla::ast::node::IdentifierExpressionNode *>(asg->target);
      auto reg = resolve_local(id->resolved_symbol_id);
      if (!reg) throw std::runtime_error("Unresolved assignment target");
      emit(Instruction::AB(OpCode::MOVE, *reg, val));
      break;
    }
    case NK::ExpressionStatement: {
      auto *s = static_cast<ayla::ast::node::ExpressionStatementNode *>(node);
      gen_expr(s->expression);
      break;
    }
    case NK::ReturnStatement: {
      auto *r = static_cast<ayla::ast::node::ReturnStatementNode *>(node);
      uint16_t val = r->value ? gen_expr(r->value) : 0;
      emit(Instruction::AB(OpCode::RETURN, val, 0));
      break;
    }
    case NK::FunctionDeclaration: {
      auto *fn = static_cast<ayla::ast::node::FunctionDeclarationNode *>(node);

      CodeFunction f;
      f.arity = fn->parameters.size();
      CodeFunction *prev_fn = current_function;
      current_function = &f;

      // declarar parâmetros
      for (auto *p : fn->parameters) {
        auto *id = static_cast<ayla::ast::IdentifierPatternNode *>(p);
        declare_local(id->symbol_id);
      }

      generate_ast(fn->body->statements);

      f.local_count = current_function->next_reg;
      module->functions.push_back(std::move(f));
      size_t func_index = module->functions.size() - 1;

      current_function = prev_fn;

      if (current_function) {
        // Aqui é crítico: coloca a função em um registrador **antes de qualquer CALL**
        uint16_t reg = declare_local(fn->symbol_id);
        uint32_t k = add_constant(Value::User(func_index, fn->parameters.size()));
        emit(Instruction::LoadK(reg, k));
      }

      break;
    }

    case NK::BlockStatement: {
      enter_scope();
      auto *b = static_cast<ayla::ast::node::BlockStatementNode *>(node);
      generate_ast(b->statements);
      leave_scope();
      break;
    }
    case NK::ImportStatement: {
      auto *imp = static_cast<ayla::ast::node::ImportStatementNode *>(node);
      uint32_t k = add_constant(Value::Module(imp->resolved_module_id));
      uint16_t dst = declare_local(imp->resolved_symbol_id);
      emit(Instruction::LoadK(dst, k));
      break;
    }
    default:
      break;
    }
  }

  //////////////////////////////////////////////////////
  // AST DRIVER
  //////////////////////////////////////////////////////

  template <typename T> void generate_ast(const std::vector<T *> &nodes) {
    ASTDebug debug;
    for (auto *n : nodes) {
      debug.debug_node(n, true);
      generate(static_cast<ayla::ast::AstNode *>(n));
    }
  }

  //////////////////////////////////////////////////////
  // FINALIZE
  //////////////////////////////////////////////////////

  void finalize_script() {
    main_function.local_count = main_function.next_reg;
    module->functions.push_back(std::move(main_function));
    current_function = nullptr;
  }
};
