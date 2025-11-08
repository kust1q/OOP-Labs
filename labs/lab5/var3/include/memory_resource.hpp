#pragma once

#include <cstring>
#include <memory_resource>
#include <map>

#include "exceptions.hpp"

class MemoryResource: public std::pmr::memory_resource {
private:
    int8_t* pool_;
    size_t pool_size_;
    size_t block_size_;
    std::map<void*, bool> blocks_;

public:
    MemoryResource(size_t pool_size, size_t block_size);
    ~MemoryResource() override;

protected:
    void* do_allocate(std::size_t bytes, std::size_t alignment) override;
    void do_deallocate(void* ptr, std::size_t bytes, std::size_t alignment) override;
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override;
};