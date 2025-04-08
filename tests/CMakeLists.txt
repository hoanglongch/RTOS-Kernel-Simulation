cmake_minimum_required(VERSION 3.10)
project(RTOS_UnitTests)

enable_testing()

# Locate GoogleTest
find_package(GTest REQUIRED)

# Include RTOS headers directory and GoogleTest headers.
include_directories(${GTEST_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/include)

# Collect all test source files.
file(GLOB TEST_SOURCES *.cpp)

# Create test executable.
add_executable(RTOS_UnitTests ${TEST_SOURCES})

# Link GoogleTest libraries and pthread.
target_link_libraries(RTOS_UnitTests ${GTEST_LIBRARIES} pthread)

# Enable test runner.
add_test(NAME RTOS_UnitTests COMMAND RTOS_UnitTests)
