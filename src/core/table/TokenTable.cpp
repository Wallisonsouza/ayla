// #pragma once
// #include "TrieNode.hpp"
// #include "core/hash/TransparentHash.hpp"
// #include "core/token/TokenDescriptor.hpp"
// #include "core/token/TokenGroup.hpp"
//
// #include <deque>
// #include <string>
// #include <unordered_map>

// namespace core::table {

// class DescriptorTable {
// public:
//     // Adiciona um token principal com nome
//     token::TokenDescriptor &add(TokenKind kind, const std::string &name,
//     token::TokenGroup group) {
//         storage_.emplace_back(kind, group, name);
//         TokenDescriptor &desc = storage_.back();
//         by_kind_[kind] = &desc;
//         by_name_[name] = &desc;
//         trie_.insert(name, &desc);
//         return desc;
//     }

//     // Adiciona um token sem nome (ex.: ayla::structural::token::TokenKind::Identifier)
//     token::TokenDescriptor &add(TokenKind kind, token::TokenGroup group) {
//         storage_.emplace_back(kind, group, "");
//         TokenDescriptor &desc = storage_.back();
//         by_kind_[kind] = &desc;
//         return desc;
//     }

//     // Adiciona um alias para um TokenDescriptor existente
//     void add_alias(TokenKind kind, const std::string &alias) {
//         auto it = by_kind_.find(kind);
//         if (!it) return; // token principal não existe
//         TokenDescriptor *desc = it->second;
//         by_name_[alias] = desc;
//         trie_.insert(alias, desc);
//         desc->aliases.push_back(alias); // opcional, útil para help
//     }

//     token::TokenDescriptor *lookup_by_kind(TokenKind kind) {
//         auto it = by_kind_.find(kind);
//         return it != by_kind_.end() ? it->second : nullptr;
//     }

//     token::TokenDescriptor *lookup_by_name(const std::string_view &name) {
//         auto it = by_name_.find(std::string(name));
//         return it != by_name_.end() ? it->second : nullptr;
//     }

//     bool has_prefix(const std::string_view &prefix) const {
//         return trie_.has_prefix(prefix);
//     }

//     const std::deque<token::TokenDescriptor> &all() const { return storage_;
//     }

//     const std::unordered_map<std::string, token::TokenDescriptor *>
//     &all_names() const { return by_name_; }

// private:
//     std::deque<token::TokenDescriptor> storage_;
//     std::unordered_map<TokenKind, token::TokenDescriptor *> by_kind_;
//     std::unordered_map<std::string, token::TokenDescriptor *, U32Hash,
//     U32Equal> by_name_; Trie<token::TokenDescriptor> trie_;
// };

// } // namespace core::table
