#ifndef WATER_DEPTH_SIMULATION_HPP
#define WATER_DEPTH_SIMULATION_HPP

#include <memory>

#include "ThrusterControl.hpp"
#include "AltimeterConnection.hpp"
#include "PressureSensorConnection.hpp"
#include "MissionPlan.hpp"


struct SimulationParameters
{
    float descentRate = 1.0f;//Descent rate in meters per second
    float ascentRate = 1.0f;//Ascent rate in meters per second
    float seabedDepth = 50.0f;//Depth of the seabed in meters
    int simulationUpdateInterval = 1;//Interval in seconds between simulation updates
};

class WaterDepthSimulation : public ThrusterControl, public AltimeterConnection, 
                                public PressureSensorConnection, public std::enable_shared_from_this<WaterDepthSimulation>
{
public:
    WaterDepthSimulation(const SimulationParameters& simulationParameters, MissionPlan& missionPlan){
        this->simulationParameters = simulationParameters;
        heightReading = simulationParameters.seabedDepth;
        this->missionPlan = missionPlan;
    }
    
    void Run(); 

    void GoUp() override;
    void GoDown() override;
    void MaintainDepth() override;

    float GetHeight() override;

    uint16_t GetPressure() override;
    float getVoltage() override;
private:
    uint16_t digitalPressureSensorReading = 0;
    float analogPressureSensorReading = 0.0f;
    float heightReading;
    bool simulationRunning = true;
    SimulationParameters simulationParameters;
    MissionPlan missionPlan;
};


#endif