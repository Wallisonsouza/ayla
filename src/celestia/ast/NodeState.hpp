#pragma once

#include "NodeFlags.hpp"


struct NodeState
{
    NodeFlags flags = NodeFlags::None;


    constexpr void add(NodeFlags flag)
    {
        flags = flags | flag;
    }


    constexpr void remove(NodeFlags flag)
    {
        flags = flags & ~flag;
    }


    constexpr bool has(NodeFlags flag) const
    {
        return static_cast<uint32_t>(flags & flag) != 0;
    }


    constexpr void clear()
    {
        flags = NodeFlags::None;
    }
};