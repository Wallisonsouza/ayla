#include "AstDumper.hpp"

#include "ast/expressions/LiteralExpressionNode.hpp"

#include <format>

void AstDumper::dump_number_literal(
    const ayla::ast::node::NumberLiteralNode *node)
{
    auto g = context.object(
        std::format("Number({})", node->value));

    (void)g;
}

void AstDumper::dump_string_literal(
    const ayla::ast::node::StringLiteralNode *node)
{
    auto g = context.object(
        std::format("String(\"{}\")", node->value));

    (void)g;
}

void AstDumper::dump_bool_literal(
    const ayla::ast::node::BoolLiteralNode *node)
{
    auto g = context.object(
        std::format(
            "Boolean({})",
            node->value ? "true" : "false"));

    (void)g;
}

void AstDumper::dump_null_literal(
    const ayla::ast::node::NullLiteralNode *node)
{
    (void)node;

    auto g = context.object("Null");

    (void)g;
}

void AstDumper::dump_array_literal(
    const ayla::ast::node::ArrayLiteralNode *node)
{
    auto g = context.object("ArrayLiteral");

    g.list("Elements", node->elements);
}

void AstDumper::dump_object_literal(
    const ayla::ast::node::ObjectLiteralNode *node)
{
    auto g = context.object("ObjectLiteral");

    g.list("Fields", node->fields);
}