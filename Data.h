#ifndef AED_AEROPORTO_DATA_H
#define AED_AEROPORTO_DATA_H

#include "Utilities.h"
#include <iostream>
#include <string>
#include <vector>

struct AirportAndAirline {
    Airport airport,
    std::vector<Airline> airlines
};

class Airport {
private:
    std::string code;
    std::string name;
    std::string city;
    std::string country;
    double latitude;
    double longitude;

public:
    Airport() {}
    Airport(const std::string& c, const std::string& n, const std::string& ci, const std::string& co, double lat, double lon)
            : code(c), name(n), city(ci), country(co), latitude(lat), longitude(lon) {}

    std::string getCode() const { return code; }
    void setCode(const std::string& c) { code = c; }

    std::string getName() const { return name; }
    void setName(const std::string& n) { name = n; }

    std::string getCity() const { return city; }
    void setCity(const std::string& ci) { city = ci; }

    std::string getCountry() const { return country; }
    void setCountry(const std::string& co) { country = co; }

    double getLatitude() const { return latitude; }
    void setLatitude(double lat) { latitude = lat; }

    double getLongitude() const { return longitude; }
    void setLongitude(double lon) { longitude = lon; }

    double getDistance(const Airport& other) const;

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

    bool operator==(const Airline& other) const { return code == other.code; }
};

/*
class Flight {
private:
    std::string source;
    std::string target;
    std::string airlineCode;

public:
    Flight() {}
    Flight(const std::string& src, const std::string& tgt, const std::string& ac)
            : source(src), target(tgt), airlineCode(ac) {}

    std::string getSource() const { return source; }
    void setSource(const std::string& src) { source = src; }

    std::string getTarget() const { return target; }
    void setTarget(const std::string& tgt) { target = tgt; }

    std::string getAirlineCode() const { return airlineCode; }
    void setAirlineCode(const std::string& ac) { airlineCode = ac; }
};*/

#endif //AED_AEROPORTO_DATA_H
