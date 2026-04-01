#pragma once
#include "ayla-structural/ayla-token/kind.hpp"
#include "core/node/NodeKind.hpp"
#include <string>
#include <unordered_map>
#include <variant>

using DiagnosticValue = std::variant<std::string, ayla::structural::token::TokenKind, core::ast::NodeKind>;

struct DiagnosticContext {
  std::unordered_map<std::string, DiagnosticValue> values;

  template <typename T> void set(std::string key, T value) { values.emplace(std::move(key), std::move(value)); }

  const DiagnosticValue *get(const std::string &key) const {
    auto it = values.find(key);
    return it != values.end() ? &it->second : nullptr;
  }
};
