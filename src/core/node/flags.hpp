#pragma once
#include <cstdint>

enum class NodeFlags : uint32_t {
  None = 0,
  HasError = 1 << 0,
  Synthetic = 1 << 1,
  Constant = 1 << 2,
  Used = 1 << 3,
  Resolved = 1 << 4,
  Checked = 1 << 5
};

struct NodeFlag {
  NodeFlags flags = NodeFlags::None;

  void set(NodeFlags flag) { flags = static_cast<NodeFlags>(static_cast<uint32_t>(flags) | static_cast<uint32_t>(flag)); }

  void remove(NodeFlags flag) { flags = static_cast<NodeFlags>(static_cast<uint32_t>(flags) & ~static_cast<uint32_t>(flag)); }

  bool has(NodeFlags flag) const { return (static_cast<uint32_t>(flags) & static_cast<uint32_t>(flag)) != 0; }

  void toggle(NodeFlags flag) { flags = static_cast<NodeFlags>(static_cast<uint32_t>(flags) ^ static_cast<uint32_t>(flag)); }

  void clear() { flags = NodeFlags::None; }
};

inline NodeFlags operator|(NodeFlags a, NodeFlags b) { return static_cast<NodeFlags>(static_cast<uint32_t>(a) | static_cast<uint32_t>(b)); }

inline NodeFlags operator&(NodeFlags a, NodeFlags b) { return static_cast<NodeFlags>(static_cast<uint32_t>(a) & static_cast<uint32_t>(b)); }

inline NodeFlags operator~(NodeFlags a) { return static_cast<NodeFlags>(~static_cast<uint32_t>(a)); }
