#include "allocator.hpp"
#include "logger.hpp"
#include <cstdlib>

void* NUMAAllocator::allocate(std::size_t size, int numaNode) {
    Logger::getInstance().info("Allocating " + std::to_string(size) + " bytes on NUMA node " + std::to_string(numaNode));
    void* ptr = std::malloc(size);
    if (!ptr) {
        throw std::bad_alloc();
    }
    return ptr;
}

void NUMAAllocator::deallocate(void* ptr, std::size_t size) {
    Logger::getInstance().info("Deallocating " + std::to_string(size) + " bytes.");
    std::free(ptr);
}
