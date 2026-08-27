#pragma once

#include "celestia/ast/declarations/FunctionDeclaration.hpp"

#include "celestia/ast/declarations/CapabilityDeclaration.hpp"
#include "celestia/ast/declarations/ImplementationDeclaration.hpp"
#include "celestia/ast/declarations/ModuleDeclaration.hpp"
#include "celestia/ast/declarations/StructDeclaration.hpp"
#include "celestia/ast/declarations/VariableDeclaration.hpp"
#include "celestia/ast/expressions/BinaryExpressionNode.hpp"
#include "celestia/ast/expressions/ExpressionNode.hpp"
#include "celestia/ast/expressions/LiteralExpressionNode.hpp"
#include "celestia/ast/patterns/NamedPatternNode.hpp"
#include "celestia/ast/statements/ExpressionStatementNode.hpp"
#include "celestia/ast/statements/ReturnStatementNode.hpp"
#include "celestia/ast/types/GenericType.hpp"
#include "celestia/ast/types/NamedType.hpp"
#include "celestia/ast/types/TypeNode.hpp"
#include "celestia/compiler/CompilationUnit.hpp"
#include "celestia/compiler/CompilerEnvironment.hpp"
#include <ostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace celestia::codegen {

struct CGeneratorContext {
  CompilationUnit &unit;
  CompilerEnvironment &compiler;
};

class CGenerator {

public:
  CGeneratorContext &context;

  explicit CGenerator(std::ostream &out, CGeneratorContext &c) : out(out), context(c) {}

  void generate_module(const ast::ModuleDeclaration *module);

private:

  // types
  void generate_type(TypeId type_id);

  void generate_generic_instance(const semantic::GenericInstanceType *type);

  void generate_primitive_type(const semantic::PrimitiveType *type); 

  // exp
  void generate_number_literal(const ast::NumberLiteralNode *literal);
  void generate_expression(const ast::Expression *expression);
  // ----------------------------------------------------------
  // Runtime
  // ----------------------------------------------------------
  void generate_string_literal(const ast::StringLiteralNode *literal);
  void generate_runtime();

  // ----------------------------------------------------------
  // Structs
  // ----------------------------------------------------------

  void generate_binary_expression(const ast::BinaryExpressionNode *expr);

   void generate_return_statement(const ast::ReturnStatement *ret);

  void collect_structs(const ast::ModuleDeclaration *module);

  void collect_struct_dependencies(const ast::StructDeclaration *decl);
  void collect_type_dependency(const ast::TypeNode *type, std::vector<std::string> &deps);
  void generate_forward_declarations();

  void generate_structs();

  void generate_field(const ast::FieldDeclaration *field);

  // ----------------------------------------------------------
  // Arrays
  // ----------------------------------------------------------
  void generate_struct_literal(const ast::StructLiteralNode *node);
  void collect_array_types(const ast::ModuleDeclaration *module);

  void collect_array_type(const ast::TypeNode *type);

  void generate_array_types();

  void visit_struct(const std::string &name);

  void generate_array_element_type(const ast::TypeNode *type);
  void generate_array_element_name(const ast::TypeNode *type);
  void generate_expression_statement(const ast::ExpressionStatement *statement);
  void generate_variable_declaration(const ast::VariableDeclaration *variable);
  void generate_struct_declaration(const ast::StructDeclaration *decl);
  void generate_capability_declaration(const ast::CapabilityDeclaration *declaration);
  void generate_declaration(const ast::Declaration *declaration);
  void generate_impl_declaration(const ast::ImplDeclaration *declaration);
  void generate_parameters(const semantic::FunctionType &type, const ast::FunctionDeclaration *function);
  void generate_function_declaration(const ast::FunctionDeclaration *function);
  void generate_block(const ast::BlockStatement *block);
  // void generate_pattern(const ast::PatternNode *pattern);
  void generate_name_pattern(const ast::NamedPattern *pattern);
  void generate_statement(const ast::Statement *statement);
  void generate_array_literal(const ast::ArrayLiteralNode *literal);
 

private:
  std::ostream &out;

  // Nome -> struct AST
  std::unordered_map<std::string, const ast::StructDeclaration *> structs;

  // Struct -> structs dos quais ele depende
  std::unordered_map<std::string, std::vector<std::string>> dependencies;

  // Resultado da ordenação
  std::vector<const ast::StructDeclaration *> ordered_structs;

  // Estado do DFS
  std::unordered_set<std::string> visiting;

  std::unordered_set<std::string> visited;

  // Nome -> ArrayType
  // std::unordered_map<std::string, const ast::ArrayType *> array_types;

  std::unordered_set<std::string> generated_arrays;
};

} // namespace celestia::codegen