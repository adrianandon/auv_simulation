#include <iostream>
#include <thread>
#include <chrono>
#include <memory>
#include "PressureSensor.hpp"



// Simulates diving to a specific height above the seafloor
void AUV_Controller::diveToHeightAboveSeafloor(double heightAboveSeafloor) {
    double targetDepth = 50.0 - heightAboveSeafloor; // Seafloor is at 50 meters
    while (pressureSensor->GetDepth() < targetDepth) {
        thrusterControl->GoDown();
        reportStatus("Diving", targetDepth);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    thrusterControl->MaintainDepth();
}

// Simulates ascending to a specific depth
void AUV_Controller::ascendToDepth(double targetDepth) {
    while (pressureSensor->GetDepth() > targetDepth) {
        thrusterControl->GoUp();
        reportStatus("Ascending", targetDepth);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    thrusterControl->MaintainDepth();
}

// Holds the current position for a certain duration (in seconds)
void AUV_Controller::holdPosition(int seconds) {
    for (int i = 0; i < seconds; ++i) {
        thrusterControl->MaintainDepth();
        reportStatus("Holding position", pressureSensor->GetDepth());
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

// Reports the current AUV status to the console
void AUV_Controller::reportStatus(const std::string& operation, double targetDepth) {
    double currentDepth = pressureSensor->GetDepth();
    double heightAboveSeafloor = altimeter->GetHeight();  // Altimeter returns height above seafloor
    std::cout << "[" << operation << "][ " << targetDepth << "m ][ " << currentDepth << "m ][ " 
                << heightAboveSeafloor << "m ]" << std::endl;
}

