#include "hal.hpp"
#include "logger.hpp"
#include <string>

HAL::HAL() {
    // Create instances for each component.
    interruptController_ = new InterruptHandler();
    contextSwitcher_     = new ContextSwitcher();
    mpuDriver_           = new MPUDriver();
    timerDriver_         = new TimerDriver();
    uartDriver_          = new UARTDriver();
    vmm_                 = new VirtualMemoryManager();  // New instance for advanced memory management.
}

HAL::~HAL() {
    delete interruptController_;
    delete contextSwitcher_;
    delete mpuDriver_;
    delete timerDriver_;
    delete uartDriver_;
    delete vmm_;
}

bool HAL::initialize() {
    Logger::getInstance().info("HAL: Initializing hardware abstraction layer components...");

    // Initialize MPU.
    if (!mpuDriver_->initialize()) {
        Logger::getInstance().error("HAL: MPU initialization failed.");
        return false;
    }
    mpuDriver_->configureRegion(0x20000000, 0x1000, 0x03);
    mpuDriver_->enforceMemoryProtection();

    // Initialize Timer Driver.
    if (!timerDriver_->initialize()) {
        Logger::getInstance().error("HAL: TimerDriver initialization failed.");
        return false;
    }

    // Initialize UART Driver.
    if (!uartDriver_->initialize()) {
        Logger::getInstance().error("HAL: UARTDriver initialization failed.");
        return false;
    }

    // Initialize Virtual Memory Manager.
    if (!vmm_->initialize()) {
        Logger::getInstance().error("HAL: VirtualMemoryManager initialization failed.");
        return false;
    }

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

TimerDriver& HAL::getTimerDriver() {
    return *timerDriver_;
}

UARTDriver& HAL::getUARTDriver() {
    return *uartDriver_;
}

VirtualMemoryManager& HAL::getVirtualMemoryManager() {
    return *vmm_;
}

void HAL::triggerInterrupt(int interruptNumber) {
    Logger::getInstance().info("HAL: Triggering interrupt " + std::to_string(interruptNumber));
    interruptController_->triggerInterrupt(interruptNumber);
}
