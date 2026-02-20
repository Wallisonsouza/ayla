#pragma once

#include <algorithm>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <vector>

#include "ast/PatternNode.hpp"
#include "ast/expressions/AssignmentExpression.hpp"
#include "ast/expressions/BinaryExpressionNode.hpp"
#include "ast/expressions/CallExpressionNode.hpp"
#include "ast/expressions/LiteralExpressionNode.hpp"

#include "ast/statements/BlockStatementNode.hpp"
#include "ast/statements/ExpressionStatementNode.hpp"
#include "ast/statements/FunctionDeclarationNode.hpp"
#include "ast/statements/ImportStatementNode.hpp"
#include "ast/statements/ReturnStatementNodes.hpp"
#include "ast/statements/VariableDeclarationNode.hpp"

#include "runtime/Instruction.hpp"
#include "runtime/value/value.hpp"
#include "semantic/symbols/SymbolId.hpp"

//////////////////////////////////////////////////////
// LOCALS E SCOPE
//////////////////////////////////////////////////////

struct Local {
  SymbolId symbol;
  uint16_t reg;
  uint32_t depth;
};

struct Frame {
  uint32_t depth = 0;
  std::vector<Local> locals;

  void enter_scope() { depth++; }
  void leave_scope() {
    locals.erase(std::remove_if(locals.begin(), locals.end(), [this](const Local &l) { return l.depth == depth; }), locals.end());
    depth--;
  }
};

struct CodeFunction {
  static constexpr uint8_t MAX_REGISTERS = 250;

  uint32_t arity = 0;
  uint32_t local_count = 0;

  std::vector<Instruction> code;
  uint8_t next_reg = 0;
  uint8_t max_reg = 0;

  Frame frame;

  uint8_t alloc_reg() {
    if (next_reg >= MAX_REGISTERS) throw std::runtime_error("Exceeded maximum number of registers in function");
    uint8_t r = next_reg++;
    if (next_reg > max_reg) max_reg = next_reg;
    return r;
  }

  uint8_t alloc_local(SymbolId sym) {
    uint8_t r = alloc_reg();
    frame.locals.push_back({sym, r, frame.depth});
    return r;
  }

  std::optional<uint8_t> resolve_local(SymbolId sym) {
    for (int i = (int)frame.locals.size() - 1; i >= 0; --i)
      if (frame.locals[i].symbol == sym) return frame.locals[i].reg;
    return std::nullopt;
  }

  void enter_scope() { frame.enter_scope(); }
  void leave_scope() { frame.leave_scope(); }

  void finalize() { local_count = max_reg; }
};

struct GenModule {
  std::vector<Value> constants;
  std::vector<CodeFunction> functions;
};

struct BytecodeGenerator {
  GenModule *module;
  CodeFunction main_function;
  CodeFunction *current_function;

  BytecodeGenerator(GenModule *m) : module(m), current_function(&main_function) {}

  //////////////////////////////////////////////////////
  // CONSTANTS
  //////////////////////////////////////////////////////

  uint32_t add_constant(const Value &v) {
    module->constants.push_back(v);
    return module->constants.size() - 1;
  }

  //////////////////////////////////////////////////////
  // EMIT
  //////////////////////////////////////////////////////

  void emit(const Instruction &i) { current_function->code.push_back(i); }

  //////////////////////////////////////////////////////
  // EXPRESSIONS
  //////////////////////////////////////////////////////

  uint16_t gen_expr(ayla::ast::AstNode *node) {
    auto dst = current_function->alloc_reg();
    return gen_expr_into(node, dst);
  }

  uint16_t gen_expr_into(ayla::ast::AstNode *node, uint16_t dst) {
    using NK = ayla::ast::NodeKind;

    switch (node->kind) {
    case NK::NumberLiteral: {
      auto *n = static_cast<ayla::ast::node::NumberLiteralNode *>(node);
      uint32_t k = add_constant(Value::Number(n->value));
      emit(Instruction::LoadK(dst, k));
      return dst;
    }

    case NK::StringLiteral: {
      auto *s = static_cast<ayla::ast::node::StringLiteralNode *>(node);
      uint32_t k = add_constant(Value::String(s->value));
      emit(Instruction::LoadK(dst, k));
      return dst;
    }

    case NK::BooleanLiteral: {
      auto *b = static_cast<ayla::ast::node::BoolLiteralNode *>(node);
      uint32_t k = add_constant(Value::Boolean(b->value));
      emit(Instruction::LoadK(dst, k));
      return dst;
    }

    case NK::Identifier: {
      auto *id = static_cast<ayla::ast::node::IdentifierExpressionNode *>(node);
      auto reg = current_function->resolve_local(id->resolved_symbol_id);
      if (!reg) throw std::runtime_error("Unresolved identifier");
      // emit(Instruction::MOVE(dst, *reg));
      return *reg;
    }

    case NK::BinaryExpression: {
      auto *bin = static_cast<ayla::ast::node::BinaryExpressionNode *>(node);
      uint16_t left = gen_expr(bin->lhs);
      uint16_t right = gen_expr(bin->rhs);

      OpCode op;
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
        throw std::runtime_error("Unhandled binary op");
      }

      emit(Instruction::ABC(op, dst, left, right));
      return dst;
    }

    case NK::CallExpression: {
      // auto *call = static_cast<ayla::ast::node::CallExpressionNode *>(node);
      // uint8_t arg_count = call->arguments.size();

      // uint16_t func_reg = current_function->alloc_reg();
      // gen_expr_into(call->callee, func_reg);

      // std::vector<uint16_t> arg_regs(arg_count);
      // for (size_t i = 0; i < arg_count; ++i) {
      //   arg_regs[i] = current_function->alloc_reg();
      //   gen_expr_into(call->arguments[i], arg_regs[i]);
      // }

      // // CALL(func_reg, num_args=arg_count, retorno=1 registrador começando em func_reg)
      // emit(Instruction::CALL(func_reg, func_reg, arg_count));

      // // se dst não é o mesmo que o registrador da função, mover resultado
      // if (dst != func_reg) emit(Instruction::MOVE(dst, func_reg));

      // return dst;
    }

    default:
      throw std::runtime_error("Unhandled expression node");
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
      auto r = current_function->alloc_local(id->symbol_id);
      if (var->initializer) gen_expr_into(var->initializer, r);
      break;
    }

