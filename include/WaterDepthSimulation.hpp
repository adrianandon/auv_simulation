#ifndef WATER_DEPTH_SIMULATION_HPP
#define WATER_DEPTH_SIMULATION_HPP

class ThrusterControl;
class AltimeterConnection;
class PressureSensorConnection;
struct SimulationParameters;

class WaterDepthSimulation : public ThrusterControl, public AltimeterConnection, public PressureSensorConnection
{
public:
    WaterDepthSimulation(SimulationParameters simulationParameters){
        this->simulationParameters = simulationParameters;
        heightReading = simulationParameters.seabedDepth;
    }
    
    void Run(); 

    void GoUp() override;
    void GoDown() override;
    void MantainDepth() override;

    float getHeight() override;

    uint16_t GetPressure() override;
    float getVoltage() override;
private:
    uint16_t digitalPressureSensorReading = 0;
    float analogPressureSensorReading = 0.0f;
    float heightReading;
    bool simulationRunning = true;
    SimulationParameters simulationParameters;
};

struct SimulationParameters
{
    float descentRate = 1.0f;//Descent rate in meters per second
    float ascentRate = 1.0f;//Ascent rate in meters per second
    float seabedDepth = 50.0f;//Depth of the seabed in meters
    int simulationUpdateInterval = 1;//Interval in seconds between simulation updates
};
#endif