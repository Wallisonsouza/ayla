#pragma once

#include <string_view>

enum class UnaryOperation
{
    Plus,
    Minus,

    Not,
    BitNot,

    Dereference,
    AddressOf,

    PreIncrement,
    PreDecrement,

    PostIncrement,
    PostDecrement
};

constexpr std::string_view to_string(UnaryOperation op)
{
    switch (op)
    {
        case UnaryOperation::Plus:          return "+";
        case UnaryOperation::Minus:         return "-";
        case UnaryOperation::Not:           return "!";
        case UnaryOperation::BitNot:        return "~";
        case UnaryOperation::Dereference:   return "*";
        case UnaryOperation::AddressOf:     return "&";
        case UnaryOperation::PreIncrement:  return "++";
        case UnaryOperation::PreDecrement:  return "--";
        case UnaryOperation::PostIncrement: return "++";
        case UnaryOperation::PostDecrement: return "--";
    }

    return "?";
}