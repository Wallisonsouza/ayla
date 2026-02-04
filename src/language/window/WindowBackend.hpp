#pragma once
#include <string>

struct WindowBackend {
  virtual ~WindowBackend() = default;

  virtual void create(int w, int h, const std::string &title) = 0;
  virtual void make_current() = 0;
  virtual void swap_buffers() = 0;
  virtual void poll_events() = 0;
  virtual bool is_open() = 0;
  virtual void destroy() = 0;
};
