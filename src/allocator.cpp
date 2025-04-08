#include "allocator.hpp"
#include <cstdlib>
#include <iostream>

void* NUMAAllocator::allocate(std::size_t size, int numaNode) {
    // In a real-world scenario, allocation may use huge page APIs and NUMA library calls.
    std::cout << "Allocating " << size << " bytes on NUMA node " << numaNode << std::endl;
    void* ptr = std::malloc(size);
    if (!ptr) {
        throw std::bad_alloc();
    }
    return ptr;
}

void NUMAAllocator::deallocate(void* ptr, std::size_t size) {
    std::cout << "Deallocating " << size << " bytes." << std::endl;
    std::free(ptr);
}
