#include "scheduler.hpp"
#include "logger.hpp"
#include <chrono>
#include <sstream>

Scheduler::Scheduler() : running_(false) {}

Scheduler::~Scheduler() {
    stop();
}

void Scheduler::addTask(const Task& task) {
    std::lock_guard<std::mutex> lock(queueMutex_);
    taskQueue_.push(task);
    Logger::getInstance().debug("Task [" + task.name + "] added with priority " + std::to_string(task.currentPriority));
    cv_.notify_one();
}

void Scheduler::start() {
    running_ = true;
    Logger::getInstance().info("Scheduler starting.");
    schedulerThread_ = std::thread(&Scheduler::schedulerLoop, this);
}

void Scheduler::stop() {
    running_ = false;
    cv_.notify_all();
    if (schedulerThread_.joinable()) {
        schedulerThread_.join();
    }
    Logger::getInstance().info("Scheduler stopped.");
}

void Scheduler::schedulerLoop() {
    while (running_) {
        std::unique_lock<std::mutex> lock(queueMutex_);
        cv_.wait(lock, [this]{ return !taskQueue_.empty() || !running_; });
        if (!running_) break;
        if (taskQueue_.empty()) continue;
        
        // Fetch the highest priority task.
        Task task = taskQueue_.top();
        taskQueue_.pop();
        lock.unlock();

        // Simulate precise context switch timing.
        auto start = std::chrono::high_resolution_clock::now();

        // Execute the task.
        if (task.taskFunction) {
            Logger::getInstance().info("Executing Task [" + task.name + "].");
            task.taskFunction();
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::ostringstream oss;
        oss << "Task [" << task.name << "] executed in " << duration.count() << " microseconds.";
        Logger::getInstance().info(oss.str());
        
        // For recurring or blocked tasks, additional logic could reinsert tasks
        // with updated priorities after applying priority inheritance.
    }
}

void Scheduler::applyPriorityInheritance(Task& blockedTask, int blockingTaskPriority) {
    if (blockingTaskPriority > blockedTask.currentPriority) {
        blockedTask.currentPriority = blockingTaskPriority;
        Logger::getInstance().warn("Priority inheritance applied: Task [" 
            + blockedTask.name + "] elevated to priority " + std::to_string(blockedTask.currentPriority));
    }
}
