#include <thread>

#include "WaterDepthSimulation.hpp"

int main() {
    WaterDepthSimulation simulation;
    std::thread simulationThread(&WaterDepthSimulation::Run, &simulation);
    simulationThread.join();
    return 0;
}

