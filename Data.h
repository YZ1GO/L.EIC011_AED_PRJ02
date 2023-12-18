#ifndef AED_AEROPORTO_DATA_H
#define AED_AEROPORTO_DATA_H

#include "Utilities.h"
#include <iostream>
#include <string>

class Airport {
public:
    std::string code;
    std::string name;
    std::string city;
    std::string country;
    double latitude;
    double longitude;

    Airport() {}
    Airport(std::string& c, std::string& n, std::string& ci, std::string& co, double lat, double lon)
            : code(c), name(n), city(ci), country(co), latitude(lat), longitude(lon) {}
    bool operator==(const Airport& other) const { return code == other.code; }
};

class Airline {
public:
    std::string code;
    std::string name;
    std::string callsign;
    std::string country;

    Airline() {}
    Airline(const std::string& c, const std::string& n, const std::string& cs, const std::string& co)
            : code(c), name(n), callsign(cs), country(co) {}
    bool operator==(const Airline& other) const { return code == other.code; }
};

class Flight {
public:
    std::string source;
    std::string target;
    std::string airlineCode;

    Flight() {}
    Flight(const std::string& src, const std::string& tgt, const std::string& ac)
            : source(src), target(tgt), airlineCode(ac) {}
};

#endif //AED_AEROPORTO_DATA_H
