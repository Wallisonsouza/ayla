#pragma once

#include "celestia/core/memory/Arena.hpp"
#include "celestia/semantic/scope/Scope.hpp"

class ScopeManager {
  core::memory::Arena arena;
  std::vector<core::Scope *> scopes;

public:
  core::Scope *create_scope(core::ScopeKind kind, core::Scope *parent) {
    auto *scope = arena.alloc<core::Scope>(kind, parent);
    scopes.push_back(scope);
    return scope;
  }
};
