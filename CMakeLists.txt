cmake_minimum_required(VERSION 3.10)
project(RealtimeOS)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

file(GLOB SRC_FILES "src/*.cpp")

add_executable(RealtimeOS ${SRC_FILES})


# Optionally enable tests if requested
option(BUILD_TESTS "Build tests" ON)
if(BUILD_TESTS)
    add_subdirectory(tests)
endif()
