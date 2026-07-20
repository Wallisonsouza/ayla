#pragma once

#include <unordered_map>

#include "ast/AstNode.hpp"
#include "ast/NodeKind.hpp"

namespace ayla {

template<typename TOwner>
class Dispatcher {
public:
    using Handler = void (*)(TOwner&, ast::AstNode*);

    template<
        ast::NodeKind Kind,
        typename TNode,
        void (TOwner::*Fn)(TNode*)>
    void bind()
    {
        handlers.emplace(
            Kind,
            [](TOwner& owner, ast::AstNode* node)
            {
                (owner.*Fn)(
                    static_cast<TNode*>(node));
            });
    }

    void dispatch(TOwner& owner, ast::AstNode* node) const
    {
        if (!node)
            return;

        auto it = handlers.find(node->kind);

        if (it != handlers.end())
        {
            it->second(owner, node);
        }
    }

private:
    std::unordered_map<ast::NodeKind, Handler> handlers;
};

} // namespace ayla