#ifndef TIMER_DRIVER_HPP
#define TIMER_DRIVER_HPP

#include <functional>
#include <thread>

class TimerDriver {
public:
    using TimerCallback = std::function<void()>;

    TimerDriver();
    ~TimerDriver();

    // Initialize the timer hardware simulation.
    bool initialize();

    // Start the timer with the specified interval in milliseconds.
    void start(unsigned int intervalMs, TimerCallback callback);

    // Stop the timer.
    void stop();

    // Return true if the timer is running.
    bool isRunning() const;

private:
    bool running_;
    unsigned int intervalMs_;
    TimerCallback callback_;
    std::thread timerThread_;

    // Internal function to simulate timer ticks.
    void timerLoop();
};

#endif // TIMER_DRIVER_HPP
