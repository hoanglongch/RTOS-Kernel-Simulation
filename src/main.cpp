#include "interrupt_handler.hpp"
#include "context_switcher.hpp"
#include "mpu_driver.hpp"
#include "scheduler.hpp"
#include "allocator.hpp"
#include "task.hpp"
#include "logger.hpp"

#include <thread>
#include <chrono>
#include <string>

int main() {
    // Configure the logger subsystem.
    Logger::getInstance().setLogLevel(LogLevel::DEBUG);
    Logger::getInstance().setLogFile("rtos.log");
    Logger::getInstance().info("Real-Time Operating System Simulation Starting...");

    // --- MPU Driver ---
    MPUDriver mpu;
    if (mpu.initialize()) {
        mpu.configureRegion(0x20000000, 0x1000, 0x03);
        mpu.enforceMemoryProtection();
    }

    // --- Interrupt Handler ---
    InterruptHandler ih;
    ih.registerInterrupt(1, [](){
        Logger::getInstance().info("Handling interrupt 1: Timer tick.");
    });
    ih.registerInterrupt(2, [](){
        Logger::getInstance().info("Handling interrupt 2: External event.");
    });
    
    // Simulate triggering of interrupts.
    ih.triggerInterrupt(1);
    ih.triggerInterrupt(2);

    // --- Context Switcher ---
    ContextSwitcher cs;
    CPUContext context;
    cs.saveContext(context);
    cs.restoreContext(context);

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
        task.taskFunction = [i](){
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
