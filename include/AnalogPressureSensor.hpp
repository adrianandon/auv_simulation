#include "PressureSensor.hpp"

class AnalogPressureSensor : public PressureSensor {
public:
    float GetDepth() override;
};
