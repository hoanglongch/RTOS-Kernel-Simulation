# Real-Time Operating System (RTOS) Simulation

This project is a robust simulation of an RTOS implemented in C++. It demonstrates key real-time operating system components and concepts, including:

- **Interrupt Handling & Context Switching:**  
  Efficient mechanisms for interrupt registration, triggering, and context save/restore.
  
- **Memory Protection & Advanced Memory Management:**  
  Implementation of an MPU driver for ARM-like architectures along with a Virtual Memory Manager supporting virtual memory, paging, and simulated page faults.
  
- **Real-Time Task Scheduler:**  
  A scheduler using a priority queue with support for priority inheritance.
  
- **Custom NUMA-Aware Memory Allocator:**  
  A custom allocator that simulates memory allocation with NUMA node and huge pages support.
  
- **Device Drivers & Hardware Abstraction Layer (HAL):**  
  Integrated device drivers (Timer, UART, Network) wrapped in a HAL for hardware independence.
  
- **Robust Logging System:**  
  A thread-safe logging subsystem with configurable log levels and output options (console and file).
  
- **Unit Testing & CI/CD:**  
  A full unit test suite built using GoogleTest and a sample CI/CD pipeline using GitHub Actions.

## Table of Contents

- [Features](#features)
- [Folder Structure](#folder-structure)
- [Prerequisites](#prerequisites)
- [Build Instructions](#build-instructions)
- [Usage](#usage)
- [Testing](#testing)
- [CI/CD Pipeline](#cicd-pipeline)
- [Future Improvements](#future-improvements)
- [License](#license)

## Features

- **Interrupt Handler:**  
  Registers, unregisters, and triggers interrupts.

- **Context Switcher:**  
  Simulates saving and restoring CPU registers.

- **MPU Driver:**  
  Initializes and configures MPU regions to simulate memory protection.

- **Task Scheduler:**  
  Supports task scheduling with priority inheritance protocol.

- **NUMA-Aware Memory Allocator:**  
  Simulated memory allocator that logs allocation and deallocation events.

- **Virtual Memory Manager:**  
  Supports virtual memory mapping, address translation, and basic page fault handling.

- **Device Drivers:**  
  Simulated Timer, UART, and Network drivers for demonstrating hardware communication.

- **HAL (Hardware Abstraction Layer):**  
  Centralizes access to low-level hardware components and drivers.

- **Logging Subsystem:**  
  Unified logging with multiple log levels and thread-safety.

- **Unit Tests:**  
  Comprehensive test suite using GoogleTest.

- **CI/CD Integration:**  
  GitHub Actions pipeline for automated builds and tests.


## Prerequisites

- **CMake**: Version 3.10 or later.
- **C++ Compiler**: GCC, Clang, or compatible (supporting C++17).
- **GoogleTest**: Installed via `libgtest-dev` package or built from source.
- **Operating System**: Ubuntu or compatible Linux distro  
  *(The CI pipeline is configured for Ubuntu)*

---

## Build Instructions

### 1. Clone the Repository

```bash
git clone https://github.com/your-username/RTOS.git
cd RTOS
```
### 2. Create a Build Directory and Run CMake
```bash
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
```
### 3. Compile the Project
```bash
make -j$(nproc)
```
### 4. Run the Executable
```bash
./RTOS   # or the generated executable name
```

## Usage

The main executable simulates various RTOS components:

- Initializes the Hardware Abstraction Layer (HAL)
- Sets up and triggers interrupts
- Simulates context switching
- Schedules and executes tasks
- Uses a NUMA-aware memory allocator
- Demonstrates virtual memory mapping and translation with the Virtual Memory Manager
- Interacts with simulated device drivers (Timer, UART, Network)

Check rtos.log for runtime logging and debug information.
