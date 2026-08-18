#include <cstdint>

namespace celestia::ast {
enum class NodeFlags : uint32_t { None = 0, HasError = 1 << 0, Synthetic = 1 << 1, Used = 1 << 2, Resolved = 1 << 3, Checked = 1 << 4 };

constexpr NodeFlags operator|(NodeFlags a, NodeFlags b) { return static_cast<NodeFlags>(static_cast<uint32_t>(a) | static_cast<uint32_t>(b)); }

constexpr NodeFlags operator&(NodeFlags a, NodeFlags b) { return static_cast<NodeFlags>(static_cast<uint32_t>(a) & static_cast<uint32_t>(b)); }

constexpr NodeFlags operator~(NodeFlags a) { return static_cast<NodeFlags>(~static_cast<uint32_t>(a)); }

} // namespace celestia::ast