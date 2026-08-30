#include "CGenerator.hpp"

#include "celestia/ast/types/GenericType.hpp"
#include "celestia/ast/types/NamedType.hpp"

#include <string>

namespace celestia::codegen {
  
void CGenerator::generate() {
  for (uint32_t i = 0; i < ir.struct_count(); ++i) { generate_struct(ir::StructId{i}); }
}

} // namespace celestia::codegen