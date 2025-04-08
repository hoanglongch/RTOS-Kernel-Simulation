#ifndef HAL_HPP
#define HAL_HPP

#include <cstdint>
#include <cstddef>
#include "context_switcher.hpp"
#include "interrupt_handler.hpp"
#include "mpu_driver.hpp"
#include "timer_driver.hpp"
#include "uart_driver.hpp"

// The HAL class abstracts hardware-specific functions such as interrupt management,
// context switching, memory protection, and additional device drivers.
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

    // Example function: trigger an interrupt via the HAL.
    void triggerInterrupt(int interruptNumber);

private:
    // Pointers to maintain module instances.
    InterruptHandler* interruptController_;
    ContextSwitcher* contextSwitcher_;
    MPUDriver* mpuDriver_;
    TimerDriver* timerDriver_;
    UARTDriver* uartDriver_;
};

#endif // HAL_HPP
