#include "memory_resource.hpp"

MemoryResource::MemoryResource(size_t pool_size, size_t block_size): pool_size_(pool_size), block_size_(block_size) {
    if (block_size == 0) {
        throw InvalidBlockSizeException("Block size must be > 0");
    }
    if (pool_size < block_size) {
        throw InvalidPoolSizeException("Pool size must be >= block size");
    }

    pool_ = new int8_t[pool_size];
    for (size_t i = 0; i < pool_size; i += block_size) {
        void* ptr = static_cast<void*>(pool_ + i);
        blocks_[ptr] = false;
    }
}

MemoryResource::~MemoryResource() {
    delete[] pool_;
}

void* MemoryResource::do_allocate(std::size_t bytes, std::size_t alignment) {
    if (bytes > block_size_) {
        throw std::bad_alloc();
    }

    for (auto& [ptr, is_used] : blocks_) {
        if (!is_used) {
            is_used = true;
            return ptr;
        }
    }

    throw std::bad_alloc();
}

void MemoryResource::do_deallocate(void* ptr, std::size_t bytes, std::size_t alignment) {
    auto it = blocks_.find(ptr);
    if (it != blocks_.end()) {
        it->second = false;
    }
}

bool MemoryResource::do_is_equal(const std::pmr::memory_resource& other) const noexcept {
    return this == &other;
}