#include "interrupt_handler.hpp"
#include "logger.hpp"
#include <sstream>

InterruptHandler::InterruptHandler() {
    // Initialization if needed
}

InterruptHandler::~InterruptHandler() {
    // Clean up if needed
}

void InterruptHandler::registerInterrupt(int interruptNumber, InterruptFunction callback) {
    std::lock_guard<std::mutex> lock(mtx_);
    interrupts_[interruptNumber] = callback;
    Logger::getInstance().debug("Registered interrupt " + std::to_string(interruptNumber));
}

void InterruptHandler::unregisterInterrupt(int interruptNumber) {
    std::lock_guard<std::mutex> lock(mtx_);
    interrupts_.erase(interruptNumber);
    Logger::getInstance().debug("Unregistered interrupt " + std::to_string(interruptNumber));
}

void InterruptHandler::triggerInterrupt(int interruptNumber) {
    InterruptFunction func;
    {
        std::lock_guard<std::mutex> lock(mtx_);
        auto it = interrupts_.find(interruptNumber);
        if (it != interrupts_.end()) {
            func = it->second;
        }
    }
    if (func) {
        Logger::getInstance().info("Triggering interrupt: " + std::to_string(interruptNumber));
        func();
    } else {
        Logger::getInstance().error("No interrupt registered for: " + std::to_string(interruptNumber));
    }
}
