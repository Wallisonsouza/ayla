#pragma once
#include "ayla/source/source.hpp"
#include "core/AST.hpp"
#include "core/token/token_stream.hpp"
#include "engine/language_context.hpp"
#include "runtime/ByteCode.hpp"
#include "semantic/scope/scope_manager.hpp"

struct CompilationUnit {

  LanguageContext &context;
  ayla::source::Source &source;

  ScopeManager scope_manager;
  ayla::compiler::ModuleBuilder module;

  Ast ast;

  core::token::TokenStream tokens;

  explicit CompilationUnit(LanguageContext &ctx, ayla::source::Source &src) : context(ctx), source(src) {}
};
