#include "hal.hpp"
#include "logger.hpp"
#include "scheduler.hpp"
#include "task.hpp"
#include "allocator.hpp"

#include <thread>
#include <chrono>
#include <string>

int main() {
    // Configure the logger subsystem.
    Logger::getInstance().setLogLevel(LogLevel::DEBUG);
    Logger::getInstance().setLogFile("rtos.log");
    Logger::getInstance().info("RTOS Simulation Starting via HAL...");

    // --- Initialize the Hardware Abstraction Layer (HAL) ---
    HAL hal;
    if (!hal.initialize()) {
        Logger::getInstance().error("HAL initialization failed. Exiting...");
        return -1;
    }

    // --- Interrupt Handler via HAL ---
    hal.getInterruptHandler().registerInterrupt(1, [](){
        Logger::getInstance().info("HAL: Handling interrupt 1: Timer tick.");
    });
    hal.getInterruptHandler().registerInterrupt(2, [](){
        Logger::getInstance().info("HAL: Handling interrupt 2: External event.");
    });
    
    // Simulate triggering of interrupts via HAL.
    hal.triggerInterrupt(1);
    hal.triggerInterrupt(2);

    // --- Context Switcher via HAL ---
    CPUContext context;
    hal.getContextSwitcher().saveContext(context);
    hal.getContextSwitcher().restoreContext(context);

    // --- Scheduler Setup ---
    Scheduler scheduler;
    scheduler.start();

    // Create several example tasks.
    for (int i = 0; i < 5; ++i) {
        Task task;
        task.id = i;
        task.name = "Task_" + std::to_string(i);
        task.basePriority = 10 - i;  // Higher value means higher priority.
        task.currentPriority = task.basePriority;
        task.taskFunction = [i]() {
            Logger::getInstance().info("Executing Task " + std::to_string(i) + " logic...");
            std::this_thread::sleep_for(std::chrono::microseconds(30));
        };
        scheduler.addTask(task);
    }

    // --- Memory Allocator ---
    const std::size_t bufferSize = 1024;
    void* buffer = NUMAAllocator::allocate(bufferSize, 1);
    // (Simulated usage of allocated memory)
    NUMAAllocator::deallocate(buffer, bufferSize);

    // Allow the scheduler to run for a short period.
    std::this_thread::sleep_for(std::chrono::seconds(1));
    scheduler.stop();

    Logger::getInstance().info("RTOS Simulation Ending.");
    return 0;
}
