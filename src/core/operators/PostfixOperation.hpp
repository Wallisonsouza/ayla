#pragma once

#include <string_view>

enum class PostfixOperation
{
    Call,
    IndexAccess,
    MemberAccess,
    Increment,
    Decrement
};

constexpr std::string_view to_string(PostfixOperation op)
{
    switch (op)
    {
        case PostfixOperation::Call:         return "()";
        case PostfixOperation::IndexAccess:  return "[]";
        case PostfixOperation::MemberAccess: return ".";
        case PostfixOperation::Increment:    return "++";
        case PostfixOperation::Decrement:    return "--";
    }

    return "?";
}