#include "core/memory/symbol.hpp"
#include "core/memory/symbol_manager.hpp"
#include "core/memory/value.hpp"

#pragma once
#include "core/memory/symbol_manager.hpp"
#include "core/memory/value.hpp"
#include <functional>
#include <memory>
#include <unordered_map>

namespace module {

using ModuleFactory = std::function<std::shared_ptr<Value>(SymbolManager &)>;

inline std::unordered_map<SymbolId, ModuleFactory> g_native_modules;

inline void register_native_function(Value &obj_value, SymbolManager &symbols, const std::string &name, Value::NativeFunction fn) {
  auto id = symbols.create_symbol(name, SymbolKind::Function, Visibility::Public, true);
  auto &obj = obj_value.get_object_ref();
  obj.set(id, std::make_shared<Value>(Value::Native(std::move(fn))));
}

inline SymbolId register_native_module(SymbolManager &symbols, const std::string &name, ModuleFactory factory) {
  auto id = symbols.create_symbol(name, SymbolKind::Module, Visibility::Public, true);
  g_native_modules[id] = std::move(factory);
  return id;
}

inline std::shared_ptr<Value> get_native_module(SymbolManager &symbols, SymbolId id) {
  auto it = g_native_modules.find(id);
  if (it != g_native_modules.end()) { return it->second(symbols); }
  return nullptr;
}

// // Sobrecarga de conveniência: busca por nome (converte para SymbolId)
// inline std::shared_ptr<Value> get_native_module(SymbolManager &symbols, const std::string &name) {
//   auto id = symbols.lookup_symbol(name);
//   if (!id) return nullptr;
//   return get_native_module(symbols, id);
// }

} // namespace module
