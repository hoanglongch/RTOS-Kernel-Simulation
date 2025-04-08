#include "interrupt_handler.hpp"
#include <iostream>

InterruptHandler::InterruptHandler() {
    // Initialization if needed
}

InterruptHandler::~InterruptHandler() {
    // Clean up resources if needed
}

void InterruptHandler::registerInterrupt(int interruptNumber, InterruptFunction callback) {
    std::lock_guard<std::mutex> lock(mtx_);
    interrupts_[interruptNumber] = callback;
}

void InterruptHandler::unregisterInterrupt(int interruptNumber) {
    std::lock_guard<std::mutex> lock(mtx_);
    interrupts_.erase(interruptNumber);
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
        func();
    } else {
        std::cerr << "No interrupt registered for: " << interruptNumber << std::endl;
    }
}
