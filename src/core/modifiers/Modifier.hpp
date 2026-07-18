#pragma once

#include <cstdint>

enum class Modifier : uint32_t
{
    None    = 0,

    Static  = 1 << 0,
    Mut     = 1 << 1,
    Extern  = 1 << 2,
    Async   = 1 << 3,
    Inline  = 1 << 4,
    Const   = 1 << 5
};

constexpr Modifier operator|(Modifier a, Modifier b)
{
    return static_cast<Modifier>(
        static_cast<uint32_t>(a) |
        static_cast<uint32_t>(b)
    );
}

constexpr Modifier operator&(Modifier a, Modifier b)
{
    return static_cast<Modifier>(
        static_cast<uint32_t>(a) &
        static_cast<uint32_t>(b)
    );
}

constexpr Modifier operator~(Modifier value)
{
    return static_cast<Modifier>(
        ~static_cast<uint32_t>(value)
    );
}