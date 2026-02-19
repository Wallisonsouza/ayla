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
  const CodeFunction *current_function = nullptr;

  ValueArena arena;
  bool debug = true;

  void log(const std::string &msg) const {
    if (debug) std::cout << msg << "\n";
  }

  //////////////////////////////////////////////////////
  // Inicializa registradores com null
  //////////////////////////////////////////////////////
  void init_registers(StackFrame &frame) {
    for (auto &idx : frame.registers)
      if (idx == SIZE_MAX) idx = arena.alloc_null();
  }

  //////////////////////////////////////////////////////
  // EXECUÇÃO DE MÓDULO
  //////////////////////////////////////////////////////
  void execute(const GenModule &m) {
    module = &m;
    if (module->functions.empty()) return;

    const size_t main_idx = module->functions.size() - 1;
    current_function = &module->functions[main_idx];

    StackFrame frame;
    frame.function_idx = main_idx;
    frame.registers.resize(current_function->local_count, SIZE_MAX);
    call_stack.push_back(std::move(frame));

    run();
  }

  //////////////////////////////////////////////////////
  // LOOP PRINCIPAL
  //////////////////////////////////////////////////////
  void run() {
    while (!call_stack.empty()) {
      auto &frame = call_stack.back();
      init_registers(frame);

      // fim do frame
      if (frame.ip >= current_function->code.size()) {
        handle_return(frame);
        continue;
      }

      const Instruction &instr = current_function->code[frame.ip++];
      frame.debug_print(arena);

      switch (instr.op) {
      case OpCode::LOADK: frame.registers[instr.A] = arena.alloc(module->constants[instr.K]); break;

      case OpCode::MOVE: frame.registers[instr.A] = frame.registers[instr.B]; break;

      case OpCode::ADD:
      case OpCode::SUB:
      case OpCode::MUL:
      case OpCode::DIV: execute_binary_op(frame, instr); break;

      case OpCode::CALL: execute_call(frame, instr); break;

      case OpCode::RETURN: handle_return(frame, instr.A); break;

      default: throw std::runtime_error("Unhandled opcode");
      }
    }
  }

private:
  //////////////////////////////////////////////////////
  // OPERADORES BINÁRIOS
  //////////////////////////////////////////////////////
  void execute_binary_op(StackFrame &frame, const Instruction &instr) {
    size_t lhs_idx = frame.get_register(instr.B);
    size_t rhs_idx = frame.get_register(instr.C);

    double a = arena.get(lhs_idx).get_number();
    double b = arena.get(rhs_idx).get_number();

    double result = (instr.op == OpCode::ADD) ? a + b : (instr.op == OpCode::SUB) ? a - b : (instr.op == OpCode::MUL) ? a * b : a / b;

    frame.registers[instr.A] = arena.alloc(Value(result));
  }

  //////////////////////////////////////////////////////
  // CHAMADA DE FUNÇÃO
  //////////////////////////////////////////////////////
  void execute_call(StackFrame &frame, const Instruction &instr) {
    size_t fn_idx = frame.get_register(instr.B);
    Value &fn_val = arena.get(fn_idx);

    if (fn_val.is_user_function()) {
      auto user_fn = fn_val.get_user_function();
      const CodeFunction &fn = module->functions[user_fn.bytecode_index];

      StackFrame new_frame;
      new_frame.return_ip = frame.ip;
      new_frame.function_idx = user_fn.bytecode_index;
      new_frame.registers.resize(fn.local_count, SIZE_MAX);

      init_registers(new_frame);

      // copia argumentos
      for (uint16_t i = 0; i < instr.C; ++i) new_frame.registers[i] = frame.registers[instr.B + 1 + i];

      call_stack.push_back(std::move(new_frame));
      current_function = &fn;
    } else if (fn_val.is_native_function()) {
      std::vector<Value> args;
      for (uint16_t i = 0; i < instr.C; ++i) { args.push_back(arena.get(frame.registers[instr.B + 1 + i])); }

      auto func = fn_val.get_native();
      auto value = func(args);

      size_t ret_idx = arena.alloc(value);
      frame.registers[instr.A] = ret_idx;
    } else {
      throw std::runtime_error("Expected UserFunction or NativeFunction in CALL");
    }
  }

  //////////////////////////////////////////////////////
  // RETORNO DE FUNÇÃO
  //////////////////////////////////////////////////////
  void handle_return(StackFrame &frame, size_t ret_idx = 0) {
    size_t ret_val_idx = frame.registers.empty() ? arena.alloc_null() : frame.get_register(ret_idx);

    call_stack.pop_back();
    if (call_stack.empty()) return;

    StackFrame &caller = call_stack.back();
    current_function = &module->functions[caller.function_idx];

    size_t dst = ret_idx < caller.registers.size() ? ret_idx : 0;
    caller.registers[dst] = ret_val_idx;

    log("[DEBUG] RETURN: R[" + std::to_string(dst) + "] = " + arena.get(ret_val_idx).convert_to_string());
  }
};
