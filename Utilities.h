#ifndef AED_AEROPORTO_UTILITIES_H
#define AED_AEROPORTO_UTILITIES_H

#include <string>
#include <algorithm>
#include <cmath>
#include <sstream>

std::string TrimString(const std::string& toTrim);

double ToRadians(double degrees);

double HarversineDistance(double lat1, double lon1, double lat2, double lon2);

std::string ToLower(const std::string& input);

std::string RemoveSpaces(const std::string& str);

template <typename T>
std::string makeBold(const T& value) {
    std::ostringstream oss;
    oss << "\033[1m" << value << "\033[0m";
    return oss.str();
};

#endif //AED_AEROPORTO_UTILITIES_H
