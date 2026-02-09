#pragma once

#include "engine/language_context.hpp"
#include <iostream>
#include <string>

inline void create_module_io(LanguageContext &ctx) {

  auto module_id = ctx.module_manager.get_or_create_module("io");
  auto module = ctx.module_manager.get(module_id);

  module->on_module_init = [](Module &m) {
    m.add_native_function("print", [](const std::vector<Value> &args) {
      std::cout << args[0].convert_to_string();
      return Value::Void();
    });

    m.add_native_function("println", [](const std::vector<Value> &args) {
      std::cout << args[0].convert_to_string() << std::endl;
      return Value::Void();
    });

    m.add_native_function("read_line", [](const std::vector<Value> &) {
      std::string line;
      std::getline(std::cin, line);
      return Value::String(line);
    });
  };
}