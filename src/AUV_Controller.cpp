#include <iostream>
#include <thread>
#include <chrono>
#include <memory>
#include "PressureSensor.hpp"
#include "AUV_Controller.hpp"


bool AUV_Controller::executeMissionPlan() {
    
    if(currentOperation == nullptr)
        if(missionPlan.isEmpty())
            return false;
        else
            currentOperation = std::make_shared<std::pair<MissionOperation, double>>(missionPlan.getNextMissionOperation());
    
    switch (currentOperation->first)
    {
        case MissionOperation::REACH_HEIGHT:
            if(reachHeightAboveSeafloor(currentOperation->second))
                currentOperation = nullptr;
            break;
        case MissionOperation::REACH_DEPTH:
            if(reachDepthBelowSurface(currentOperation->second))
                currentOperation = nullptr;
            break;
        case MissionOperation::HOLD_POSITION:
            holdPosition(currentOperation->second);
            currentOperation = nullptr;
            break;

    };
    return true;
}

bool AUV_Controller::reachHeightAboveSeafloor(double targetHeight) {
    double currentHeight = altimeter->GetHeight();
    if (currentHeight < targetHeight) {
        thrusterControl->GoUp();
        reportStatus("Ascending ", targetHeight);
    } else if (currentHeight > targetHeight) {
        thrusterControl->GoDown();
        reportStatus("Diving ", targetHeight);
    } else {
        return true; // Target height reached
    }
    return false; // Target height not reached yet
}

bool AUV_Controller::reachDepthBelowSurface(double targetDepth) {
    double currentDepth = pressureSensor->GetDepth();
    if (currentDepth < targetDepth) {
        thrusterControl->GoDown();
        reportStatus("Diving ", targetDepth);

    } else if (currentDepth > targetDepth) {
        reportStatus("Ascending ", targetDepth);

        thrusterControl->GoUp();
    } else {
        return true; // Target depth reached
    }
    return false; // Target depth not reached yet
}


void AUV_Controller::holdPosition(int seconds) {
    for (int i = 0; i < seconds; ++i) {
        thrusterControl->MaintainDepth();
        reportStatus("Holding position", pressureSensor->GetDepth());
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void AUV_Controller::reportStatus(const std::string& operation, double targetDepth) {
    double currentDepth = pressureSensor->GetDepth();
    double heightAboveSeafloor = altimeter->GetHeight();
    std::cout << "[" << operation << "][ " << targetDepth << "m ][ " << currentDepth << "m ][ " 
                << heightAboveSeafloor << "m ]" << std::endl;
}
