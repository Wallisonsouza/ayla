#pragma once

#include <cstdint>

enum class Modifier : uint32_t
{
    None    = 0,

    Static  = 1 << 0,
    Extern  = 1 << 1,
    Async   = 1 << 2,
    Inline  = 1 << 3,
    Const   = 1 << 4
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