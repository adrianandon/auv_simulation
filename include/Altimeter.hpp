#ifndef ALTIMETER_HPP
#define ALTIMETER_HPP

#include "AltimeterConnection.hpp"
#include <memory>

class Altimeter {
public:
    Altimeter(std::shared_ptr<AltimeterConnection> connection) : connection(connection) {}
    float GetHeight();
protected:
    std::shared_ptr<AltimeterConnection> connection;
};
#endif // ALTIMETER_HPP