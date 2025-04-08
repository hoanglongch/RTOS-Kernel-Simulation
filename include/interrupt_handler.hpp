#ifndef INTERRUPT_HANDLER_HPP
#define INTERRUPT_HANDLER_HPP

#include <functional>
#include <unordered_map>
#include <mutex>

// A class to simulate an interrupt handling system.
class InterruptHandler {
public:
    // Type for an interrupt routine.
    using InterruptFunction = std::function<void()>;

    InterruptHandler();
    ~InterruptHandler();

    // Register an interrupt number with its corresponding callback.
    void registerInterrupt(int interruptNumber, InterruptFunction callback);

    // Unregister an interrupt.
    void unregisterInterrupt(int interruptNumber);

    // Simulate the triggering of an interrupt.
    void triggerInterrupt(int interruptNumber);

private:
    std::unordered_map<int, InterruptFunction> interrupts_;
    std::mutex mtx_;
};

#endif // INTERRUPT_HANDLER_HPP
