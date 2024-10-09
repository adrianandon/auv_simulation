#include "PressureSensor.hpp"

class DigitalPressureSensor : public PressureSensor {
public:
    float GetDepth() override;
};
