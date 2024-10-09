#include <iostream>
#include <thread>
#include <chrono>
#include <memory>

class AUV_Controller {
public:
    AUV_Controller(std::shared_ptr<PressureSensor> pressureSensor, std::shared_ptr<Altimeter> altimeter, std::shared_ptr<ThrusterControl> thrusterControl)
        : pressureSensor(pressureSensor), altimeter(altimeter), thrusterControl(thrusterControl) {}

    void executeMission() {
        // Step 1: Dive to 2 meters above the sea floor
        diveToHeightAboveSeafloor(2.0);
        holdPosition(5);  // Hold for 5 seconds
        
        // Step 2: Ascend to 10 meters depth
        ascendToDepth(10.0);
        holdPosition(5);  // Hold for 5 seconds
        
        // Step 3: Dive to 15 meters above the sea floor
        diveToHeightAboveSeafloor(15.0);
        holdPosition(5);  // Hold for 5 seconds
        
        // Step 4: Return to surface (0 meters)
        ascendToDepth(0.0);
    }

private:
    std::shared_ptr<PressureSensor> pressureSensor;
    std::shared_ptr<Altimeter> altimeter;
    std::shared_ptr<ThrusterControl> thrusterControl;

    // Simulates diving to a specific height above the seafloor
    void diveToHeightAboveSeafloor(double heightAboveSeafloor) {
        double targetDepth = 50.0 - heightAboveSeafloor; // Seafloor is at 50 meters
        while (pressureSensor->GetDepth() < targetDepth) {
            thrusterControl->GoDown();
            reportStatus("Diving", targetDepth);
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        thrusterControl->MaintainDepth();
    }

    // Simulates ascending to a specific depth
    void ascendToDepth(double targetDepth) {
        while (pressureSensor->GetDepth() > targetDepth) {
            thrusterControl->GoUp();
            reportStatus("Ascending", targetDepth);
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        thrusterControl->MaintainDepth();
    }

    // Holds the current position for a certain duration (in seconds)
    void holdPosition(int seconds) {
        for (int i = 0; i < seconds; ++i) {
            thrusterControl->MaintainDepth();
            reportStatus("Holding position", pressureSensor->GetDepth());
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    // Reports the current AUV status to the console
    void reportStatus(const std::string& operation, double targetDepth) {
        double currentDepth = pressureSensor->GetDepth();
        double heightAboveSeafloor = altimeter->GetVoltage();  // Altimeter returns height above seafloor
        std::cout << "[" << operation << "][ " << targetDepth << "m ][ " << currentDepth << "m ][ " 
                  << heightAboveSeafloor << "m ]" << std::endl;
    }
};
