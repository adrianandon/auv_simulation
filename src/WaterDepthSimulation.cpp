#include <chrono>
#include <thread>

#include "WaterDepthSimulation.hpp"
#include "ThrusterControl.hpp"
#include "AltimeterConnection.hpp"
#include "PressureSensorConnection.hpp"
#include "AUV_Controller.hpp"
#include "PressureSensor.hpp"
#include "AnalogPressureSensor.hpp"
#include "DigitalPressureSensor.hpp"
#include <iostream>
#include <memory>

void WaterDepthSimulation:: Run() {
    try
    {
        std::shared_ptr<PressureSensor> pressureSensor = std::make_shared<AnalogPressureSensor>(shared_from_this());
        std::shared_ptr<Altimeter> altimeter = std::make_shared<Altimeter>(shared_from_this());
        std::shared_ptr<ThrusterControl> thrusterControl = shared_from_this();
        AUV_Controller auvController{pressureSensor, altimeter, thrusterControl, missionPlan};
        
        std::cout << "Starting simulation" << std::endl;

        while (auvController.executeMissionPlan())
            std::this_thread::sleep_for(std::chrono::seconds(simulationParameters.simulationUpdateInterval));

        std::cout << "Simulation complete" << std::endl;

    }
    catch(const std::runtime_error& e)
    {
        std::cerr << e.what() << " Simulation stopped." << std::endl;
    }
    
}

void WaterDepthSimulation::GoUp(){
    heightReading = heightReading + simulationParameters.ascentRate * simulationParameters.simulationUpdateInterval;
    if (heightReading > simulationParameters.seabedDepth)
        throw std::runtime_error("The AUV has surfaced!");
    auto depth = simulationParameters.seabedDepth - heightReading;
    digitalPressureSensorReading = static_cast<uint16_t>(depth / 600 * 0xFFFF);
    analogPressureSensorReading = depth / 650 * 12;
}


void WaterDepthSimulation::GoDown(){
    heightReading = heightReading - simulationParameters.descentRate*simulationParameters.simulationUpdateInterval;
    if(heightReading < 0)
        throw std::runtime_error("The AUV has crashed on the seabed!");
    auto depth = simulationParameters.seabedDepth - heightReading;
    digitalPressureSensorReading = static_cast<uint16_t>(depth / 600 * 0xFFFF);
    analogPressureSensorReading = depth/650 * 12;
}

void WaterDepthSimulation::MaintainDepth(){

}

float WaterDepthSimulation::GetHeight(){
    return heightReading;
}

uint16_t WaterDepthSimulation::GetPressure(){
    return digitalPressureSensorReading;
}

float WaterDepthSimulation::getVoltage(){
    return analogPressureSensorReading;
}

