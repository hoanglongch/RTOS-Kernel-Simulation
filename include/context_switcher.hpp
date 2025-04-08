#ifndef CONTEXT_SWITCHER_HPP
#define CONTEXT_SWITCHER_HPP

#include <cstdint>
#include <array>

// Structure representing a simulated CPU context.
struct CPUContext {
    std::array<uint32_t, 16> registers; // Simulates R0-R15 registers.
    uint32_t cpsr;                      // Simulated current program status register.
};

class ContextSwitcher {
public:
    ContextSwitcher();
    ~ContextSwitcher();

    // Save the current CPU context (simulated).
    void saveContext(CPUContext& context);

    // Restore the given CPU context (simulated).
    void restoreContext(const CPUContext& context);
};

#endif // CONTEXT_SWITCHER_HPP
