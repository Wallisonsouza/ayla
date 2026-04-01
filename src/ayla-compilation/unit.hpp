#pragma once
#include "ayla-compilation/context.hpp"
#include "ayla-source/source.hpp"
#include "ayla-structural/ayla-token/token_stream.hpp"
#include "core/AST.hpp"
#include "core/managers/scope_manager.hpp"
#include "core/memory/symbol_manager.hpp"
#include "diagnostic/DiagnosticEngine.hpp"

namespace ayla::compilation {
struct Unit {
  Context &context;
  source::Source &source;
  SymbolManager symbols;
  core::memory::Arena type_arena;

  DiagnosticEngine diagns;
  ScopeManager scopes;

  AST ast;
  structural::token::TokenStream tokens;

  explicit Unit(Context &ctx, source::Source &src) : context(ctx), source(src), diagns(*this) {}
};

} // namespace ayla::compilation
