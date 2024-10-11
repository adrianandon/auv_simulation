#include <thread>
#include <iostream>

#include "WaterDepthSimulation.hpp"
#include "MissionPlan.hpp"
#include "MissionOperation.hpp"

int main() {
    
    SimulationParameters simulationParameters{.descentRate = 1.0f, .ascentRate = 1.0f, 
    .seabedDepth = 50.0f, .simulationUpdateInterval = 1};

    std::cout << "Autonomous Underwater Vehicle (AUV) Simulation v1.0" << std::endl;

    int sensorType;

    while (true) {
        std::cout << "Enter sensor type (1 for Digital Pressure Sensor, 2 for Analogue Pressure Sensor): ";
        std::cin >> sensorType;

        if (std::cin.fail()) {
            std::cin.clear(); // Clear the error state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
            std::cout << "Invalid input! Please enter a number." << std::endl;
            continue;
        }

        if (sensorType == 1) {
            simulationParameters.pressureSensorType = PressureSensorType::DIGITAL;
            break;
        } else if (sensorType == 2) {
            simulationParameters.pressureSensorType = PressureSensorType::ANALOG;
            break;
        } else {
            std::cerr << "Invalid sensor type! Please enter 1 or 2." << std::endl;
        }
    }
    
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

