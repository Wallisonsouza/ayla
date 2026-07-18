#pragma once

#include "ast/expressions/AssignmentExpression.hpp"
#include "ast/expressions/BinaryExpressionNode.hpp"
#include "ast/expressions/CallExpressionNode.hpp"
#include "ast/expressions/IndexAcessExpressionNode.hpp"
#include "ast/expressions/LiteralExpressionNode.hpp"
#include "ast/expressions/MemberAccessExpressionNode.hpp"
#include "ast/expressions/UnaryExpressionNode.hpp"
#include "ast/statements/BlockStatementNode.hpp"
#include "ast/statements/ExpressionStatementNode.hpp"
#include "ast/statements/FunctionDeclarationNode.hpp"
#include "ast/statements/IfStatementNode.hpp"
#include "ast/statements/ImportStatementNode.hpp"
#include "ast/statements/ReturnStatementNodes.hpp"
#include "ast/statements/VariableDeclarationNode.hpp"
#include "ast/statements/WhileStatementNode.hpp"
#include "core/node/BinaryOp.hpp"

#include <stdexcept>
#include <string>
#include <vector>
#include "runtime/value/value.hpp"

enum class OpCode {
  NOP,
  PUSH_NUMBER,
  PUSH_STRING,
  PUSH_BOOLEAN,
  PUSH_NULL,
  PUSH_VOID,
  PUSH_OBJECT,
  PUSH_ARRAY,
  LOAD,
  STORE,
  LOAD_FIELD,
  STORE_FIELD,
  LOAD_INDEX,
  STORE_INDEX,
  ADD,
  SUB,
  MUL,
  DIV,
  EQ,
  LT,
  LTE,
  GT,
  GTE,
  NOT,
  JUMP,
  JUMP_IF_FALSE,
  CALL,
  RETURN,
  IMPORT,
  MODULE,
};

struct Instruction {
  OpCode op;
  SymbolId var_id = {};
  Value operand;
  size_t jump_target = 0;
  std::string name; // Para campos ou módulos

  Instruction(OpCode o) : op(o) {}
  Instruction(OpCode o, SymbolId id) : op(o), var_id(id) {}
  Instruction(OpCode o, const Value &v) : op(o), operand(v) {}
  Instruction(OpCode o, size_t target) : op(o), jump_target(target) {}
  Instruction(OpCode o, const std::string &n) : op(o), name(n) {}
};

struct BytecodeGenerator {
  std::vector<Instruction> code;

  BytecodeGenerator() = default;

  void emit(const Instruction &instr) { code.push_back(instr); }
  const std::vector<Instruction> &get_code() const { return code; }

  void generate_node(ayla::ast::AstNode *node) {
    if (!node) return;

    using NK = ayla::ast::NodeKind;

    switch (node->kind) {
    case NK::NumberLiteral: {
      auto n = static_cast<ayla::ast::node::NumberLiteralNode *>(node);
      emit(Instruction(OpCode::PUSH_NUMBER, Value::Number(n->value)));
      break;
    }
    case NK::StringLiteral: {
      auto s = static_cast<ayla::ast::node::StringLiteralNode *>(node);
      emit(Instruction(OpCode::PUSH_STRING, Value::String(s->value)));
      break;
    }
    case NK::BooleanLiteral: {
      auto b = static_cast<ayla::ast::node::BoolLiteralNode *>(node);
      emit(Instruction(OpCode::PUSH_BOOLEAN, Value::Boolean(b->value)));
      break;
    }
    case NK::Identifier: {
      auto id = static_cast<ayla::ast::node::IdentifierExpressionNode *>(node);
      emit(Instruction(OpCode::LOAD, id->resolved_symbol_id));
      break;
    }
    case NK::BinaryExpression: {
      auto bin = static_cast<ayla::ast::node::BinaryExpressionNode *>(node);
      generate_node(bin->lhs);
      generate_node(bin->rhs);
      using BO = ayla::ast::BinaryOperation;
      switch (bin->op) {
      case BO::Add: emit(Instruction(OpCode::ADD)); break;
      case BO::Subtract: emit(Instruction(OpCode::SUB)); break;
      case BO::Multiply: emit(Instruction(OpCode::MUL)); break;
      case BO::Divide: emit(Instruction(OpCode::DIV)); break;
      case BO::Equal: emit(Instruction(OpCode::EQ)); break;
      case BO::Less: emit(Instruction(OpCode::LT)); break;
      case BO::LessEqual: emit(Instruction(OpCode::LTE)); break;
      case BO::Greater: emit(Instruction(OpCode::GT)); break;
      case BO::GreaterEqual: emit(Instruction(OpCode::GTE)); break;
      default: throw std::runtime_error("Operador binário não implementado");
      }
      break;
    }
    case NK::UnaryExpression: {
      auto un = static_cast<ayla::ast::node::UnaryExpressionNode *>(node);
      generate_node(un->operand);
      if (un->op == ayla::UnaryOperation::NOT) emit(Instruction(OpCode::NOT));
      break;
    }
    case NK::VariableDeclaration: {
      auto var = static_cast<ayla::ast::node::VariableDeclarationNode *>(node);
      if (var->initializer)
        generate_node(var->initializer);
      else
        emit(Instruction(OpCode::PUSH_NULL));
      auto *id = static_cast<ayla::ast::IdentifierPatternNode *>(var->pattern);
      emit(Instruction(OpCode::STORE, id->symbol_id));
      break;
    }
    case NK::Assignment: {
      auto ass = static_cast<ayla::ast::node::AssignmentExpressionNode *>(node);
      generate_node(ass->value);
      switch (ass->target->kind) {
      case NK::Identifier: {
        auto *id = static_cast<ayla::ast::node::IdentifierExpressionNode *>(ass->target);
        emit(Instruction(OpCode::STORE, id->resolved_symbol_id));
        break;
      }
      default: throw std::runtime_error("Assignment target não suportado");
      }
      break;
    }
    case NK::ExpressionStatement: {
      auto es = static_cast<ayla::ast::node::ExpressionStatementNode *>(node);
      generate_node(es->expression);
      emit(Instruction(OpCode::PUSH_VOID));
      break;
    }
    default: break; // outros nodes podem ser adicionados da mesma forma
    }
  }

  void generate_ast(const std::vector<ayla::ast::AstNode *> &nodes) {
    for (auto *n : nodes) generate_node(n);
  }
};
