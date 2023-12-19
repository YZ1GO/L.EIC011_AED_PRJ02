#ifndef AED_AEROPORTO_DATA_H
#define AED_AEROPORTO_DATA_H

#include "Utilities.h"
#include <iostream>
#include <string>
#include <vector>

struct Coordinates {
    double latitude;
    double longitude;
};

class Airport {
private:
    std::string code;
    std::string name;
    std::string city;
    std::string country;
    Coordinates location;

public:
    Airport() {}
    Airport(const std::string& c, const std::string& n, const std::string& ci, const std::string& co, Coordinates l)
            : code(c), name(n), city(ci), country(co), location(l) {}

    std::string getCode() const { return code; }
    void setCode(const std::string& c) { code = c; }

    std::string getName() const { return name; }
    void setName(const std::string& n) { name = n; }

    std::string getCity() const { return city; }
    void setCity(const std::string& ci) { city = ci; }

    std::string getCountry() const { return country; }
    void setCountry(const std::string& co) { country = co; }

    Coordinates getLocation() const { return location; }

    void setLocation(double latitude, double longitude) {
        location.latitude = latitude;
        location.longitude = longitude;
    }

    double getDistance(const Coordinates& other) const;

    bool operator==(const Airport& other) const { return code == other.code; }
};

class Airline {
private:
    std::string code;
    std::string name;
    std::string callsign;
    std::string country;

public:
    Airline() {}
    Airline(const std::string& c, const std::string& n, const std::string& cs, const std::string& co)
            : code(c), name(n), callsign(cs), country(co) {}

    std::string getCode() const { return code; }
    void setCode(const std::string& c) { code = c; }

    std::string getName() const { return name; }
    void setName(const std::string& n) { name = n; }

    std::string getCallsign() const { return callsign; }
    void setCallsign(const std::string& cs) { callsign = cs; }

    std::string getCountry() const { return country; }
    void setCountry(const std::string& co) { country = co; }

    bool operator<(const Airline& other) const { return code < other.code; }
    bool operator==(const Airline& other) const { return code == other.code; }
};

#endif //AED_AEROPORTO_DATA_H
