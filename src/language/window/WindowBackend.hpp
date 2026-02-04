#pragma once
#include <string>

struct WindowBackend {
  virtual ~WindowBackend() = default;

  virtual int create(int w, int h, const std::string &title) = 0;

  virtual void close(int id) = 0;
  virtual void resize(int id, int w, int h) = 0;
  virtual void move(int id, int x, int y) = 0;
  virtual int get_width(int id) = 0;
  virtual int get_height(int id) = 0;
  virtual bool is_visible(int id) = 0;
  virtual void show(int id) = 0;
  virtual void hide(int id) = 0;
  virtual void set_title(int id, const std::string &title) = 0;
  virtual std::string get_title(int id) = 0;
  virtual void update(int id) = 0;
};
