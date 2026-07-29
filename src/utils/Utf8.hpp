#pragma once

#include <cstdint>
#include <string>
#include <string_view>

namespace utils {

class Utf8 {
public:
  struct Result {
    char32_t codepoint;
    size_t size;
  };

  static size_t length(uint8_t first) noexcept {
    if ((first & 0x80) == 0) return 1;

    if ((first & 0xE0) == 0xC0) return 2;

    if ((first & 0xF0) == 0xE0) return 3;

    if ((first & 0xF8) == 0xF0) return 4;

    return 1;
  }

  static Result decode(const char *ptr) noexcept {

    uint8_t b0 = static_cast<uint8_t>(ptr[0]);

    size_t size = length(b0);

    char32_t cp = 0;

    switch (size) {

    case 1: cp = b0; break;

    case 2: cp = ((b0 & 0x1F) << 6) | (static_cast<uint8_t>(ptr[1]) & 0x3F); break;

    case 3: cp = ((b0 & 0x0F) << 12) | ((static_cast<uint8_t>(ptr[1]) & 0x3F) << 6) | (static_cast<uint8_t>(ptr[2]) & 0x3F); break;

    case 4: cp = ((b0 & 0x07) << 18) | ((static_cast<uint8_t>(ptr[1]) & 0x3F) << 12) | ((static_cast<uint8_t>(ptr[2]) & 0x3F) << 6) | (static_cast<uint8_t>(ptr[3]) & 0x3F); break;
    }

    return {.codepoint = cp, .size = size};
  }

  static const char *advance(const char *ptr) noexcept { return ptr + length(static_cast<uint8_t>(*ptr)); }

  static bool decode(std::string_view text, std::u32string &out) noexcept {
    out.clear();

    size_t i = 0;

    // UTF-8 BOM
    if (text.size() >= 3 && static_cast<uint8_t>(text[0]) == 0xEF && static_cast<uint8_t>(text[1]) == 0xBB && static_cast<uint8_t>(text[2]) == 0xBF) { i = 3; }

    while (i < text.size()) {

      auto result = decode(text.data() + i);

      if (i + result.size > text.size()) return false;

      out.push_back(result.codepoint);

      i += result.size;
    }

    return true;
  }

  static std::u32string decode(std::string_view text) noexcept {
    std::u32string out;
    decode(text, out);
    return out;
  }

  static void encode(uint32_t cp, std::string &out) {
    if (cp <= 0x7F) {

      out.push_back(static_cast<char>(cp));

    } else if (cp <= 0x7FF) {

      out.push_back(static_cast<char>(0xC0 | ((cp >> 6) & 0x1F)));

      out.push_back(static_cast<char>(0x80 | (cp & 0x3F)));

    } else if (cp <= 0xFFFF) {

      out.push_back(static_cast<char>(0xE0 | ((cp >> 12) & 0x0F)));

      out.push_back(static_cast<char>(0x80 | ((cp >> 6) & 0x3F)));

      out.push_back(static_cast<char>(0x80 | (cp & 0x3F)));

    } else if (cp <= 0x10FFFF) {

      out.push_back(static_cast<char>(0xF0 | ((cp >> 18) & 0x07)));

      out.push_back(static_cast<char>(0x80 | ((cp >> 12) & 0x3F)));

      out.push_back(static_cast<char>(0x80 | ((cp >> 6) & 0x3F)));

      out.push_back(static_cast<char>(0x80 | (cp & 0x3F)));
    }
  }

  static std::string encode(std::u32string_view text) {
    std::string out;

    out.reserve(text.size() * 4);

    for (char32_t cp : text) encode(cp, out);

    return out;
  }
};

} // namespace utils