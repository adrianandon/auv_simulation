#include <thread>

WaterDepthSimulation simulation;
std::thread simulationThread(&WaterDepthSimulation::Run, &simulation);
