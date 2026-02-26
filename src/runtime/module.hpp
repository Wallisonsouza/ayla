
#include "runtime/Instruction.hpp"
#include "runtime/value/value.hpp"
#include "semantic/symbols/SymbolId.hpp"
#include <algorithm>
#include <optional>
#include <vector>

namespace ayla::compiler {

struct Local {
  SymbolId symbol;
  uint8_t reg;
  uint32_t depth;
};

struct LocalTable {
  uint32_t depth = 0;
  std::vector<Local> locals;

  void enter_scope() { depth++; }

  void leave_scope() {
    locals.erase(std::remove_if(locals.begin(), locals.end(), [this](const Local &l) { return l.depth == depth; }), locals.end());
    depth--;
  }

  void add(SymbolId sym, uint8_t reg) { locals.push_back({sym, reg, depth}); }

  std::optional<uint8_t> resolve(SymbolId sym) const {
    for (int i = (int)locals.size() - 1; i >= 0; --i)
      if (locals[i].symbol == sym) return locals[i].reg;

    return std::nullopt;
  }
};

struct FunctionBuilder {
  uint32_t arity = 0;
  uint32_t local_count = 0;

  std::vector<runtime::Register> code;

  runtime::RegisterAllocator regs;
  LocalTable locals;

  uint8_t alloc_reg() { return regs.alloc(); }

  uint8_t alloc_local(SymbolId sym) {
    uint8_t r = regs.alloc();
    locals.add(sym, r);
    return r;
  }

  void emit(const runtime::Register &i) { code.push_back(i); }

  void finalize() { local_count = regs.used(); }
};

struct ModuleBuilder {
  std::vector<Value> constants;
  std::vector<FunctionBuilder> functions;

  uint32_t add_constant(const Value &v) {
    constants.push_back(v);
    return constants.size() - 1;
  }

  size_t add_function(FunctionBuilder &&fn) {
    functions.push_back(std::move(fn));
    return functions.size() - 1;
  }

  void print() const {
    std::cout << "\nconstants: \n";
    for (size_t i = 0; i < constants.size(); ++i) {
      const auto &val = constants[i];
      std::cout << "  " << "[" << std::setw(2) << i << "] " << val.convert_to_string() << "\n";
    }

    std::cout << "\nfunctions: \n";
    for (size_t i = 0; i < functions.size(); ++i) {
      const auto &fn = functions[i];
      std::cout << "  " << "Function " << i << " (arity=" << fn.arity << ", locals=" << fn.local_count << ")\n";

      for (size_t j = 0; j < fn.code.size(); ++j) {
        const runtime::Register &instr = fn.code[j];
        std::cout << "    " << std::setw(4) << std::setfill('0') << j << "  " << instr.to_string(constants) << "\n";
      }
      std::cout << "\n";
    }
  }
};

} // namespace ayla::compiler