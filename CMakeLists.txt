cmake_minimum_required(VERSION 3.10)

# Project name
project(AUVSimulation)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

# Source files
set(SOURCES
    src/Altimeter.cpp
    src/AnalogPressureSensor.cpp
    src/AUV_Controller.cpp
    src/DigitalPressureSensor.cpp
    src/WaterDepthSimulation.cpp
    src/MissionPlan.cpp
    src/main.cpp
)

# Executable target
add_executable(auv_simulation ${SOURCES})
