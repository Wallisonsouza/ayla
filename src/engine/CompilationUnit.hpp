#pragma once
#include "core/AST.hpp"
#include "core/source/Source.hpp"
#include "core/token/token_stream.hpp"
#include "diagnostic/DiagnosticEngine.hpp"
#include "engine/language_context.hpp"
#include "semantic/scope/scope_manager.hpp"

struct CompilationUnit {

  LanguageContext &context;
  core::source::Source &source;

  DiagnosticEngine diagns;

  ScopeManager scope_manager;

  Ast ast;

  core::token::TokenStream tokens;

  explicit CompilationUnit(LanguageContext &ctx, core::source::Source &src) : context(ctx), source(src), diagns(*this) {}
};
