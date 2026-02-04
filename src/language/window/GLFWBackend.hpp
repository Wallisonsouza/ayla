#pragma once
#include "WindowBackend.hpp"
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <unordered_map>

struct GLFWBackend : WindowBackend {

  std::unordered_map<int, GLFWwindow *> windows;
  int next_id = 1;

  GLFWBackend() {
    if (!glfwInit()) std::abort();
  }

  ~GLFWBackend() {
    destroy_all();
    glfwTerminate();
  }

  int create(int w, int h, const std::string &title) override {
    GLFWwindow *win = glfwCreateWindow(w, h, title.c_str(), nullptr, nullptr);
    if (!win) std::abort();

    int id = next_id++;
    windows[id] = win;
    return id;
  }

  void close(int id) override {
    auto it = windows.find(id);
    if (it != windows.end()) {
      glfwDestroyWindow(it->second);
      windows.erase(it);
    }
  }

  void resize(int id, int w, int h) override {
    auto it = windows.find(id);
    if (it != windows.end()) glfwSetWindowSize(it->second, w, h);
  }

  void move(int id, int x, int y) override {
    auto it = windows.find(id);
    if (it != windows.end()) glfwSetWindowPos(it->second, x, y);
  }

  int get_width(int id) override {
    int w = 0, h = 0;
    auto it = windows.find(id);
    if (it != windows.end()) { glfwGetWindowSize(it->second, &w, &h); }
    return w;
  }

  int get_height(int id) override {
    int w = 0, h = 0;
    auto it = windows.find(id);
    if (it != windows.end()) { glfwGetWindowSize(it->second, &w, &h); }
    return h;
  }

  bool is_visible(int id) override {
    auto it = windows.find(id);
    if (it != windows.end()) return glfwGetWindowAttrib(it->second, GLFW_VISIBLE);
    return false;
  }

  void show(int id) override {
    auto it = windows.find(id);
    if (it != windows.end()) glfwShowWindow(it->second);
  }

  void hide(int id) override {
    auto it = windows.find(id);
    if (it != windows.end()) glfwHideWindow(it->second);
  }

  void set_title(int id, const std::string &title) override {
    auto it = windows.find(id);
    if (it != windows.end()) glfwSetWindowTitle(it->second, title.c_str());
  }

  std::string get_title(int id) override {
    auto it = windows.find(id);
    if (it != windows.end()) return glfwGetWindowTitle(it->second);
    return {};
  }

  void update(int id) override {
    auto it = windows.find(id);
    if (it != windows.end()) {
      glfwMakeContextCurrent(it->second);
      glfwSwapBuffers(it->second);
    }
  }

private:
  void destroy_all() {
    for (auto &[id, win] : windows) {
      if (win) glfwDestroyWindow(win);
    }
    windows.clear();
  }
};
