class Altimeter {
public:
    float GetHeightAboveSeafloor() {
        // Return height above seafloor in meters.
        return 50.0 - GetDepth();  // Assuming max depth is 50 meters.
    }
};
