#pragma once
#include "runtime/value/value.hpp"
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

namespace ayla::runtime {
enum class OpCode { LOADK, MOVE, GEN_TABLE, GET_ARRAY, SET_TABLE, GEN_ARRAY, SET_ARRAY, ADD, SUB, MUL, DIV, LOAD, STORE, GET_TABLE, STORE_FIELD, CALL, RETURN, JUMP, JUMP_IF_FALSE, IMPORT, NOP };

inline static std::string opcode_to_string(OpCode op) {
  switch (op) {
  case OpCode::LOADK:
    return "LOADK";

  // table
  case OpCode::GEN_TABLE:
    return "GEN_TABLE";
  case OpCode::GET_TABLE:
    return "GET_TABLE";
  case OpCode::SET_TABLE:
    return "SET_TABLE";

  // array
  case OpCode::GEN_ARRAY:
    return "GEN_ARRAY";
  case OpCode::GET_ARRAY:
    return "GET_ARRAY";
  case OpCode::SET_ARRAY:
    return "SET_ARRAY";

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

struct Register {
  OpCode op;
  uint8_t A = UINT8_MAX;
  uint8_t B = UINT8_MAX;
  uint8_t C = UINT8_MAX;
  uint32_t K = UINT32_MAX;
  std::string key;

  Register(OpCode op) : op(op) {}

  static Register ABC(OpCode op, uint8_t A, uint8_t B, uint8_t C) {
    Register r(op);
    r.A = A;
    r.B = B;
    r.C = C;
    return r;
  }

  static Register LOADK(uint8_t A, uint32_t K) {
    Register r(OpCode::LOADK);
    r.A = A;
    r.K = K;
    return r;
  }

  static Register MOVE(uint8_t A, uint8_t B) {
    Register r(OpCode::MOVE);
    r.A = A;
    r.B = B;
    return r;
  }

  static Register GEN_ARRAY(uint8_t dst, uint32_t length) {
    Register r(OpCode::GEN_ARRAY);
    r.A = dst;
    r.K = length;
    return r;
  }
  static Register GET_ARRAY(uint8_t dst, uint8_t array_reg, uint32_t idx) {
    Register r(OpCode::GET_ARRAY);
    r.A = dst;
    r.B = array_reg;
    r.K = idx;
    return r;
  }
  static Register SET_ARRAY(uint8_t array_reg, uint32_t idx, uint8_t val_reg) {
    Register r(OpCode::SET_ARRAY);
    r.A = array_reg;
    r.B = val_reg;
    r.K = idx;
    return r;
  }

  static Register GEN_TABLE(uint8_t dst, uint32_t length) {
    Register r(OpCode::GEN_TABLE);
    r.A = dst;
    r.K = length;
    return r;
  }
  static Register GET_TABLE(uint8_t dst, uint8_t table_reg, const std::string &key) {
    Register r(OpCode::GET_TABLE);
    r.A = dst;
    r.B = table_reg;
    r.key = key;
    return r;
  }
  static Register SET_TABLE(uint8_t table_reg, const std::string &key, uint8_t val_reg) {
    Register r(OpCode::SET_TABLE);
    r.A = table_reg;
    r.B = val_reg;
    r.key = key;
    return r;
  }

  static Register CALL(uint8_t A, uint8_t B, uint8_t C) {
    Register r(OpCode::CALL);
    r.A = A;
    r.B = B;
    r.C = C;
    return r;
  }

  std::string to_string(const std::vector<Value> &constants) const {
    std::ostringstream out;
    out << std::left << std::setw(16) << opcode_to_string(op);

    switch (op) {
    case OpCode::LOADK:
      out << " R" << unsigned(A) << ", K" << K;
      if (K < constants.size()) out << " ; " << constants[K].convert_to_string();
      break;

    case OpCode::GEN_ARRAY:
      out << " R" << unsigned(A);
      if (K != UINT32_MAX) out << "[" << K << "]";
      break;

    case OpCode::GET_ARRAY:
      out << " R" << unsigned(A) << " = R" << unsigned(B) << "[" << K << "]";
      break;

    case OpCode::SET_ARRAY:
      out << " R" << unsigned(A) << "[" << K << "] = R" << unsigned(B);
      break;

    case OpCode::GEN_TABLE:
      out << " R" << unsigned(A);
      if (K != UINT32_MAX) out << "[" << K << "]";
      break;

    case OpCode::GET_TABLE:
      out << " R" << unsigned(A) << " = R" << unsigned(B) << "[\"" << key << "\"]";
      break;

    case OpCode::SET_TABLE:
      out << " R" << unsigned(A) << "[\"" << key << "\"] = R" << unsigned(B);
      break;

    case OpCode::MOVE:
      out << " R" << unsigned(A) << ", R" << unsigned(B);
      break;

    case OpCode::CALL:
      out << " R" << unsigned(A) << ", R" << unsigned(B) << ", " << unsigned(C);
      break;

    default:
      if (A != UINT8_MAX) out << " R" << unsigned(A);
      if (B != UINT8_MAX) out << ", R" << unsigned(B);
      if (C != UINT8_MAX) out << ", R" << unsigned(C);
      break;
    }

    return out.str();
  }
};
struct RegisterAllocator {
  static constexpr uint8_t MAX = 250;
  uint8_t next = 0;
  uint8_t peak = 0;

  uint8_t alloc() {
    if (next >= MAX) throw std::runtime_error("Too many registers");
    uint8_t r = next++;
    peak = std::max(peak, next);
    return r;
  }

  void reset(uint8_t start = 0) {
    next = start;
    peak = start;
  }
  uint8_t used() const { return peak; }
  uint8_t mark() const { return next; }
  void free_to(uint8_t m) {
    if (m <= next) next = m;
  }
};
} // namespace ayla::runtime