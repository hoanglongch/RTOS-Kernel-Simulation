#include "timer_driver.hpp"
#include "logger.hpp"
#include <chrono>
#include <thread>

TimerDriver::TimerDriver() : running_(false), intervalMs_(0) {}

TimerDriver::~TimerDriver() {
    stop();
}

bool TimerDriver::initialize() {
    Logger::getInstance().info("TimerDriver: Initialized.");
    return true;
}

void TimerDriver::start(unsigned int intervalMs, TimerCallback callback) {
    if (running_)
        return;
    running_ = true;
    intervalMs_ = intervalMs;
    callback_ = callback;
    timerThread_ = std::thread(&TimerDriver::timerLoop, this);
    Logger::getInstance().info("TimerDriver: Timer started with interval " + std::to_string(intervalMs) + " ms.");
}

void TimerDriver::stop() {
    if (running_) {
        running_ = false;
        if (timerThread_.joinable())
            timerThread_.join();
        Logger::getInstance().info("TimerDriver: Timer stopped.");
    }
}

bool TimerDriver::isRunning() const {
    return running_;
}

void TimerDriver::timerLoop() {
    while (running_) {
        std::this_thread::sleep_for(std::chrono::milliseconds(intervalMs_));
        if (callback_) {
            callback_();
        }
    }
}
