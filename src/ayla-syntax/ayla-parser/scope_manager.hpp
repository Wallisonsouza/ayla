#include "ayla-syntax/ayla-parser/scope.hpp"
#include "core/memory/Arena.hpp"

class ScopeManager {
  core::memory::Arena arena;
  std::vector<core::ParserScope *> scopes;

public:
  core::ParserScope *create_scope(core::ParserScope *parent) {
    auto *scope = arena.alloc<core::ParserScope>(parent);
    scopes.push_back(scope);
    return scope;
  }
};
