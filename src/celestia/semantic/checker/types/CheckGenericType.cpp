#include "celestia/semantic/checker/TypeChecker.hpp"

namespace celestia::semantic {

TypeId TypeChecker::check_generic_type(ast::GenericTypeNode *node) {

  if (!node || !node->name) return TypeId::invalid();

  SymbolId constructor_id = node->symbol_id;

  if (!constructor_id.is_valid()) {

    error(node, "invalid generic constructor");

    return TypeId::invalid();
  }

  return check_generic_instance_type(node);
}

TypeId TypeChecker::check_generic_instance_type(ast::GenericTypeNode *node) {

  if (!node) return TypeId::invalid();

  SymbolId constructor = node->symbol_id;

  if (!constructor.is_valid()) {

    error(node, "invalid generic constructor");

    return TypeId::invalid();
  }

  std::vector<TypeId> arguments;

  for (auto *argument : node->arguments) {

    if (!argument) {
      error(node, "invalid generic argument");
      return TypeId::invalid();
    }

    TypeId argument_type = type_from_node(argument);

    if (!argument_type.is_valid()) {

      error(argument, "invalid generic argument type");

      return TypeId::invalid();
    }

    arguments.push_back(argument_type);
  }

  TypeId generic_type = context.compiler.types.get_or_create_generic_instance(constructor, std::move(arguments));

  if (!generic_type.is_valid()) {

    error(node, "could not create generic instance");

    return TypeId::invalid();
  }

  node->type_id = generic_type;

  return generic_type;
}
} // namespace celestia::semantic