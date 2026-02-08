#pragma once

#include "engine/language_context.hpp"
#include <GLFW/glfw3.h>
#include <string>

inline void create_module_glfw(LanguageContext &ctx) {
  auto module_id = ctx.module_manager.get_or_create_module("glfw");
  auto module = ctx.module_manager.get(module_id);

  module->on_module_init = [](Module &m) {
    // init
    m.add_native_function("init", [](const std::vector<Value> &) { return Value::Boolean(glfwInit()); });

    // terminate
    m.add_native_function("terminate", [](const std::vector<Value> &) {
      glfwTerminate();
      return Value::Void();
    });

    // create_window
    m.add_native_function("create_window", [](const std::vector<Value> &args) {
      int width = (int)args[0].get_number();
      int height = (int)args[1].get_number();
      std::string title = args[2].convert_to_string();

      GLFWwindow *win = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
      return Value::Number((uint64_t)win);
    });

    // destroy_window
    m.add_native_function("destroy_window", [](const std::vector<Value> &args) {
      GLFWwindow *win = (GLFWwindow *)(uint64_t)args[0].get_number();
      if (win) glfwDestroyWindow(win);
      return Value::Void();
    });

    // window_should_close
    m.add_native_function("window_should_close", [](const std::vector<Value> &args) {
      GLFWwindow *win = (GLFWwindow *)(uint64_t)args[0].get_number();
      return Value::Boolean(glfwWindowShouldClose(win));
    });

    // set_window_should_close
    m.add_native_function("set_window_should_close", [](const std::vector<Value> &args) {
      GLFWwindow *win = (GLFWwindow *)(uint64_t)args[0].get_number();
      int val = (int)args[1].get_number();
      glfwSetWindowShouldClose(win, val);
      return Value::Void();
    });

    // poll_events
    m.add_native_function("poll_events", [](const std::vector<Value> &) {
      glfwPollEvents();
      return Value::Void();
    });

    // swap_buffers
    m.add_native_function("swap_buffers", [](const std::vector<Value> &args) {
      GLFWwindow *win = (GLFWwindow *)(uint64_t)args[0].get_number();
      glfwSwapBuffers(win);
      return Value::Void();
    });

    // show_window
    m.add_native_function("show_window", [](const std::vector<Value> &args) {
      GLFWwindow *win = (GLFWwindow *)(uint64_t)args[0].get_number();
      glfwShowWindow(win);
      return Value::Void();
    });

    // hide_window
    m.add_native_function("hide_window", [](const std::vector<Value> &args) {
      GLFWwindow *win = (GLFWwindow *)(uint64_t)args[0].get_number();
      glfwHideWindow(win);
      return Value::Void();
    });

    // set_window_title
    m.add_native_function("set_window_title", [](const std::vector<Value> &args) {
      GLFWwindow *win = (GLFWwindow *)(uint64_t)args[0].get_number();
      std::string title = args[1].convert_to_string();
      glfwSetWindowTitle(win, title.c_str());
      return Value::Void();
    });

    // get_window_width
    m.add_native_function("get_window_width", [](const std::vector<Value> &args) {
      GLFWwindow *win = (GLFWwindow *)(uint64_t)args[0].get_number();
      int width, height;
      glfwGetWindowSize(win, &width, &height);
      return Value::Number(width);
    });

    // get_window_height
    m.add_native_function("get_window_height", [](const std::vector<Value> &args) {
      GLFWwindow *win = (GLFWwindow *)(uint64_t)args[0].get_number();
      int width, height;
      glfwGetWindowSize(win, &width, &height);
      return Value::Number(height);
    });

    // make_context_current
    m.add_native_function("make_context_current", [](const std::vector<Value> &args) {
      GLFWwindow *win = (GLFWwindow *)(uint64_t)args[0].get_number();
      glfwMakeContextCurrent(win);
      return Value::Void();
    });
  };
}
