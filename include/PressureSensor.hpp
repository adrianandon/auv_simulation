#ifndef PRESSURE_SENSOR_HPP

#define PRESSURE_SENSOR_HPP
#include "PressureSensorConnection.hpp"
#include <memory>

class PressureSensor {
public:
    PressureSensor(std::shared_ptr<PressureSensorConnection> connection) : connection(connection) {}
    virtual float GetDepth() = 0;  // Returns depth in meters.
protected:
    std::shared_ptr<PressureSensorConnection> connection;
};
#endif // PRESSURE_SENSOR_HPP