#pragma once
#include <memory>
#include <vector>

struct Value;

using array = std::vector<std::shared_ptr<Value>>;

struct ArrayValue {
  array elements;

  size_t size() const;
  bool empty() const;

  std::shared_ptr<Value> get(size_t i) const;
  std::shared_ptr<Value> get_or_null(size_t i) const;

  void set(size_t i, std::shared_ptr<Value> v);

  void push(std::shared_ptr<Value> v);
  std::shared_ptr<Value> pop();

  void clear();

  void insert(size_t i, std::shared_ptr<Value> v);
  void remove(size_t i);
};
