#include "logger.hpp"

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

Logger::Logger() 
    : currentLogLevel_(LogLevel::DEBUG), isFileLoggingEnabled_(false) {}

Logger::~Logger() {
    if (logFile_.is_open()) {
        logFile_.close();
    }
}

void Logger::setLogLevel(LogLevel level) {
    std::lock_guard<std::mutex> lock(logMutex_);
    currentLogLevel_ = level;
}

bool Logger::setLogFile(const std::string& filename) {
    std::lock_guard<std::mutex> lock(logMutex_);
    logFile_.open(filename, std::ios_base::out | std::ios_base::app);
    if (logFile_.is_open()) {
        isFileLoggingEnabled_ = true;
        return true;
    }
    return false;
}

void Logger::log(LogLevel level, const std::string& message) {
    // Only log messages that meet the current log level threshold.
    if (static_cast<int>(level) < static_cast<int>(currentLogLevel_))
        return;

    // Ensure thread safety for the logging output.
    std::lock_guard<std::mutex> lock(logMutex_);

    // Compose the formatted log message.
    std::string logMessage = getTimestamp() + " [" + levelToString(level) + "] " + message;

    // Output the log message to the console.
    std::cout << logMessage << std::endl;

    // If file logging is enabled, write the message to the file.
    if (isFileLoggingEnabled_ && logFile_.is_open()) {
        logFile_ << logMessage << std::endl;
        logFile_.flush();
    }
}

void Logger::debug(const std::string& message) {
    log(LogLevel::DEBUG, message);
}

void Logger::info(const std::string& message) {
    log(LogLevel::INFO, message);
}

void Logger::warn(const std::string& message) {
    log(LogLevel::WARNING, message);
}

void Logger::error(const std::string& message) {
    log(LogLevel::ERROR, message);
}

std::string Logger::getTimestamp() const {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    // Format the timestamp as "YYYY-MM-DD HH:MM:SS".
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
    return ss.str();
}

std::string Logger::levelToString(LogLevel level) const {
    switch (level) {
        case LogLevel::DEBUG:   return "DEBUG";
        case LogLevel::INFO:    return "INFO";
        case LogLevel::WARNING: return "WARNING";
        case LogLevel::ERROR:   return "ERROR";
        default:                return "UNKNOWN";
    }
}
