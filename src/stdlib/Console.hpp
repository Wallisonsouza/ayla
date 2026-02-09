#pragma once

#include "engine/language_context.hpp"
#include <iostream>

inline void create_module_console(LanguageContext &ctx) {

  auto module = ctx.module_manager.get_or_create_module_ptr("console");

  module->on_module_init = [&ctx](Module &m) {
    m.add_native_function("log", [](const std::vector<Value> &args) {
      for (const auto &arg : args) { std::cout << arg.convert_to_string(); }
      std::cout << std::endl;
      return Value::Void();
    });

    m.add_native_function("error", [](const std::vector<Value> &args) {
      std::cerr << "\033[1;31m";
      for (const auto &arg : args) { std::cerr << arg.convert_to_string(); }
      std::cerr << "\033[0m" << std::endl;
      return Value::Void();
    });

    m.add_native_function("warn", [](const std::vector<Value> &args) {
      std::cout << "\033[1;33m";
      for (const auto &arg : args) { std::cout << arg.convert_to_string(); }
      std::cout << "\033[0m" << std::endl;
      return Value::Void();
    });
  };
}