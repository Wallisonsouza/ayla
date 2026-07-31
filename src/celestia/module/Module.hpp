#pragma once

#include "celestia/semantic/scope/Scope.hpp"
#include <string>

class Module {
public:
  explicit Module(std::string name) : name_(std::move(name)), scope_(nullptr) {}

  std::string_view name() const { return name_; }

  core::Scope &get_scope() { return scope_; }

  // const core::Scope &get_scope() const { return scope_; }

private:
  std::string name_;

  core::Scope scope_;
};