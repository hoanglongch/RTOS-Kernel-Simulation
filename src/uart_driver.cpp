#include "uart_driver.hpp"
#include "logger.hpp"

UARTDriver::UARTDriver() {}

UARTDriver::~UARTDriver() {}

bool UARTDriver::initialize() {
    Logger::getInstance().info("UARTDriver: Initialized.");
    return true;
}

void UARTDriver::write(const std::string& data) {
    // Simulate UART transmission by logging the output.
    Logger::getInstance().info("UARTDriver: Sending data: " + data);
}

std::string UARTDriver::read() {
    // Simulate reading data from UART.
    std::string simulatedData = "UARTDriver: Received simulated data.";
    Logger::getInstance().info(simulatedData);
    return simulatedData;
}
