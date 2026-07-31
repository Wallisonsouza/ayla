#include "celestia/semantic/types/type.hpp"
namespace semantic {

struct BuiltinTypes {

  celestia::semantic::Type *Unknown;
  celestia::semantic::Type *Number;
  celestia::semantic::Type *String;
  celestia::semantic::Type *Boolean;
  celestia::semantic::Type *Char;
  celestia::semantic::Type *Null;
  celestia::semantic::Type *Void;
};

} // namespace semantic