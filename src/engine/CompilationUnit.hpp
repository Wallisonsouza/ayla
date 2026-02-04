#pragma once
#include "core/AST.hpp"
#include "core/managers/scope_manager.hpp"
#include "core/source/Source.hpp"
#include "core/token/token_stream.hpp"
#include "diagnostic/DiagnosticEngine.hpp"
#include "engine/language_context.hpp"

struct CompilationUnit {

  LanguageContext &context;
  core::source::Source &source;

  core::memory::Arena type_arena;

  DiagnosticEngine diagns;

  ScopeManager scope_manager;

  AST ast;

  core::token::TokenStream tokens;

  explicit CompilationUnit(LanguageContext &ctx, core::source::Source &src) : context(ctx), source(src), diagns(*this) {}
};
