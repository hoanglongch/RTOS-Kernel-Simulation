#include "gtest/gtest.h"
#include "allocator.hpp"

TEST(AllocatorTest, AllocateAndDeallocate) {
    const std::size_t size = 1024;
    // Allocate memory from node 0.
    void* ptr = nullptr;
    EXPECT_NO_THROW(ptr = NUMAAllocator::allocate(size, 0));
    EXPECT_NE(ptr, nullptr);
    // Deallocate and check for any exceptions.
    EXPECT_NO_THROW(NUMAAllocator::deallocate(ptr, size));
}
