#pragma once
#include "TrieNode.hpp"

#include "ayla-structural/ayla-token/descriptor.hpp"
#include "ayla-structural/ayla-token/kind.hpp"
#include "core/hash/TransparentHash.hpp"

#include <deque>
#include <string>
#include <unordered_map>

namespace core::table {

class DescriptorTable {
public:
  ayla::structural::token::TokenDescriptor &add(ayla::structural::token::TokenKind kind, const std::string &name, ayla::structural::token::TokenGroup group) {
    storage_.emplace_back(kind, group, name);
    ayla::structural::token::TokenDescriptor &desc = storage_.back();
    by_kind_[kind] = &desc;
    by_name_[name] = &desc;
    trie_.insert(name, &desc);
    return desc;
  }

  // Adiciona um token sem nome (ex.: ayla::structural::token::TokenKind::Identifier)
  ayla::structural::token::TokenDescriptor &add(ayla::structural::token::TokenKind kind, ayla::structural::token::TokenGroup group) {
    storage_.emplace_back(kind, group, "");
    ayla::structural::token::TokenDescriptor &desc = storage_.back();
    by_kind_[kind] = &desc;
    return desc;
  }

  // Adiciona um alias para um ayla::structural::token::TokenDescriptor existente
  void add_alias(ayla::structural::token::TokenKind kind, const std::string &alias) {

    auto desc = lookup_by_kind(kind);
    if (!desc) { return; }

    by_name_[alias] = desc;
    trie_.insert(alias, desc);
    desc->aliases.push_back(alias);
  }

  ayla::structural::token::TokenDescriptor *lookup_by_kind(ayla::structural::token::TokenKind kind) {
    auto it = by_kind_.find(kind);
    return it != by_kind_.end() ? it->second : nullptr;
  }

  ayla::structural::token::TokenDescriptor *lookup_by_name(const std::string_view &name) {
    auto it = by_name_.find(std::string(name));
    return it != by_name_.end() ? it->second : nullptr;
  }

  bool has_prefix(const std::string_view &prefix) const { return trie_.has_prefix(prefix); }

  const std::deque<ayla::structural::token::TokenDescriptor> &all() const { return storage_; }

  const std::unordered_map<std::string, ayla::structural::token::TokenDescriptor *, U32Hash, U32Equal> &all_names() const { return by_name_; }

  Trie<ayla::structural::token::TokenDescriptor> &trie() { return trie_; }

private:
  std::deque<ayla::structural::token::TokenDescriptor> storage_;
  std::unordered_map<ayla::structural::token::TokenKind, ayla::structural::token::TokenDescriptor *> by_kind_;
  std::unordered_map<std::string, ayla::structural::token::TokenDescriptor *, U32Hash, U32Equal> by_name_;
  Trie<ayla::structural::token::TokenDescriptor> trie_;
};

} // namespace core::table
