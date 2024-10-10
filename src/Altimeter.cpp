#include "Altimeter.hpp"

float Altimeter::GetHeight() {
    // Return height above seafloor in meters.
    return connection->GetHeight();
}
