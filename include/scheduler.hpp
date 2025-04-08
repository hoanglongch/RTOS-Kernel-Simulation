#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include "task.hpp"
#include <queue>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <thread>

// A simple real-time task scheduler that uses a priority queue.
class Scheduler {
public:
    Scheduler();
    ~Scheduler();

    // Add a new task.
    void addTask(const Task& task);

    // Start the scheduler loop on a separate thread.
    void start();

    // Stop the scheduler.
    void stop();

private:
    // Comparator to order tasks by currentPriority (higher value means higher priority).
    struct TaskComparator {
        bool operator()(const Task& a, const Task& b) {
            // If priorities are equal, order by task id.
            if (a.currentPriority == b.currentPriority) {
                return a.id > b.id;
            }
            return a.currentPriority < b.currentPriority;
        }
    };

    std::priority_queue<Task, std::vector<Task>, TaskComparator> taskQueue_;
    std::mutex queueMutex_;
    std::condition_variable cv_;
    std::atomic<bool> running_;
    std::thread schedulerThread_;

    // Main loop running scheduled tasks.
    void schedulerLoop();

    // Simulate applying priority inheritance for blocked tasks.
    void applyPriorityInheritance(Task& blockedTask, int blockingTaskPriority);
};

#endif // SCHEDULER_HPP
