#ifndef HAL_HPP
#define HAL_HPP

#include <cstdint>
#include <cstddef>
#include "context_switcher.hpp"
#include "interrupt_handler.hpp"
#include "mpu_driver.hpp"
#include "timer_driver.hpp"
#include "uart_driver.hpp"
#include "virtual_memory_manager.hpp"
#include "network_driver.hpp"   // New include for NetworkDriver

// The HAL class abstracts hardware-specific functions including interrupt management,
// context switching, memory protection, additional device drivers, and advanced memory management.
class HAL {
public:
    HAL();
    ~HAL();

    // Initialize all HAL components.
    // Returns true if all components were successfully initialized.
    bool initialize();

    // Access underlying HAL components.
    InterruptHandler& getInterruptHandler();
    ContextSwitcher& getContextSwitcher();
    MPUDriver& getMPUDriver();
    TimerDriver& getTimerDriver();
    UARTDriver& getUARTDriver();
    VirtualMemoryManager& getVirtualMemoryManager();
    NetworkDriver& getNetworkDriver(); // New accessor for NetworkDriver

    // Trigger an interrupt via the HAL.
    void triggerInterrupt(int interruptNumber);

private:
    InterruptHandler* interruptController_;
    ContextSwitcher* contextSwitcher_;
    MPUDriver* mpuDriver_;
    TimerDriver* timerDriver_;
    UARTDriver* uartDriver_;
    VirtualMemoryManager* vmm_;
    NetworkDriver* networkDriver_;  // New pointer for NetworkDriver
};

#endif // HAL_HPP
