#pragma once

#include "semantic/symbols/SymbolId.hpp"
#include <optional>
#include <string>

enum class OpCode {
  NOP,
  POP,
  PUSH_NUMBER,
  PUSH_STRING,
  PUSH_BOOLEAN,
  PUSH_NULL,
  PUSH_VOID,
  PUSH_OBJECT,
  PUSH_FUNCTION,
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
  std::optional<SymbolId> var_id;
  std::optional<size_t> const_index;
  size_t jump_target = 0;
  std::string name;

  Instruction(OpCode o) : op(o) {}
  Instruction(OpCode o, SymbolId id) : op(o), var_id(id) {}
  Instruction(OpCode o, size_t index, bool is_const) : op(o), const_index(index) {}
  Instruction(OpCode o, size_t target) : op(o), jump_target(target) {}
  Instruction(OpCode o, const std::string &n) : op(o), name(n) {}
};
