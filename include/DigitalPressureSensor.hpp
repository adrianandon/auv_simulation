#ifndef DIGITALPRESSURESENSOR_HPP
#define DIGITALPRESSURESENSOR_HPP

#include "PressureSensor.hpp"

class DigitalPressureSensor : public PressureSensor {
public:
    DigitalPressureSensor(std::shared_ptr<PressureSensorConnection> connection) : PressureSensor(connection) {}
    float GetDepth() override;
};
#endif // DIGITALPRESSURESENSOR_HPP