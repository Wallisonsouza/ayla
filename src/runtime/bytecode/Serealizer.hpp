#include "runtime/bytecode/ByteCode.hpp"
#include <iostream>

inline std::string opcode_to_string(OpCode op) {
  switch (op) {
  case OpCode::NOP: return "NOP";
  case OpCode::PUSH_NUMBER: return "PUSH_NUMBER";
  case OpCode::PUSH_STRING: return "PUSH_STRING";
  case OpCode::PUSH_BOOLEAN: return "PUSH_BOOLEAN";
  case OpCode::PUSH_NULL: return "PUSH_NULL";
  case OpCode::PUSH_VOID: return "PUSH_VOID";
  case OpCode::PUSH_OBJECT: return "PUSH_OBJECT";
  case OpCode::PUSH_ARRAY: return "PUSH_ARRAY";
  case OpCode::LOAD: return "LOAD";
  case OpCode::STORE: return "STORE";
  case OpCode::LOAD_FIELD: return "LOAD_FIELD";
  case OpCode::STORE_FIELD: return "STORE_FIELD";
  case OpCode::LOAD_INDEX: return "LOAD_INDEX";
  case OpCode::STORE_INDEX: return "STORE_INDEX";
  case OpCode::ADD: return "ADD";
  case OpCode::SUB: return "SUB";
  case OpCode::MUL: return "MUL";
  case OpCode::DIV: return "DIV";
  case OpCode::EQ: return "EQ";
  case OpCode::LT: return "LT";
  case OpCode::LTE: return "LTE";
  case OpCode::GT: return "GT";
  case OpCode::GTE: return "GTE";
  case OpCode::NOT: return "NOT";
  case OpCode::JUMP: return "JUMP";
  case OpCode::JUMP_IF_FALSE: return "JUMP_IF_FALSE";
  case OpCode::CALL: return "CALL";
  case OpCode::RETURN: return "RETURN";
  case OpCode::IMPORT: return "IMPORT";
  case OpCode::MODULE: return "MODULE";
  }
  return "UNKNOWN";
}

inline std::string serialize_instruction(const Instruction &instr) {
  std::string s = opcode_to_string(instr.op);

  if (instr.var_id.value != 0) s += " var_id=" + std::to_string(instr.var_id.value);
  if (instr.operand.is_number()) s += " value=" + std::to_string(instr.operand.get_number());
  if (!instr.name.empty()) s += " name=" + instr.name;
  if (instr.jump_target != 0) s += " jump_target=" + std::to_string(instr.jump_target);

  return s;
}

inline void serialize_bytecode(const std::vector<Instruction> &code) {
  for (size_t i = 0; i < code.size(); ++i) { std::cout << i << ": " << serialize_instruction(code[i]) << "\n"; }
}
