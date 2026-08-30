#pragma once

#include <format>
#include <iostream>
#include <string_view>
#include <utility>

namespace celestia::debug {

enum class Category {
  Lexer,
  Parser,
  Resolver,
  TypeChecker,
  Lowering,
  IR,
  Codegen,
};

constexpr std::string_view category_name(Category category) {

  switch (category) {
  case Category::Lexer:      return "Lexer";
  case Category::Parser:     return "Parser";
  case Category::Resolver:   return "Resolver";
  case Category::TypeChecker:return "TypeChecker";
  case Category::Lowering:   return "Lowering";
  case Category::IR:         return "IR";
  case Category::Codegen:    return "Codegen";
  }

  return "Unknown";
}

class Trace {
public:

  static void enable(Category category) {
    enabled(category) = true;
  }

  static void disable(Category category) {
    enabled(category) = false;
  }

  static bool is_enabled(Category category) {
    return enabled(category);
  }

  template <typename... Args>
  static void log(
      Category category,
      std::format_string<Args...> format,
      Args &&...args) {

    if (!is_enabled(category))
      return;

    std::cout
        << '['
        << category_name(category)
        << "] "
        << std::format(
               format,
               std::forward<Args>(args)...)
        << '\n';
  }

private:

  static bool &enabled(Category category) {

    static bool states[7] = {
        false, // Lexer
        false, // Parser
        false, // Resolver
        false, // TypeChecker
        false, // Lowering
        false, // IR
        false  // Codegen
    };

    return states[static_cast<int>(category)];
  }
};

template <typename... Args>
void trace(
    Category category,
    std::format_string<Args...> format,
    Args &&...args) {

  Trace::log(
      category,
      format,
      std::forward<Args>(args)...);
}

} // namespace celestia::debug