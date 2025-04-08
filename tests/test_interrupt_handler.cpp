#include "gtest/gtest.h"
#include "interrupt_handler.hpp"
#include "logger.hpp"
#include <atomic>

TEST(InterruptHandlerTest, RegisterAndTriggerInterrupt) {
    // Disable logging output for tests if desired.
    InterruptHandler handler;
    std::atomic<bool> triggered(false);
    handler.registerInterrupt(1, [&]() {
        triggered.store(true);
    });
    handler.triggerInterrupt(1);
    EXPECT_TRUE(triggered.load());
}

TEST(InterruptHandlerTest, UnregisteredInterruptFails) {
    InterruptHandler handler;
    // When triggering an unregistered interrupt, we expect nothing to be called.
    // To test this, you might maintain a flag or rely on the absence of side effects.
    // For demonstration, we simply trigger and check that no exceptions occur.
    EXPECT_NO_THROW(handler.triggerInterrupt(99));
}
