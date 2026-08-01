// #include "TypeChecker.hpp"
// #include <iostream>

// void ayla::TypeChecker::check_module_declaration(celestia::ast::ModuleDeclaration *node) {
//   if (!node) return;

   

//   // auto *module = unit.context.module_manager.get(node->resolved_module_id);
//   // if (!module) return;

//   // module->type = unit.context.type_arena.alloc<ModuleType>();

//   // for (auto *stmt : node->body) {

//   //   if (!stmt) continue;

//   //   check(stmt);

//   //   if (auto *fn = dynamic_cast<celestia::ast::FunctionDeclarationNode *>(stmt)) {

//   //     if (fn->identifier) module->type->add_member(fn->identifier->name, fn->inferred_type);
//   //   }
//   // }

//   // node->inferred_type = module->type;

//   // if (auto *sym = unit.context.symbol_manager.get(node->resolved_symbol_id)) { sym->type = module->type; }
// }

// void ayla::TypeChecker::check_import_declaration_node(celestia::ast::ImportDeclarationNode *node) {




//   // if (!node) return;

//   // auto *module = unit.context.module_manager.get(node->resolved_module_id);
//   // if (!module) {
//   //   //report_error(DiagnosticCode::ModuleNotFound, node->slice);
//   //   node->inferred_type = &BuiltinTypes::Unknown;
//   //   return;
//   // }

//   // node->inferred_type = module->type;

//   // if (auto *sym = unit.context.symbol_manager.get(node->resolved_symbol_id)) { sym->type = node->inferred_type; }
// }
