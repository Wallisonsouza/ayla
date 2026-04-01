#pragma once
#include "ayla-compilation/context.hpp"
#include "core/AST.hpp"
#include "core/managers/scope_manager.hpp"
#include "core/memory/symbol_manager.hpp"
#include "core/source/Source.hpp"
#include "core/token/token_stream.hpp"
#include "diagnostic/DiagnosticEngine.hpp"

namespace ayla::compilation {
struct Unit {
  Context &context;
  core::source::Source &source;
  SymbolManager symbols;
  core::memory::Arena type_arena;

  DiagnosticEngine diagns;
  ScopeManager scopes;

  AST ast;
  core::token::TokenStream tokens;

  explicit Unit(Context &ctx, core::source::Source &src) : context(ctx), source(src), diagns(*this) {}
};

} // namespace ayla::compilation
