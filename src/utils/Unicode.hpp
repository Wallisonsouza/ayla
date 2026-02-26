#pragma once
#include <algorithm>
#include <string>
#include <unicode/uchar.h>
#include <unicode/urename.h>

namespace utils {

class Unicode {
public:
  inline static void trim_u32string(std::u32string &s) {
    s.erase(s.begin(), std::ranges::find_if(s.begin(), s.end(), [](char32_t ch) { return !is_white_space(ch); }));
    s.erase(std::ranges::find_if(s.rbegin(), s.rend(), [](char32_t ch) { return !is_white_space(ch); }).base(), s.end());
  }

  static int char_width(char32_t cp) {
    if (cp == 0) return 0;

    auto cat = u_charType(cp);
    if (cat == U_COMBINING_SPACING_MARK || cat == U_NON_SPACING_MARK) return 0; // acentos combinantes

    // East Asian Width (CJK, fullwidth)
    UProperty prop = UCHAR_EAST_ASIAN_WIDTH;
    int width = u_getIntPropertyValue(cp, prop);
    if (width == U_EA_FULLWIDTH || width == U_EA_WIDE) return 2;

    // Cobrir emojis recentes (Unicode 13, 14, 15…)
    if ((cp >= 0x1F300 && cp <= 0x1FAFF) || // símbolos, faces, transportes, recentes
        (cp >= 0x1F1E6 && cp <= 0x1F1FF))   // bandeiras (regional indicators)
      return 2;

    // Outros casos (ASCII, etc)
    return 1;
  }

  inline static bool is_alpha(char32_t cp) { return u_isUAlphabetic(cp); }

  inline static bool is_letter(char32_t cp) { return (cp >= 0x61 && cp <= 0x7A) || (cp >= 0x41 && cp <= 0x5A); }

  inline static bool is_digit(char32_t cp) { return (cp >= 0x30 && cp <= 0x39); }

  inline static bool is_alphanumeric(char32_t cp) { return is_letter(cp) || is_digit(cp); }

  inline static bool is_white_space(char32_t cp) { return u_isUWhiteSpace(cp); }

  static bool isDigit(char32_t c) { return u_isdigit(c); }

  inline static bool is_symbol(char32_t cp) {

    UCharCategory cat = static_cast<UCharCategory>(u_charType(cp));

    return cat == U_MATH_SYMBOL || cat == U_CURRENCY_SYMBOL || cat == U_MODIFIER_SYMBOL || cat == U_OTHER_SYMBOL;
  }
};

} // namespace utils
