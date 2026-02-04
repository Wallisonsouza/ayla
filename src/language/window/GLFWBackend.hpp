#pragma once
#include "WindowBackend.hpp"
#include <GLFW/glfw3.h>
#include <cstdlib>

struct GLFWBackend : WindowBackend {

  GLFWwindow *window = nullptr;

  GLFWBackend() {
    if (!glfwInit()) std::abort();
  }

  ~GLFWBackend() {
    destroy();
    glfwTerminate();
  }

  void create(int w, int h, const std::string &t) override {
    window = glfwCreateWindow(w, h, t.c_str(), nullptr, nullptr);
    if (!window) std::abort();
  }

  void make_current() override { glfwMakeContextCurrent(window); }

  void swap_buffers() override { glfwSwapBuffers(window); }

  void poll_events() override { glfwPollEvents(); }

  bool is_open() override { return window && !glfwWindowShouldClose(window); }

  void destroy() override {
    if (window) {
      glfwDestroyWindow(window);
      window = nullptr;
    }
  }
};
