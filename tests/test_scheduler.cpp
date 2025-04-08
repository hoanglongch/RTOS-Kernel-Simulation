#include "gtest/gtest.h"
#include "scheduler.hpp"
#include "task.hpp"
#include <atomic>
#include <thread>
#include <chrono>

TEST(SchedulerTest, TaskExecution) {
    Scheduler scheduler;
    std::atomic<int> counter{0};

    // Create several simple tasks that increment a counter.
    for (int i = 0; i < 5; i++) {
        Task task;
        task.id = i;
        task.name = "Task_" + std::to_string(i);
        task.basePriority = 10;
        task.currentPriority = task.basePriority;
        task.taskFunction = [&counter]() {
            counter.fetch_add(1);
        };
        scheduler.addTask(task);
    }

    scheduler.start();
    // Allow some time for tasks to execute.
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    scheduler.stop();

    EXPECT_EQ(counter.load(), 5);
}

TEST(SchedulerTest, PriorityInheritance) {
    Scheduler scheduler;
    Task task;
    task.id = 1;
    task.name = "BlockedTask";
    task.basePriority = 5;
    task.currentPriority = task.basePriority;
    // There is no real blocking in our simulation. We manually invoke applyPriorityInheritance.
    scheduler.applyPriorityInheritance(task, 10);
    EXPECT_EQ(task.currentPriority, 10);
}
