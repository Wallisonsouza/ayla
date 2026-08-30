#pragma once

#include "celestia/compiler/CompilationUnit.hpp"
#include "celestia/compiler/CompilerEnvironment.hpp"
#include "celestia/core/visitor/Stage.hpp"

#include "celestia/compiler/LanguageConstraints.hpp"
#include <stdexcept>
#include <string>
#include <string_view>

class LanguageBootstrapStage : public Stage {
public:
  void run(CompilerEnvironment &env, CompilationUnit &unit) override {

    if (!unit.ast_module) { throw std::runtime_error("LanguageBootstrapStage: missing AST module"); }

    Module *builtin = env.modules.get(env.modules.builtin());

    if (!builtin) { throw std::runtime_error("LanguageBootstrapStage: builtin module not initialized"); }

    env.builtins.int_type = bind_primitive(env, *builtin, celestia::constrains::types::Int, celestia::semantic::PrimitiveKind::Int);

    env.builtins.uint_type = bind_primitive(env, *builtin, celestia::constrains::types::UInt, celestia::semantic::PrimitiveKind::UInt);

    env.builtins.int8_type = bind_primitive(env, *builtin, celestia::constrains::types::Int8, celestia::semantic::PrimitiveKind::Int8);

    env.builtins.int16_type = bind_primitive(env, *builtin, celestia::constrains::types::Int16, celestia::semantic::PrimitiveKind::Int16);

    env.builtins.int32_type = bind_primitive(env, *builtin, celestia::constrains::types::Int32, celestia::semantic::PrimitiveKind::Int32);

    env.builtins.int64_type = bind_primitive(env, *builtin, celestia::constrains::types::Int64, celestia::semantic::PrimitiveKind::Int64);

    env.builtins.uint8_type = bind_primitive(env, *builtin, celestia::constrains::types::UInt8, celestia::semantic::PrimitiveKind::UInt8);

    env.builtins.uint16_type = bind_primitive(env, *builtin, celestia::constrains::types::UInt16, celestia::semantic::PrimitiveKind::UInt16);

    env.builtins.uint32_type = bind_primitive(env, *builtin, celestia::constrains::types::UInt32, celestia::semantic::PrimitiveKind::UInt32);

    env.builtins.uint64_type = bind_primitive(env, *builtin, celestia::constrains::types::UInt64, celestia::semantic::PrimitiveKind::UInt64);

    env.builtins.f32_type = bind_primitive(env, *builtin, celestia::constrains::types::F32, celestia::semantic::PrimitiveKind::F32);

    env.builtins.f64_type = bind_primitive(env, *builtin, celestia::constrains::types::F64, celestia::semantic::PrimitiveKind::F64);

    env.builtins.bool_type = bind_primitive(env, *builtin, celestia::constrains::types::Bool, celestia::semantic::PrimitiveKind::Bool);

    env.builtins.char_type = bind_primitive(env, *builtin, celestia::constrains::types::Char, celestia::semantic::PrimitiveKind::Char);

    env.builtins.string_type = bind_primitive(env, *builtin, celestia::constrains::types::String, celestia::semantic::PrimitiveKind::String);

    env.builtins.void_type = bind_primitive(env, *builtin, celestia::constrains::types::Void, celestia::semantic::PrimitiveKind::Void);

    env.intrinsics.array = require_symbol(env, *builtin, celestia::constrains::intrinsics::Array);

    env.intrinsics.map = require_symbol(env, *builtin, celestia::constrains::intrinsics::Map);

    env.intrinsics.set = require_symbol(env, *builtin, celestia::constrains::intrinsics::Set);

    env.intrinsics.ref = require_symbol(env, *builtin, celestia::constrains::intrinsics::Ref);
  }

private:
  static celestia::semantic::SymbolId require_symbol(CompilerEnvironment &env, Module &module, std::string_view name) {

    celestia::semantic::SymbolId id = module.get_scope().symbol(name);

    if (!id.is_valid()) { throw std::runtime_error("LanguageBootstrapStage: builtin declaration not found: '" + std::string(name) + "'"); }

    auto *symbol = env.symbols.get(id);

    if (!symbol) { throw std::runtime_error("LanguageBootstrapStage: invalid symbol for builtin '" + std::string(name) + "'"); }

    return id;
  }

  static celestia::semantic::TypeId bind_primitive(CompilerEnvironment &env, Module &module, std::string_view name, celestia::semantic::PrimitiveKind kind) {

    celestia::semantic::SymbolId id = require_symbol(env, module, name);

    celestia::semantic::TypeId type_id = env.types.get_or_create_primitive(id, kind);

    auto *symbol = env.symbols.get(id);

    if (!symbol) { throw std::runtime_error("LanguageBootstrapStage: invalid symbol for builtin '" + std::string(name) + "'"); }

    symbol->type = type_id;

    return type_id;
  }
};