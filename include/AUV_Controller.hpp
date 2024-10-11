#ifndef AUV_CONTROLLER_HPP
#define AUV_CONTROLLER_HPP

#include <memory>
#include <string>

#include "Altimeter.hpp"
#include "PressureSensor.hpp"
#include "ThrusterControl.hpp"
#include "MissionPlan.hpp"


class AUV_Controller {
public:
    AUV_Controller(std::shared_ptr<PressureSensor> pressureSensor, std::shared_ptr<Altimeter> altimeter, 
    std::shared_ptr<ThrusterControl> thrusterControl, MissionPlan& missionPlan)
        : pressureSensor(pressureSensor), altimeter(altimeter), thrusterControl(thrusterControl),
        missionPlan(missionPlan) {}

    bool executeMissionPlan();

private:
    std::shared_ptr<PressureSensor> pressureSensor;
    std::shared_ptr<Altimeter> altimeter;
    std::shared_ptr<ThrusterControl> thrusterControl;
    std::shared_ptr<std::pair<MissionOperation, double>> currentOperation;
    MissionPlan missionPlan;

    bool reachTarget(double targetValue, double currentValue, bool isDepth);    
    bool reachHeightAboveSeafloor(double targetHeight);
    bool reachDepthBelowSurface(double targetDepth);
    void holdPosition(int seconds);
    void reportStatus(const std::string& operation, double targetDepth);
};
#endif // AUV_CONTROLLER_HPP