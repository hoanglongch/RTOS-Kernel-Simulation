#ifndef TASK_HPP
#define TASK_HPP

#include <functional>
#include <cstdint>
#include <string>

// Structure representing a scheduled task.
struct Task {
    int id;
    std::string name;
    int basePriority;
    int currentPriority;
    std::function<void()> taskFunction;
};

#endif // TASK_HPP
