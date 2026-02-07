#pragma once

#include "engine/language_context.hpp"
#include <iostream>

inline void create_module_console(LanguageContext &ctx) {
  auto module_id = ctx.module_manager.get_or_create_module("console");
  auto module = ctx.module_manager.get(module_id);

  module->on_module_init = [&ctx](Module &m) {
    m.add_native_function("log", [](const std::vector<Value> &args) {
      for (const auto &arg : args) { std::cout << arg.convert_to_string(); }
      return Value::Void();
    });
  };
}
