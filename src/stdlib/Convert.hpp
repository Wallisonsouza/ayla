#pragma once
#include "engine/language_context.hpp"
#include <string>

inline void create_module_convert(LanguageContext &ctx) {

  auto module_id = ctx.module_manager.get_or_create_module("convert");
  auto module = ctx.module_manager.get(module_id);

  module->on_module_init = [](Module &m) {
    
    m.add_native_function("parse_number", [](const std::vector<Value> &args) {
      std::string s = args[0].convert_to_string();
      return Value::Number(std::stod(s));
    });

    m.add_native_function("parse_bool", [](const std::vector<Value> &args) {
      std::string s = args[0].convert_to_string();
      return Value::Boolean(s == "true");
    });

    m.add_native_function("to_string", [](const std::vector<Value> &args) { return Value::String(std::to_string(args[0].get_number())); });
  };
}