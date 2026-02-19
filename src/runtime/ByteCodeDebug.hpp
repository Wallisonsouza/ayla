// #pragma once

// #include "ByteCode.hpp"
// #include "Instruction.hpp"

// struct BytecodeLogger {

//   static std::string opcode_to_string(OpCode op) {
//     switch (op) {
//     case OpCode::LOADK: return "LOADK";
//     case OpCode::MOVE: return "MOVE";
//     case OpCode::ADD: return "ADD";
//     case OpCode::SUB: return "SUB";
//     case OpCode::MUL: return "MUL";
//     case OpCode::DIV: return "DIV";
//     case OpCode::LOAD: return "LOAD";
//     case OpCode::STORE: return "STORE";
//     case OpCode::LOAD_FIELD: return "LOAD_FIELD";
//     case OpCode::STORE_FIELD: return "STORE_FIELD";
//     case OpCode::CALL: return "CALL";
//     case OpCode::RETURN: return "RETURN";
//     case OpCode::JUMP: return "JUMP";
//     case OpCode::JUMP_IF_FALSE: return "JUMP_IF_FALSE";
//     case OpCode::IMPORT: return "IMPORT";
//     case OpCode::NOP: return "NOP";
//     default: return "UNKNOWN";
//     }
//   }

//   static void log(const BytecodeGenerator &byte_code) {
//     std::cout << "Module:\n";
//     std::cout << "Constants:\n";
//     for (size_t i = 0; i < byte_code.module->constants.size(); ++i) { log_constant(byte_code.module->constants[i], i); }
//     std::cout << "Functions:\n";
//     for (size_t i = 0; i < byte_code.module->functions.size(); ++i) { log_function(byte_code.module->functions[i], i); }
//     std::cout << "Main function code:\n";

//     auto &main_fn = byte_code.module->functions.back();
//     log_code(main_fn.code);
//   }

//   static void log_instruction(const Instruction &instr) {
//     std::cout << "  " << opcode_to_string(instr.op) << " (A=" << instr.A << ", B=" << instr.B << ", C=" << instr.C << ", K=" << instr.K << ")\n";
//   }

//   static void log_function(const Function &fn, size_t idx) {
//     std::cout << "Function [" << idx << "] (arity=" << fn.arity << ", local_count=" << fn.local_count << "):\n";
//     for (const auto &instr : fn.code) { log_instruction(instr); }
//   }

//   static void log_module(const GenModule &mod) {
//     std::cout << "Module:\n";
//     std::cout << "Constants:\n";
//     for (size_t i = 0; i < mod.constants.size(); ++i) { log_constant(mod.constants[i], i); }

//     std::cout << "Functions:\n";
//     for (size_t i = 0; i < mod.functions.size(); ++i) { log_function(mod.functions[i], i); }
//   }
//   static void log_code(const std::vector<Instruction> &code) {
//     for (size_t i = 0; i < code.size(); ++i) {
//       std::cout << i << ": ";
//       log_instruction(code[i]);
//     }
//   }

//   static void log_constant(const Value &v, size_t idx) { std::cout << "  [" << idx << "] " << v.convert_to_string() << "\n"; }
// };
