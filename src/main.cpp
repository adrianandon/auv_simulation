#include <thread>

#include "WaterDepthSimulation.hpp"
#include "MissionPlan.hpp"
#include "MissionOperation.hpp"

int main() {
    
    SimulationParameters simulationParameters{.descentRate = 1.0f, .ascentRate = 1.0f, 
    .seabedDepth = 50.0f, .simulationUpdateInterval = 1};
    
    MissionPlan missionPlan;
    missionPlan.addMissionOperation(MissionOperation::REACH_HEIGHT, 2.0);
    missionPlan.addMissionOperation(MissionOperation::HOLD_POSITION, 5.0);
    missionPlan.addMissionOperation(MissionOperation::REACH_DEPTH, 10.0);
    missionPlan.addMissionOperation(MissionOperation::REACH_HEIGHT, 15.0);
    missionPlan.addMissionOperation(MissionOperation::REACH_DEPTH, 0.0);

    std::shared_ptr<WaterDepthSimulation> simulation = std::make_shared<WaterDepthSimulation> (simulationParameters, missionPlan);
    std::thread simulationThread(&WaterDepthSimulation::Run, simulation);
    simulationThread.join();
    return 0;

}

