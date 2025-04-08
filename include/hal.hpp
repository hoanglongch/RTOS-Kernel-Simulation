#ifndef HAL_HPP
#define HAL_HPP

#include <cstdint>
#include <cstddef>
#include "context_switcher.hpp"
#include "interrupt_handler.hpp"
#include "mpu_driver.hpp"

// The HAL class abstracts hardware-specific functions such as interrupt management,
// context switching, and memory protection.
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

    // Example function: trigger an interrupt via the HAL.
    void triggerInterrupt(int interruptNumber);

    // Future expansion: functions to abstract more hardware operations like
    // memory management or device drivers can be added here.

private:
    // Pointers (or smart pointers in a production system) to maintain module instances.
    InterruptHandler* interruptController_;
    ContextSwitcher* contextSwitcher_;
    MPUDriver* mpuDriver_;
};

#endif // HAL_HPP
