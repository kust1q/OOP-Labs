#include "memory_resource.hpp"

MemoryResource::MemoryResource() {
    pool_ = new int8_t[pool_size_];
}

MemoryResource::~MemoryResource() {
    delete[] pool_;
}

void* MemoryResource::do_allocate(std::size_t bytes, std::size_t alignment) {
    if (bytes == 0) {
        return nullptr;
    }

    size_t current_offset = 0;

    for (const auto& [ptr, size] : blocks_) {
        int8_t* block_ptr = reinterpret_cast<int8_t*>(ptr);
        size_t block_offset = block_ptr - pool_;
        
        if (current_offset + bytes <= block_offset) {
            void* result = pool_ + current_offset;
            blocks_[result] = bytes;
            return result;
        }
        
        current_offset = block_offset + size;
    }
    
    if (current_offset + bytes <= pool_size_) {
        void* result = pool_ + current_offset;
        blocks_[result] = bytes;
        return result;
    }
    
    throw std::bad_alloc();
}

void MemoryResource::do_deallocate(void* ptr, std::size_t bytes, std::size_t alignment) {
    auto it = blocks_.find(ptr);
    if (it == blocks_.end()) {
        throw InvalidDeallocatedBlockException("Unable to free unallocated memory");
    }
    if (it->second != bytes) {
        throw InvalidDeallocatedBitesSisezSizeException("Wrong block size to deallocate");
    }

    blocks_.erase(it);
}   

bool MemoryResource::do_is_equal(const std::pmr::memory_resource& other) const noexcept {
    return this == &other;
}