#ifndef ANALOGPRESSURESENSOR_HPP
#define ANALOGPRESSURESENSOR_HPP

#include "PressureSensor.hpp"

class AnalogPressureSensor : public PressureSensor {
public:
    float GetDepth() override;
};
#endif // ANALOGPRESSURESENSOR_HPP
