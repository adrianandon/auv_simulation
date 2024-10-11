#include <iostream>
#include <thread>
#include <chrono>
#include <memory>
#include <iomanip>

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

bool AUV_Controller::reachTarget(double targetValue, double currentValue, bool isDepth) {
    if (currentValue < targetValue) {
        if (isDepth) {
            reportStatus("Descending ", targetValue);
            thrusterControl->GoDown();
        } else {
            reportStatus("Ascending ", targetValue);
            thrusterControl->GoUp();
        }
    } else if (currentValue > targetValue) {
        if (isDepth) {
            reportStatus("Ascending ", targetValue);
            thrusterControl->GoUp();
        } else {
            reportStatus("Descending ", targetValue);
            thrusterControl->GoDown();
        }
    } else {
        return true; // Target value reached
    }
    return false; // Target value not reached yet
}

bool AUV_Controller::reachHeightAboveSeafloor(double targetHeight) {
    double currentHeight = altimeter->GetHeight();
    return reachTarget(targetHeight, currentHeight, false);
}

bool AUV_Controller::reachDepthBelowSurface(double targetDepth) {
     double currentDepth = pressureSensor->GetDepth();
     return reachTarget(targetDepth, currentDepth, true);
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

    std::cout << std::fixed << std::setprecision(1);
    std::cout << "[" << operation << "][ " << targetDepth << "m ][ " << currentDepth << "m ][ " 
                << heightAboveSeafloor << "m ]" << std::endl;
}
