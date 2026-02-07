#pragma once

#include "engine/language_context.hpp"
#include <GLFW/glfw3.h>

inline void create_module_glfw(LanguageContext &ctx) {
  auto module_id = ctx.module_manager.get_or_create_module("glfw");
  auto module = ctx.module_manager.get(module_id);

  module->on_module_init = [](Module &m) {
    m.add_native_function("init", [](const std::vector<Value> &) { return Value::Boolean(glfwInit()); });

    m.add_native_function("terminate", [](const std::vector<Value> &) {
      glfwTerminate();
      return Value::Void();
    });

    m.add_native_function("create_window", [](const std::vector<Value> &args) {
      int w = (int)args[0].get_number();
      int h = (int)args[1].get_number();
      auto title = args[2].convert_to_string();

      GLFWwindow *win = glfwCreateWindow(w, h, title.c_str(), nullptr, nullptr);

      return Value::Number((uint64_t)win);
    });

    // destroy_window
    m.add_native_function("destroy_window", [](const std::vector<Value> &args) {
      auto win = (GLFWwindow *)(uint64_t)args[0].get_number();
      glfwDestroyWindow(win);
      return Value::Void();
    });

    // window_should_close
    m.add_native_function("window_should_close", [](const std::vector<Value> &args) {
      auto win = (GLFWwindow *)(uint64_t)args[0].get_number();
      return Value::Boolean(glfwWindowShouldClose(win));
    });

    // set_window_should_close
    m.add_native_function("set_window_should_close", [](const std::vector<Value> &args) {
      auto win = (GLFWwindow *)(uint64_t)args[0].get_number();
      int v = (int)args[1].get_number();
      glfwSetWindowShouldClose(win, v);
      return Value::Void();
    });

    // poll_events
    m.add_native_function("poll_events", [](const std::vector<Value> &) {
      glfwPollEvents();
      return Value::Void();
    });

    // swap_buffers
    m.add_native_function("swap_buffers", [](const std::vector<Value> &args) {
      auto win = (GLFWwindow *)(uint64_t)args[0].get_number();
      glfwSwapBuffers(win);
      return Value::Void();
    });

    // make_context_current
    m.add_native_function("make_context_current", [](const std::vector<Value> &args) {
      auto win = (GLFWwindow *)(uint64_t)args[0].get_number();
      glfwMakeContextCurrent(win);
      return Value::Void();
    });
  };
}
