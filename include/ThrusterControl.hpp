#ifndef THRUSTERCONTROL_HPP
#define THRUSTERCONTROL_HPP

class ThrusterControl {
    public: 
    virtual ~ThrusterControl() = default;
    virtual void GoUp() = 0;
    virtual void GoDown() = 0;
    virtual void MaintainDepth() = 0;
};
#endif