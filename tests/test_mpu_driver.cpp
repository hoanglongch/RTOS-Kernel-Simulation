#include "gtest/gtest.h"
#include "mpu_driver.hpp"

TEST(MPUDriverTest, InitializeAndConfigure) {
    MPUDriver mpu;
    EXPECT_TRUE(mpu.initialize());
    EXPECT_TRUE(mpu.configureRegion(0x20000000, 0x1000, 0x03));
}

TEST(MPUDriverTest, EnforceWithoutInitialization) {
    MPUDriver mpu;
    // Directly call enforce to see that it handles uninitialized state.
    // In this test, we simply check that no exceptions are thrown.
    EXPECT_NO_THROW(mpu.enforceMemoryProtection());
}
