#pragma once
#include "runtime/value/value.hpp"
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

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
  case OpCode::LOADK:
    return "LOADK";
  case OpCode::MOVE:
    return "MOVE";
  case OpCode::ADD:
    return "ADD";
  case OpCode::SUB:
    return "SUB";
  case OpCode::MUL:
    return "MUL";
  case OpCode::DIV:
    return "DIV";
  case OpCode::LOAD:
    return "LOAD";
  case OpCode::STORE:
    return "STORE";
  case OpCode::LOAD_FIELD:
    return "LOAD_FIELD";
  case OpCode::STORE_FIELD:
    return "STORE_FIELD";
  case OpCode::CALL:
    return "CALL";
  case OpCode::RETURN:
    return "RETURN";
  case OpCode::JUMP:
    return "JUMP";
  case OpCode::JUMP_IF_FALSE:
    return "JUMP_IF_FALSE";
  case OpCode::IMPORT:
    return "IMPORT";
  case OpCode::NOP:
    return "NOP";
  default:
    return "UNKNOWN";
  }
}

struct Instruction {

  OpCode op;

  uint16_t A = UINT16_MAX;
  uint16_t B = UINT16_MAX;
  uint16_t C = UINT16_MAX;

  uint32_t K = UINT32_MAX;

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

  static Instruction _A(OpCode op, uint16_t A) {
    Instruction i(op);
    i.A = A;
    return i;
  }

  static Instruction AB(OpCode op, uint16_t A, uint16_t B) {
    Instruction i(op);
    i.A = A;
    i.B = B;
    return i;
  }

  static Instruction MOVE(uint16_t A, uint16_t B) { return AB(OpCode::MOVE, A, B); }

  static Instruction CALL(uint16_t A, uint16_t B, uint16_t C) { return ABC(OpCode::CALL, A, B, C); }

  static Instruction RETURN() { return Instruction::_A(OpCode::RETURN, 0); }

  std::string to_string(const std::vector<Value> &constants) const {
    std::ostringstream out;

    out << std::left << std::setw(8) << opcode_to_string(op);

    switch (op) {
    case OpCode::LOADK:
      out << " R" << A << ", K" << K;
      if (K < constants.size()) out << "     ; " << constants[K].convert_to_string();
      break;

    case OpCode::MOVE:
      out << " R" << A << ", R" << B;
      break;

    case OpCode::CALL:
      out << " R" << A << ", R" << B << ", " << C;
      break;

    case OpCode::RETURN:
      out << " R" << A;
      break;

    default:
      if (A != UINT16_MAX) out << " R" << A;
      if (B != UINT16_MAX) out << ", R" << B;
      if (C != UINT16_MAX) out << ", R" << C;
      break;
    }

    return out.str();
  }
};
