#include "hal.hpp"
#include "logger.hpp"
#include "scheduler.hpp"
#include "task.hpp"
#include "allocator.hpp"

#include <thread>
#include <chrono>
#include <string>
#include <cstdint>

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

    // --- Virtual Memory Manager Usage via HAL ---
    // Map a region:
    //   Virtual Address: 0x40000000
    //   Physical Address: 0x80000000
    //   Size: 4096 bytes
    //   Permissions: READ | WRITE
    if (hal.getVirtualMemoryManager().mapRegion(0x40000000, 0x80000000, 4096, 
            MemoryPermissions::READ | MemoryPermissions::WRITE)) {
        Logger::getInstance().info("Mapped virtual region 0x40000000 successfully.");
    }

    // Translate a valid virtual address within the mapped region.
    uint32_t physicalAddress;
    if (hal.getVirtualMemoryManager().translateAddress(0x40000010, physicalAddress)) {
        Logger::getInstance().info("Translated virtual address 0x40000010 to physical address: 0x" +
            std::to_string(physicalAddress));
    } else {
        hal.getVirtualMemoryManager().handlePageFault(0x40000010);
    }

    // Attempt to translate an unmapped virtual address to trigger a page fault.
    if (!hal.getVirtualMemoryManager().translateAddress(0x50000000, physicalAddress)) {
        hal.getVirtualMemoryManager().handlePageFault(0x50000000);
    }

    // Dump the current page table for debugging.
    Logger::getInstance().debug(hal.getVirtualMemoryManager().dumpPageTable());

    // --- Network Driver Usage via HAL ---
    // Send a simulated network packet.
    hal.getNetworkDriver().sendPacket("Hello from RTOS!");
    // Receive a simulated network packet.
    std::string packet = hal.getNetworkDriver().receivePacket();
    Logger::getInstance().info("Main: Received packet: " + packet);

    // --- Allow the scheduler to run for a short period ---
    std::this_thread::sleep_for(std::chrono::seconds(1));
    scheduler.stop();

    Logger::getInstance().info("RTOS Simulation Ending.");
    return 0;
}
