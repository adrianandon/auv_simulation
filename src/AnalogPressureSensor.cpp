#include "AnalogPressureSensor.hpp"


float AnalogPressureSensor::GetDepth()  {
    // Conversion from voltage to depth in meters.
    auto voltage = connection->getVoltage();
    return voltage / 12.0 * 650;  // 650m max at 12.0V
}
