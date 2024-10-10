#ifndef DIGITALPRESSURESENSOR_HPP
#define DIGITALPRESSURESENSOR_HPP

#include "PressureSensor.hpp"

class DigitalPressureSensor : public PressureSensor {
public:
    float GetDepth() override;
};
#endif // DIGITALPRESSURESENSOR_HPP