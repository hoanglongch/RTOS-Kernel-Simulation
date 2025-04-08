#include "hal.hpp"
#include "logger.hpp"
#include <string>

HAL::HAL() {
    // Create module instances.
    interruptController_ = new InterruptHandler();
    contextSwitcher_ = new ContextSwitcher();
    mpuDriver_ = new MPUDriver();
}

HAL::~HAL() {
    // Clean up resources.
    delete interruptController_;
    delete contextSwitcher_;
    delete mpuDriver_;
}

bool HAL::initialize() {
    Logger::getInstance().info("HAL: Initializing hardware abstraction layer components...");

    // Initialize MPU. In a production environment, you might want to
    // check for additional hardware components.
    if (!mpuDriver_->initialize()) {
        Logger::getInstance().error("HAL: MPU initialization failed.");
        return false;
    }
    // Configure and enforce MPU regions as needed.
    mpuDriver_->configureRegion(0x20000000, 0x1000, 0x03);
    mpuDriver_->enforceMemoryProtection();

    Logger::getInstance().info("HAL: All components initialized successfully.");
    return true;
}

InterruptHandler& HAL::getInterruptHandler() {
    return *interruptController_;
}

ContextSwitcher& HAL::getContextSwitcher() {
    return *contextSwitcher_;
}

MPUDriver& HAL::getMPUDriver() {
    return *mpuDriver_;
}

void HAL::triggerInterrupt(int interruptNumber) {
    Logger::getInstance().info("HAL: Triggering interrupt " + std::to_string(interruptNumber));
    interruptController_->triggerInterrupt(interruptNumber);
}
