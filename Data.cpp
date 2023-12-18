#include "Data.h"

double Data::getDistance(const Airport& other) const {
    return HarversineDistance(this.latitude, this.longitude, other.getLatitude, other.getLongitude);
}
