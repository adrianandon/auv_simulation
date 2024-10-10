#ifndef AUV_CONTROLLER_HPP
#define AUV_CONTROLLER_HPP

#include <memory>
#include <string>

#include "Altimeter.hpp"
#include "PressureSensor.hpp"
#include "ThrusterControl.hpp"

class AUV_Controller {
public:
    AUV_Controller(std::shared_ptr<PressureSensor> pressureSensor, std::shared_ptr<Altimeter> altimeter, std::shared_ptr<ThrusterControl> thrusterControl)
        : pressureSensor(pressureSensor), altimeter(altimeter), thrusterControl(thrusterControl) {}

    void executeMission();

private:
    std::shared_ptr<PressureSensor> pressureSensor;
    std::shared_ptr<Altimeter> altimeter;
    std::shared_ptr<ThrusterControl> thrusterControl;

    // Simulates diving to a specific height above the seafloor
    void diveToHeightAboveSeafloor(double heightAboveSeafloor);

    // Simulates ascending to a specific depth
    void ascendToDepth(double targetDepth);

    // Holds the current position for a certain duration (in seconds)
    void holdPosition(int seconds) ;

    // Reports the current AUV status to the console
    void reportStatus(const std::string& operation, double targetDepth);
};
#endif // AUV_CONTROLLER_HPP