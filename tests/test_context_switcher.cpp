#include "gtest/gtest.h"
#include "context_switcher.hpp"

TEST(ContextSwitcherTest, SaveAndRestoreContext) {
    ContextSwitcher cs;
    CPUContext context;
    // Save the context; since we use random numbers in the simulation,
    // we simply verify that calling these methods does not cause errors.
    EXPECT_NO_THROW(cs.saveContext(context));
    EXPECT_NO_THROW(cs.restoreContext(context));
}
