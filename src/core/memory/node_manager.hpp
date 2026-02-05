// #pragma once
// #include "frontend/ast/AstNode.hpp"
// #include <memory>
// #include <vector>

// namespace core {

// using NodeId = size_t;

// struct NodeManager {

//   std::vector<std::unique_ptr<node::Node>> nodes;

//   template <typename NodeType, typename... Args>
//   NodeId create_node(Args &&...args) {
//     NodeId id = nodes.size();
//     nodes.push_back(std::make_unique<NodeType>(std::forward<Args>(args)...));
//     return id;
//   }

//   node::Node *get(NodeId id) {
//     if (id >= nodes.size())
//       return nullptr;
//     return nodes[id].get();
//   }

//   const node::Node *get(NodeId id) const {
//     if (id >= nodes.size())
//       return nullptr;
//     return nodes[id].get();
//   }

//   size_t size() const { return nodes.size(); }
// };

// } // namespace core
