#include "Data.h"

double Airport::getDistance(const Coordinates& other) const {
    return HarversineDistance(location.latitude, location.longitude, other.latitude, other.longitude);
}