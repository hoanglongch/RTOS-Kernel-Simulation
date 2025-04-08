#ifndef ALLOCATOR_HPP
#define ALLOCATOR_HPP

#include <cstddef>
#include <new>

// A custom memory allocator interface that simulates NUMA awareness and huge pages support.
class NUMAAllocator {
public:
    // Allocate memory from a simulated NUMA node.
    static void* allocate(std::size_t size, int numaNode = 0);

    // Deallocate memory.
    static void deallocate(void* ptr, std::size_t size);
};

#endif // ALLOCATOR_HPP