    case NK::AssignmentExpression: {
      auto *asg = static_cast<ayla::ast::node::AssignmentExpressionNode *>(node);
      auto *id = static_cast<ayla::ast::node::IdentifierExpressionNode *>(asg->target);
      auto reg = current_function->resolve_local(id->resolved_symbol_id);
      if (!reg) throw std::runtime_error("Unresolved assignment");
      gen_expr_into(asg->value, *reg);
      break;
    }

    case NK::ExpressionStatement: {
      auto *s = static_cast<ayla::ast::node::ExpressionStatementNode *>(node);
      gen_expr(s->expression);
      break;
    }

    case NK::ReturnStatement: {
      auto *r = static_cast<ayla::ast::node::ReturnStatementNode *>(node);
      if (r->value) {
        uint16_t val = gen_expr(r->value);
        emit(Instruction::MOVE(0, val));
      }
      emit(Instruction::RETURN());
      break;
    }

    case NK::FunctionDeclaration: {
      auto *fn = static_cast<ayla::ast::node::FunctionDeclarationNode *>(node);
      CodeFunction f;
      f.arity = fn->parameters.size();
      f.next_reg = f.arity;
      f.max_reg = f.arity;

      for (size_t i = 0; i < fn->parameters.size(); ++i) {
        auto *id = static_cast<ayla::ast::IdentifierPatternNode *>(fn->parameters[i]);
        f.frame.locals.push_back({id->symbol_id, (uint16_t)i, 0});
      }

      CodeFunction *prev = current_function;
      current_function = &f;

      generate_ast(fn->body->statements);
      f.finalize();

      module->functions.push_back(std::move(f));
      size_t idx = module->functions.size() - 1;

      current_function = prev;

      uint16_t reg = current_function->alloc_local(fn->symbol_id);
      uint32_t k = add_constant(Value::User(idx, fn->parameters.size()));
      emit(Instruction::LoadK(reg, k));

      break;
    }

    case NK::BlockStatement: {
      auto *b = static_cast<ayla::ast::node::BlockStatementNode *>(node);
      current_function->enter_scope();
      generate_ast(b->statements);
      current_function->leave_scope();
      break;
    }

    case NK::ImportStatement: {
      auto *imp = static_cast<ayla::ast::node::ImportStatementNode *>(node);
      uint32_t k = add_constant(Value::Module(imp->resolved_module_id));
      uint16_t dst = current_function->alloc_local(imp->resolved_symbol_id);
      emit(Instruction::LoadK(dst, k));
      break;
    }

    default:
      break;
    }
  }

  template <typename T> void generate_ast(const std::vector<T *> &nodes) {
    for (auto *n : nodes) { generate(static_cast<ayla::ast::AstNode *>(n)); }
  }

  void finalize_script() {
    main_function.finalize();
    module->functions.push_back(std::move(main_function));
    current_function = nullptr;
  }

  void print_bytecode() const {
    std::cout << "=== CONSTANTS ===\n";
    for (size_t i = 0; i < module->constants.size(); ++i) {
      const auto &val = module->constants[i];
      std::cout << "[" << std::setw(2) << i << "] " << val.convert_to_string() << "\n";
    }

    std::cout << "\n=== FUNCTIONS ===\n";
    for (size_t i = 0; i < module->functions.size(); ++i) {
      const CodeFunction &fn = module->functions[i];
      std::cout << "Function " << i << " (arity=" << fn.arity << ", locals=" << fn.local_count << ")\n";

      for (size_t j = 0; j < fn.code.size(); ++j) {
        const Instruction &instr = fn.code[j];
        std::cout << std::setw(4) << std::setfill('0') << j << "  " << instr.to_string(module->constants) << "\n";
      }
      std::cout << "\n";
    }
  }
};
