#pragma once

#include "engine/language_context.hpp"
#include <GLFW/glfw3.h>
#include <string>

inline void create_module_glfw(LanguageContext &ctx) {

  auto module = ctx.module_manager.get_or_create_module_ptr("glfw");

  module->on_module_init = [](Module &m) {
    m.add_native_function("init", [](const std::vector<Value> &) { return Value::Boolean(glfwInit()); });

    m.add_native_function("terminate", [](const std::vector<Value> &) {
      glfwTerminate();
      return Value::Void();
    });

    m.add_native_function("create_window", [](const std::vector<Value> &args) {
      int width = (int)args[0].get_number();
      int height = (int)args[1].get_number();
      std::string title = args[2].convert_to_string();

      GLFWwindow *win = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
      return Value::Number((uint64_t)win);
    });

    m.add_native_function("destroy_window", [](const std::vector<Value> &args) {
      GLFWwindow *win = (GLFWwindow *)(uint64_t)args[0].get_number();
      if (win) glfwDestroyWindow(win);
      return Value::Void();
    });

    m.add_native_function("window_should_close", [](const std::vector<Value> &args) {
      GLFWwindow *win = (GLFWwindow *)(uint64_t)args[0].get_number();
      return Value::Boolean(glfwWindowShouldClose(win));
    });

    m.add_native_function("set_window_should_close", [](const std::vector<Value> &args) {
      GLFWwindow *win = (GLFWwindow *)(uint64_t)args[0].get_number();
      int val = (int)args[1].get_number();
      glfwSetWindowShouldClose(win, val);
      return Value::Void();
    });

    m.add_native_function("poll_events", [](const std::vector<Value> &) {
      glfwPollEvents();
      return Value::Void();
    });

    m.add_native_function("swap_buffers", [](const std::vector<Value> &args) {
      GLFWwindow *win = (GLFWwindow *)(uint64_t)args[0].get_number();
      glfwSwapBuffers(win);
      return Value::Void();
    });

    m.add_native_function("show_window", [](const std::vector<Value> &args) {
      GLFWwindow *win = (GLFWwindow *)(uint64_t)args[0].get_number();
      glfwShowWindow(win);
      return Value::Void();
    });

    m.add_native_function("hide_window", [](const std::vector<Value> &args) {
      GLFWwindow *win = (GLFWwindow *)(uint64_t)args[0].get_number();
      glfwHideWindow(win);
      return Value::Void();
    });

    m.add_native_function("set_window_title", [](const std::vector<Value> &args) {
      GLFWwindow *win = (GLFWwindow *)(uint64_t)args[0].get_number();
      std::string title = args[1].convert_to_string();
      glfwSetWindowTitle(win, title.c_str());
      return Value::Void();
    });

    m.add_native_function("get_window_width", [](const std::vector<Value> &args) {
      GLFWwindow *win = (GLFWwindow *)(uint64_t)args[0].get_number();
      int width, height;
      glfwGetWindowSize(win, &width, &height);
      return Value::Number(width);
    });

    m.add_native_function("get_window_height", [](const std::vector<Value> &args) {
      GLFWwindow *win = (GLFWwindow *)(uint64_t)args[0].get_number();
      int width, height;
      glfwGetWindowSize(win, &width, &height);
      return Value::Number(height);
    });

    m.add_native_function("make_context_current", [](const std::vector<Value> &args) {
      GLFWwindow *win = (GLFWwindow *)(uint64_t)args[0].get_number();
      glfwMakeContextCurrent(win);
      return Value::Void();
    });
  };
}