#pragma once

#include "engine/language_context.hpp"
#include "language/window/WindowBackend.hpp"

inline void create_module_window(LanguageContext &ctx) {

  auto module_id = ctx.module_manager.create_module("window");
  auto module = ctx.module_manager.get(module_id);

  module->on_module_init = [&ctx](Module &m) {
    auto backend = ctx.backends.get<WindowBackend>();

    m.add_native_function("create", [backend](const std::vector<Value> &args) {
      int id = backend->create((int)args[0].get_number(), (int)args[1].get_number(), args[2].get_string());
      return Value::Number(id);
    });

    m.add_native_function("close", [backend](const std::vector<Value> &args) {
      backend->close((int)args[0].get_number());
      return Value::Void();
    });

    m.add_native_function("resize", [backend](const std::vector<Value> &args) {
      backend->resize((int)args[0].get_number(), (int)args[1].get_number(), (int)args[2].get_number());
      return Value::Void();
    });

    m.add_native_function("move", [backend](const std::vector<Value> &args) {
      backend->move((int)args[0].get_number(), (int)args[1].get_number(), (int)args[2].get_number());
      return Value::Void();
    });

    m.add_native_function("get_width", [backend](const std::vector<Value> &args) { return Value::Number(backend->get_width((int)args[0].get_number())); });

    m.add_native_function("get_height", [backend](const std::vector<Value> &args) { return Value::Number(backend->get_height((int)args[0].get_number())); });

    m.add_native_function("is_visible", [backend](const std::vector<Value> &args) { return Value::Boolean(backend->is_visible((int)args[0].get_number())); });

    m.add_native_function("show", [backend](const std::vector<Value> &args) {
      backend->show((int)args[0].get_number());
      return Value::Void();
    });

    m.add_native_function("hide", [backend](const std::vector<Value> &args) {
      backend->hide((int)args[0].get_number());
      return Value::Void();
    });

    m.add_native_function("set_title", [backend](const std::vector<Value> &args) {
      backend->set_title((int)args[0].get_number(), args[1].get_string());
      return Value::Void();
    });

    m.add_native_function("get_title", [backend](const std::vector<Value> &args) { return Value::String(backend->get_title((int)args[0].get_number())); });

    m.add_native_function("update", [backend](const std::vector<Value> &args) {
      backend->update((int)args[0].get_number());
      return Value::Void();
    });
  };
}
