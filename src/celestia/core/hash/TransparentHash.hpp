#pragma once
#include <cstddef>
#include <string>
#include <string_view>

struct U32Hash {
  using is_transparent = void;

  size_t operator()(std::string_view v) const noexcept {
    size_t h = 0;
    for (char32_t c : v)
      h = h * 131 + static_cast<size_t>(c);
    return h;
  }

  size_t operator()(const std::string &v) const noexcept {
    return operator()(std::string_view{v});
  }
};

struct U32Equal {
  using is_transparent = void;

  bool operator()(std::string_view a, std::string_view b) const noexcept {
    return a == b;
  }

  bool operator()(const std::string &a, const std::string &b) const noexcept {
    return a == b;
  }

  bool operator()(const std::string &a, std::string_view b) const noexcept {
    return a == b;
  }

  bool operator()(std::string_view a, const std::string &b) const noexcept {
    return a == b;
  }
};