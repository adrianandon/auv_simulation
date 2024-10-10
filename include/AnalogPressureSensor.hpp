#ifndef ANALOGPRESSURESENSOR_HPP
#define ANALOGPRESSURESENSOR_HPP

#include "PressureSensor.hpp"

class AnalogPressureSensor : public PressureSensor {
public:
    AnalogPressureSensor(std::shared_ptr<PressureSensorConnection> connection) : PressureSensor(connection) {}
    float GetDepth() override;
};
#endif // ANALOGPRESSURESENSOR_HPP
