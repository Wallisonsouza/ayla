#pragma once

namespace celestia::semantic {

enum class TypeKind {
    Unknown,
    Primitive,
    Function,
    GenericDefinition,
    GenericInstance,
    Generic,
    Struct,
    Object,
 
};

}