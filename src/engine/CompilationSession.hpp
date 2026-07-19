
// #include "core/managers/source_manager.hpp"
// #include "engine/CompilationUnit.hpp"
// #include "engine/Pipeline.hpp"
// #include "engine/compilation_unit_manager.hpp"

// #include <memory>
// #include <vector>

// class CompilationSession {

//   LanguageContext &context;

//   CompilationUnitManager comp_manager;
//   SourceManager source_manager;
//   Pipeline pipeline;

// public:
//   CompilationSession(LanguageContext &ctx) : context(ctx) {}

//   CompilationUnit &add_unity(const std::string &path) {
//     auto  *src = source_manager.create_source(path);
//     return *comp_manager.create_compilation_unit(context, *src);
//   }

//   void add_pass(std::unique_ptr<Pass> pass) { pipeline.add_pass(std::move(pass)); }

//   void run_pipeline() {
//     for (auto &unit : comp_manager.arena) { pipeline.run(*unit); }
//   }

//   CompilationUnit &entry_unit() { return *comp_manager.units.front(); }
// };

// // auto ptr = std::make_shared<GenModule>();

// // auto byte_code = BytecodeGenerator(ptr.get());

// // for (auto &unit : comp_manager.units) {
// //   byte_code.generate_ast(unit->ast.get_nodes());
// //   byte_code.finalize_script();
// // }

// // byte_code.print_bytecode();
// // // AylaVM vm;
// // // vm.execute(*ptr);