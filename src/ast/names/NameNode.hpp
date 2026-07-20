#include "ast/AstNode.hpp"
#include "string"

namespace ayla::ast {

struct NameNode : AstNode {
  std::string str;
  explicit NameNode(std::string n) : AstNode(NodeKind::Name), str(std::move(n)) {}
};

} // namespace ayla::ast