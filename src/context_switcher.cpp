#include "context_switcher.hpp"
#include "logger.hpp"
#include <cstdlib>
#include <sstream>

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
    Logger::getInstance().info("Context saved.");
}

void ContextSwitcher::restoreContext(const CPUContext& context) {
    std::ostringstream oss;
    oss << "Restoring context:\n";
    for (size_t i = 0; i < context.registers.size(); i++) {
        oss << "R" << i << ": " << context.registers[i] << " ";
        if (i % 4 == 3) {
            oss << "\n";
        }
    }
    oss << "CPSR: " << context.cpsr;
    Logger::getInstance().info(oss.str());
}
