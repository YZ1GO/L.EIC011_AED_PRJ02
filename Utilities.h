#ifndef AED_AEROPORTO_UTILITIES_H
#define AED_AEROPORTO_UTILITIES_H

#include <string>
#include <algorithm>
#include <cmath>

std::string TrimString(const std::string& toTrim);

double ToRadians(double degrees);

double HarversineDistance(double lat1, double lon1, double lat2, double lon2);

std::string ToLower(const std::string& input);

std::string RemoveSpaces(const std::string& str);

#endif //AED_AEROPORTO_UTILITIES_H
