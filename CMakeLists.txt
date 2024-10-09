cmake_minimum_required(VERSION 3.10)

# Project name
project(AUVSimulation)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

# Source files
set(SOURCES
    src/AnalogPressureSensor.cpp
    src/PressureSensor.cpp
    src/PressureSensorConnection.cpp
)

# Executable target
add_executable(auv_simulation ${SOURCES})
