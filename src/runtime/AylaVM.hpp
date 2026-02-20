#pragma once
#include "runtime/ByteCode.hpp"
#include "runtime/Instruction.hpp"
#include "runtime/value/value.hpp"

#include <iostream>
#include <stdexcept>
#include <vector>

struct ValueArena {
  std::vector<Value> buffer;

  size_t alloc(const Value &v) {
    buffer.push_back(v);
    return buffer.size() - 1;
  }

  size_t alloc_null() { return alloc(Value::Null()); }

  Value &get(size_t idx) { return buffer[idx]; }

  const Value &get(size_t idx) const { return buffer[idx]; }

  void reset() { buffer.clear(); }
};

struct StackFrame {
  size_t return_ip = 0;
  uint32_t function_idx = 0;
  size_t ip = 0;
  std::vector<size_t> registers;

  size_t get_register(size_t idx) const { return idx < registers.size() ? registers[idx] : SIZE_MAX; }

  void debug_print(const ValueArena &arena, size_t frame_index = 0) const {
    std::cout << "[Frame " << frame_index << "] return_ip=" << return_ip << " function_idx=" << function_idx << " ip=" << ip << "\n";

    for (size_t i = 0; i < registers.size(); ++i) {
      size_t reg_idx = registers[i];
      std::cout << "  R[" << i << "] = " << (reg_idx != SIZE_MAX ? arena.get(reg_idx).convert_to_string() : "null") << "\n";
    }
  }
};

struct AylaVM {
  std::vector<StackFrame> call_stack;
  const GenModule *module = nullptr;

  ValueArena arena;
  bool debug = true;

  void log(const std::string &msg) const {
    if (debug) std::cout << msg << "\n";
  }

  size_t safe_register(const StackFrame &frame, size_t idx) {
    if (idx >= frame.registers.size()) return arena.alloc_null();
    size_t reg_idx = frame.registers[idx];
    if (reg_idx >= arena.buffer.size()) return arena.alloc_null();
    return reg_idx;
  }

  void execute(const GenModule &m) {
    module = &m;
    if (module->functions.empty()) return;

    const size_t main_idx = module->functions.size() - 1;
    const CodeFunction &main_fn = module->functions[main_idx];

    StackFrame frame;
    frame.function_idx = main_idx;
    frame.ip = 0;
    frame.registers.resize(main_fn.local_count, SIZE_MAX);

    call_stack.push_back(std::move(frame));
    run();
  }

private:
  void run() {
    while (!call_stack.empty()) {
      StackFrame &frame = call_stack.back();
      const CodeFunction &fn = module->functions[frame.function_idx];

      // fim do frame
      if (frame.ip >= fn.code.size()) {
        handle_return(frame);
        continue;
      }

      const Instruction &instr = fn.code[frame.ip++];

      switch (instr.op) {
      case OpCode::LOADK:
        frame.registers[instr.A] = arena.alloc(module->constants[instr.K]);
        break;

      case OpCode::MOVE:
        frame.registers[instr.A] = safe_register(frame, instr.B);
        break;

      case OpCode::ADD:
      case OpCode::SUB:
      case OpCode::MUL:
      case OpCode::DIV:
        execute_binary_op(frame, instr);
        break;

      case OpCode::CALL:
        execute_call(frame, instr);
        break;

      case OpCode::RETURN:
        handle_return(frame, instr.A);
        break;

      default:
        throw std::runtime_error("Unhandled opcode");
      }
    }
  }

  void execute_binary_op(StackFrame &frame, const Instruction &instr) {
    size_t lhs_idx = safe_register(frame, instr.B);
    size_t rhs_idx = safe_register(frame, instr.C);

    double a = arena.get(lhs_idx).get_number();
    double b = arena.get(rhs_idx).get_number();
    double result = (instr.op == OpCode::ADD) ? a + b : (instr.op == OpCode::SUB) ? a - b : (instr.op == OpCode::MUL) ? a * b : a / b;

    frame.registers[instr.A] = arena.alloc(Value(result));

    std::cout << result;
  }

  void execute_call(StackFrame &frame, const Instruction &instr) {
    size_t fn_reg = instr.B;
    size_t fn_idx = safe_register(frame, fn_reg);
    Value &fn_val = arena.get(fn_idx);

    if (!fn_val.is_function()) throw std::runtime_error("Expected user function in CALL");

    auto function = fn_val.get_function();
    const CodeFunction &fn = module->functions[function.bytecode_index];

    StackFrame new_frame;
    new_frame.return_ip = frame.ip;
    new_frame.function_idx = function.bytecode_index;
    new_frame.ip = 0;
    new_frame.registers.resize(fn.local_count, SIZE_MAX);

    for (uint16_t i = 0; i < instr.C; i++) {
      size_t arg_reg = fn_reg + 1 + i;

      if (arg_reg >= frame.registers.size()) break;

      new_frame.registers[i] = safe_register(frame, arg_reg);
    }

    call_stack.push_back(std::move(new_frame));
  }

  void handle_return(StackFrame &frame, size_t ret_idx = 0) {
    size_t ret_val_idx = frame.registers.empty() ? arena.alloc_null() : safe_register(frame, ret_idx);

    call_stack.pop_back();
    if (call_stack.empty()) return;

    StackFrame &caller = call_stack.back();
    size_t dst = ret_idx < caller.registers.size() ? ret_idx : 0;
    caller.registers[dst] = ret_val_idx;
  }
};
