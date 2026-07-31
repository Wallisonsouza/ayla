#pragma once
#include <deque>
#include <string_view>
#include <unordered_map>

template <typename T> struct TrieNode {
  bool is_terminal = false;
  T *value = nullptr;
  std::unordered_map<char32_t, TrieNode *> children;

  const TrieNode *child(char32_t c) const {
    auto it = children.find(c);
    return it == children.end() ? nullptr : it->second;
  }
};

template <typename T> class Trie {
private:
  TrieNode<T> root_;
  std::deque<TrieNode<T>> pool_;

  TrieNode<T> *create_node() {
    pool_.emplace_back();
    return &pool_.back();
  }

public:
  void clear() {
    root_ = TrieNode<T>{};
    pool_.clear();
  }

  const TrieNode<T> *root() const { return &root_; }

  void insert(std::string_view key, T *value) {
    TrieNode<T> *node = &root_;
    for (char32_t ch : key) {
      auto it = node->children.find(ch);
      if (it == node->children.end()) {
        TrieNode<T> *new_node = create_node();
        node->children[ch] = new_node;
        node = new_node;
      } else {
        node = it->second;
      }
    }
    node->is_terminal = true;
    node->value = value;
  }

  bool has_prefix(std::string_view prefix) const {
    const TrieNode<T> *node = &root_;
    for (char32_t ch : prefix) {
      auto it = node->children.find(ch);
      if (it == node->children.end()) return false;
      node = it->second;
    }
    return true;
  }

  T *lookup(std::string_view key) const {
    const TrieNode<T> *node = &root_;
    for (char32_t ch : key) {
      auto it = node->children.find(ch);
      if (it == node->children.end()) return nullptr;
      node = it->second;
    }
    return node->is_terminal ? node->value : nullptr;
  }
};
