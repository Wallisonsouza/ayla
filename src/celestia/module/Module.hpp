#pragma once
#include "celestia/semantic/scope/Scope.hpp"
#include <string>

class Module {

public:
  Module(std::string name, Module *parent = nullptr) : name_(std::move(name)), scope_(core::ScopeKind::Module, parent ? &parent->get_scope() : nullptr) {}

  std::string_view name() const { return name_; }

  core::Scope &get_scope() { return scope_; }

private:

  std::string name_;

  core::Scope scope_;
};