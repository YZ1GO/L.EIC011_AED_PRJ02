#include "Data.h"

double Airport::getDistance(const Airport& other) const {
    return HarversineDistance(latitude, longitude, other.getLatitude(), other.getLongitude());
}