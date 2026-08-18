// // TypeChecker.Arrays.cpp

// #include "celestia/semantic/checker/TypeChecker.hpp"
// #include "celestia/semantic/types/BuiltinTypes.hpp"

// namespace celestia::semantic {

// void TypeChecker::array_literal(ast::ArrayLiteralNode *node) {

//   if (!node) return;

//   for (auto *element : node->elements) {

//     if (!element) continue;

//     check(element);
//   }

//   if (node->elements.empty()) { return; }

//   const Type *element_type = nullptr;

//   for (auto *element : node->elements) {

//     if (!element) continue;

//     element_type = element->resolved_type;

//     if (element_type) break;
//   }

//   if (!element_type) return;

//   for (auto *element : node->elements) {

//     if (!element) continue;

//     if (!element->resolved_type) return;

//     if (!same_type(element_type, element->resolved_type)) { return; }
//   }

//   // Cria o tipo semântico do array.
//   node->resolved_type = make_array_type(element_type);
// }

// #include "celestia/semantic/checker/TypeChecker.hpp"
// #include "celestia/semantic/types/ArrayType.hpp"
// #include "celestia/semantic/types/BuiltinTypes.hpp"

// namespace celestia::semantic {

// const ArrayType *TypeChecker::make_array_type(const Type *element_type) {

//   if (!element_type) return nullptr;

//   return new ArrayType(element_type);
// }

// void TypeChecker::array_literal(ast::ArrayLiteralNode *node) {

//   if (!node) return;

//   for (auto *element : node->elements) {

//     if (!element) continue;

//     check(element);
//   }

//   if (node->elements.empty()) return;

//   const Type *element_type = nullptr;

//   for (auto *element : node->elements) {

//     if (!element) continue;

//     element_type = element->resolved_type;

//     if (element_type) break;
//   }

//   if (!element_type) return;

//   for (auto *element : node->elements) {

//     if (!element) continue;

//     if (!element->resolved_type) return;

//     if (!same_type(element_type, element->resolved_type)) { return; }
//   }

//   node->resolved_type = un make_array_type(element_type);
// }

// } // namespace celestia::semantic

// } // namespace celestia::semantic