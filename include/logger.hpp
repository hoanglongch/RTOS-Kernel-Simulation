#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <mutex>
#include <fstream>
#include <sstream>
#include <chrono>
#include <iostream>
#include <iomanip>

// Define log levels
enum class LogLevel {
    DEBUG = 0,
    INFO,
    WARNING,
    ERROR,
};

class Logger {
public:
    // Get the singleton instance of the logger.
    static Logger& getInstance();

    // Set the minimum log level; only messages at or above this level will be logged.
    void setLogLevel(LogLevel level);

    // Optionally enable file logging. Returns true if file logging is successfully enabled.
    bool setLogFile(const std::string& filename);

    // Log a message with the given log level.
    void log(LogLevel level, const std::string& message);

    // Convenience methods for logging at specific levels.
    void debug(const std::string& message);
    void info(const std::string& message);
    void warn(const std::string& message);
    void error(const std::string& message);

private:
    // Private constructor/destructor for singleton.
    Logger();
    ~Logger();

    // Deleted copy constructor and assignment operator to ensure a single instance.
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    // Helper functions to format a timestamp and convert log levels to strings.
    std::string getTimestamp() const;
    std::string levelToString(LogLevel level) const;

    LogLevel currentLogLevel_;
    std::mutex logMutex_;
    std::ofstream logFile_;
    bool isFileLoggingEnabled_;
};

#endif // LOGGER_HPP
