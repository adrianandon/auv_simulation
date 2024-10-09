class WaterDepthSimulation {
public:
    void Run() {
        while (simulationRunning) {
            // Simulate changes in depth and communicate with the AUV controller.
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
private:
    bool simulationRunning = true;
};
