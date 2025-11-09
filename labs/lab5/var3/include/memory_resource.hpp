#pragma once

#include <cstring>
#include <memory_resource>
#include <map>

#include "exceptions.hpp"

namespace {
    inline const size_t POOLSIZE = 4096;
}

class MemoryResource: public std::pmr::memory_resource {
private:
    size_t pool_size_{POOLSIZE};
    int8_t* pool_;
    std::map<void*, size_t> blocks_;

public:
    MemoryResource();
    ~MemoryResource() override;
    MemoryResource(const MemoryResource&) = delete;
    MemoryResource& operator=(const MemoryResource&) = delete;
    MemoryResource(MemoryResource&&) = delete;
    MemoryResource& operator=(MemoryResource&&) = delete;

protected:
    void* do_allocate(std::size_t bytes, std::size_t alignment) override;
    void do_deallocate(void* ptr, std::size_t bytes, std::size_t alignment) override;
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override;
};