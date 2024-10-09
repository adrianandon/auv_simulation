#include "DigitalPressureSensor.hpp"
#include <cstdint>


float DigitalPressureSensor::GetDepth()  {
    // Conversion from voltage to depth in meters.
    auto pressure = connection->GetPressure();
    return static_cast<float>(pressure) / 0xFFFF * 600;  // 600m max at 0xFFFF
}