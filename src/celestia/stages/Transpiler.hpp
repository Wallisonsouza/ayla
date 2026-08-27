#include "celestia/compiler/CompilationUnit.hpp"
#include "celestia/core/visitor/Stage.hpp"
#include "celestia/transpiler/CGenerator.hpp"

#include <filesystem>
#include <fstream>

class CTranspilePass : public Stage {
public:
  void run(CompilerEnvironment &env, CompilationUnit &unit) override {

    auto *module = unit.ast_module;

    std::filesystem::path output_dir = "out";

    std::filesystem::create_directories(output_dir);

    std::filesystem::path source = unit.source.path;
    std::filesystem::path output = output_dir / source.filename();

    output.replace_extension(".c");

    std::ofstream out(output);

    if (!out) return;

    celestia::codegen::CGeneratorContext ctx{.unit = unit, .compiler = env};
    
    celestia::codegen::CGenerator gen(out, ctx);

    gen.generate_module(module);
  }
};

// #include "celestia/compiler/CompilationUnit.hpp"
// #include "celestia/core/visitor/Stage.hpp"
// #include "celestia/transpiler/CGenerator.hpp"

// #include <cstdlib>
// #include <filesystem>
// #include <fstream>
// #include <iostream>

// class CTranspilePass : public Stage {
// public:
//   void run(CompilerEnvironment &env, CompilationUnit &unit) override {

//     auto *module = unit.module;

//     if (!module) return;

//     std::filesystem::path output_dir = "out";

//     std::filesystem::create_directories(output_dir);

//     std::filesystem::path source = unit.source.path;

//     std::filesystem::path c_file = output_dir / source.filename();

//     c_file.replace_extension(".c");

//     // --------------------------------------------------
//     // Gerar C
//     // --------------------------------------------------

//     {
//       std::ofstream out(c_file);

//       if (!out) {
//         std::cerr << "Could not create: " << c_file << '\n';

//         return;
//       }

//       celestia::codegen::CGenerator gen(out);

//       gen.generate_module(module);
//     }

//     // --------------------------------------------------
//     // Compilar C
//     // --------------------------------------------------

//     std::filesystem::path executable = output_dir / source.stem();

//     std::string command = "clang " + c_file.string() + " -o " + executable.string();

//     std::cout << "Compiling: " << command << '\n';

//     int result = std::system(command.c_str());

//     if (result != 0) {

//       std::cerr << "C compilation failed\n";

//       return;
//     }

//     std::cout << "Generated: " << c_file << '\n';

//     std::cout << "Executable: " << executable << '\n';
//   }
// };