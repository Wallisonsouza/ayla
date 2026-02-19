#pragma once
#include <cstdint>
#include <iostream>

enum class OpCode {

  // data movement
  LOADK, // R[A] = K[B]
  MOVE,  // R[A] = R[B]

  // arithmetic
  ADD, // R[A] = R[B] + R[C]
  SUB,
  MUL,
  DIV,

  // variables
  LOAD,  // R[A] = local[B]
  STORE, // local[A] = R[B]

  // objects
  LOAD_FIELD,  // R[A] = R[B].K[C]
  STORE_FIELD, // R[A].K[B] = R[C]

  // calls
  CALL,   // CALL A B C  -> R[A] = R[B](R[B+1] ... argc=C)
  RETURN, // RETURN A

  // control flow
  JUMP,
  JUMP_IF_FALSE,

  // misc
  IMPORT,
  NOP
};

inline static std::string opcode_to_string(OpCode op) {
  switch (op) {
  case OpCode::LOADK: return "LOADK";
  case OpCode::MOVE: return "MOVE";
  case OpCode::ADD: return "ADD";
  case OpCode::SUB: return "SUB";
  case OpCode::MUL: return "MUL";
  case OpCode::DIV: return "DIV";
  case OpCode::LOAD: return "LOAD";
  case OpCode::STORE: return "STORE";
  case OpCode::LOAD_FIELD: return "LOAD_FIELD";
  case OpCode::STORE_FIELD: return "STORE_FIELD";
  case OpCode::CALL: return "CALL";
  case OpCode::RETURN: return "RETURN";
  case OpCode::JUMP: return "JUMP";
  case OpCode::JUMP_IF_FALSE: return "JUMP_IF_FALSE";
  case OpCode::IMPORT: return "IMPORT";
  case OpCode::NOP: return "NOP";
  default: return "UNKNOWN";
  }
}

struct Instruction {

  OpCode op;

  uint16_t A = 0;
  uint16_t B = 0;
  uint16_t C = 0;

  uint32_t K = 0;

  Instruction(OpCode op) : op(op) {}

  static Instruction LoadK(uint16_t A, uint32_t K) {
    Instruction i(OpCode::LOADK);
    i.A = A;
    i.K = K;
    return i;
  }

  static Instruction ABC(OpCode op, uint16_t A, uint16_t B, uint16_t C) {
    Instruction i(op);
    i.A = A;
    i.B = B;
    i.C = C;
    return i;
  }

  static Instruction AB(OpCode op, uint16_t A, uint16_t B) {
    Instruction i(op);
    i.A = A;
    i.B = B;
    return i;
  }

  void debug_print() const { std::cout << "Instruction: " << opcode_to_string(op) << " A=" << A << " B=" << B << " C=" << C << " K=" << K << "\n"; }
};
