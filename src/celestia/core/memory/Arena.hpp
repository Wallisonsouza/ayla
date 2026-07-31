#pragma once
#include <algorithm>
#include <cstddef>
#include <memory>
#include <type_traits>
#include <vector>

namespace core::memory {

struct ArenaBlock {
  std::unique_ptr<char[]> data;
  size_t offset;
  size_t size;

  explicit ArenaBlock(size_t sz) : data(std::make_unique<char[]>(sz)), offset(0), size(sz) {}
};

class Arena {
  static constexpr size_t DEFAULT_BLOCK_SIZE = 64 * 1024;

  std::vector<ArenaBlock> blocks;

public:
  Arena() { blocks.emplace_back(DEFAULT_BLOCK_SIZE); }

  void *allocate(size_t size, size_t alignment = alignof(std::max_align_t)) {
    ArenaBlock *b = &blocks.back();
    void *ptr = b->data.get() + b->offset;
    size_t space = b->size - b->offset;

    if (void *aligned = std::align(alignment, size, ptr, space)) {
      b->offset = b->size - space + size;
      return aligned;
    }

    size_t blockSize = std::max(size + alignment, DEFAULT_BLOCK_SIZE);
    blocks.emplace_back(blockSize);
    return allocate(size, alignment);
  }

  template <typename T, typename... Args> T *alloc(Args &&...args) {
    static_assert(!std::is_array_v<T>, "T não pode ser um array");
    void *mem = allocate(sizeof(T), alignof(T));
    T *obj = new (mem) T(std::forward<Args>(args)...);
    return obj;
  }

  void reset() {
    blocks.clear();
    blocks.emplace_back(DEFAULT_BLOCK_SIZE);
  }
};

} // namespace core::memory
