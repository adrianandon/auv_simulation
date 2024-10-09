class AnalogPressureSensor : public PressureSensor {
public:
    float voltage;  // Voltage to represent pressure

    uint16_t GetDepth() override {
        // Conversion from voltage to depth in meters.
        return static_cast<uint16_t>((voltage / 12.0) * 650);  // 650m max at 12.0V
    }
};
