#include <chrono>
#include <thread>

#include "WaterDepthSimulation.hpp"


void WaterDepthSimulation:: Run() {
    while (simulationRunning) {
        // Simulate changes in depth and communicate with the AUV controller.
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

