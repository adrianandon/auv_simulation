#include <chrono>
#include <thread>

#include "WaterDepthSimulation.hpp"
#include "ThrusterControl.hpp"
#include "AltimeterConnection.hpp"
#include "PressureSensorConnection.hpp"
#include "AUV_Controller.hpp"
#include "PressureSensor.hpp"

void WaterDepthSimulation:: Run() {
    try
    {
        std::shared_ptr<PressureSensor> pressureSensor = std::make_shared<PressureSensor>{this};
        std::shared_ptr<Altimeter> altimeter = std::make_shared<Altimeter>{this};
        AUV_Controller auvController{pressureSensor, altimeter, this};
        auvController.executeMission();
        // while (simulationRunning) {
        //     // Simulate changes in depth and communicate with the AUV controller.
        //     std::this_thread::sleep_for(std::chrono::seconds(simulationParameters.simulationUpdateInterval));
        // }
    }
    catch(const std::runtime_error& e)
    {
        std::cerr << e.what() << " Simulation stopped." << std::endl;
    }
    
}

void WaterDepthSimulation::GoUp(){

}


void WaterDepthSimulation::GoDown(){
    heightReading = heightReading - simulationParameters.descentRate*simulationParameters.simulationUpdateInterval;
    if(heightReading < 0)
        throw std::runtime_error("The AUV has crashed on the seabed!");
    auto depth = simulationParameters.seabedDepth - heightReading;
    digitalPressureSensorReading = static_cast<uint16_t>(depth / 600 * 0xFFFF);
    analogPressureSensorReading = depth/650 * 12;
}

void WaterDepthSimulation::MantainDepth(){

}

float WaterDepthSimulation::getHeight(){
    return heightReading;
}

uint16_t WaterDepthSimulation::GetPressure(){
    return digitalPressureSensorReading;
}

float WaterDepthSimulation::getVoltage(){
    return analogPressureSensorReading;
}

