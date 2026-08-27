#include "celestia/semantic/checker/TypeChecker.hpp"

namespace celestia::semantic {

void TypeChecker::check_return_statement(ast::ReturnStatement *node) {

  if (!node) return;

  // ------------------------------------------------
  // Verifica se estamos dentro de uma função
  // ------------------------------------------------

  if (!current_function.is_valid()) {

    error(node, "return outside function");

    return;
  }

  // ------------------------------------------------
  // Obtém FunctionType
  // ------------------------------------------------

  auto &type = context.compiler.types.get(current_function);

  if (type.kind != TypeKind::Function) {

    error(node, "current type is not a function");

    return;
  }

  auto &function_type = static_cast<FunctionType &>(type);

  TypeId expected = function_type.return_type;

  if (!expected.is_valid()) {

    error(node, "function has no return type");

    return;
  }

  // ------------------------------------------------
  // return;
  // ------------------------------------------------

  if (!node->value) {

    // Se não tem valor, precisa ser void.
    const auto &expected_type = context.compiler.types.get(expected);

    if (expected_type.kind != TypeKind::Primitive) {

      error(node, "return without value requires void");

      return;
    }

    const auto &primitive = static_cast<const PrimitiveType &>(expected_type);

    if (primitive.primitive != PrimitiveKind::Void) {

      error(node, "return requires a value");

      return;
    }

    return;
  }

  // ------------------------------------------------
  // return value;
  // ------------------------------------------------

  check(node->value);

  TypeId actual = node->value->type_id;

  if (!actual.is_valid()) {

    error(node, "return expression has no type");

    return;
  }

  // ------------------------------------------------
  // void não pode receber valor
  // ------------------------------------------------

  const auto &expected_type = context.compiler.types.get(expected);

  if (expected_type.kind == TypeKind::Primitive) {

    const auto &primitive = static_cast<const PrimitiveType &>(expected_type);

    if (primitive.primitive == PrimitiveKind::Void) {

      error(node, "void function cannot return a value");

      return;
    }
  }

  // ------------------------------------------------
  // Compatibilidade
  // ------------------------------------------------

  std::cout << "expected: " << context.compiler.types.get(expected).to_string() << '\n';

  std::cout << "actual: " << context.compiler.types.get(actual).to_string() << '\n';

  if (!is_assignable(expected, actual)) {

    error(node, "return type is not assignable "
                "to function return type");

    return;
  }
}

} // namespace celestia::semantic