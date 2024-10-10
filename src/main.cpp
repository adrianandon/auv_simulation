#include <thread>

#include "WaterDepthSimulation.hpp"

int main() {
    
    SimulationParameters simulationParameters{.descentRate = 1.0f, .ascentRate = 1.0f, 
    .seabedDepth = 50.0f, .simulationUpdateInterval = 1.0f};
    std::make_shared<MissionPlan> missionPlan;
    std::make_shared<WaterDepthSimulation> simulation{simulationParameters};
    std::thread simulationThread(&WaterDepthSimulation::Run, simulation);
    simulationThread.join();
    return 0;

}

