#ifndef PRESSURESENSORCONNECTION_HPP
#define PRESSURESENSORCONNECTION_HPP

#include <cstdint>

class PressureSensorConnection 
{
    public: 
    virtual ~PressureSensorConnection() = default;
    virtual uint16_t GetPressure() = 0;  
    virtual float getVoltage() = 0; 
};
#endif