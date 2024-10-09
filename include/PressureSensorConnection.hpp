#include <cstdint>

class PressureSensorConnection 
{
    public: 
    virtual uint16_t GetPressure() = 0;  
    virtual float getVoltage() = 0; 
};