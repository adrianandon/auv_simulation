#ifndef THRUSTERCONTROL_HPP
#define THRUSTERCONTROL_HPP

class ThrusterControl {
    public: 
    void GoUp() = 0;
    void GoDown() = 0;
    void MantainDepth() = 0;
};
#endif