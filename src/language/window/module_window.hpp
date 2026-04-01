#pragma once

#include "ayla-compilation/context.hpp"
#include "language/window/WindowBackend.hpp"

inline void create_module_window(ayla::compilation::Context &ctx) {

  auto module_id = ctx.module_manager.create_module("window");
  auto module = ctx.module_manager.get(module_id);

  module->on_module_init = [&ctx](Module &m) {
    auto backend = ctx.backends.get<WindowBackend>();

    m.add_native_function("create", [backend](const std::vector<Value> &args) {
      backend->create((int)args[0].get_number(), (int)args[1].get_number(), args[2].get_string());
      return Value::Void();
    });

    m.add_native_function("makeCurrent", [backend](const std::vector<Value> &) {
      backend->make_current();
      return Value::Void();
    });

    m.add_native_function("swapBuffers", [backend](const std::vector<Value> &) {
      backend->swap_buffers();
      return Value::Void();
    });

    m.add_native_function("pollEvents", [backend](const std::vector<Value> &) {
      backend->poll_events();
      return Value::Void();
    });

    m.add_native_function("isOpen", [backend](const std::vector<Value> &) { return Value::Boolean(backend->is_open()); });

    m.add_native_function("destroy", [backend](const std::vector<Value> &) {
      backend->destroy();
      return Value::Void();
    });
  };
}
