#pragma once

#include "core/visitor/AstStage.hpp"

#include "ast/declarations/FunctionDeclarationNode.hpp"
#include "ast/expressions/BinaryExpressionNode.hpp"

class TypeCheckerStage : public AstStage {
public:
  TypeCheckerStage() {
    bind(&TypeCheckerStage::check_function);

    bind(&TypeCheckerStage::check_binary);
  }

private:
  void check_function(const ayla::ast::node::FunctionDeclarationNode *node);

  void check_binary(const ayla::ast::node::BinaryExpressionNode *node);
};