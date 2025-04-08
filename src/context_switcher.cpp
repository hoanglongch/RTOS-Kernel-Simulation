#include "context_switcher.hpp"
#include <iostream>
#include <cstdlib>

ContextSwitcher::ContextSwitcher() {
    // Initialization if needed
}

ContextSwitcher::~ContextSwitcher() {
    // Cleanup if needed
}

void ContextSwitcher::saveContext(CPUContext& context) {
    // Simulate saving random register values.
    for (auto& reg : context.registers) {
        reg = rand();
    }
    context.cpsr = rand();
    std::cout << "Context saved." << std::endl;
}

void ContextSwitcher::restoreContext(const CPUContext& context) {
    // In a real OS, CPU registers would be restored. Here we just print them.
    std::cout << "Restoring context:" << std::endl;
    for (size_t i = 0; i < context.registers.size(); i++) {
        std::cout << "R" << i << ": " << context.registers[i] << " ";
        if (i % 4 == 3) {
            std::cout << std::endl;
        }
    }
    std::cout << "CPSR: " << context.cpsr << std::endl;
}
