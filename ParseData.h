#ifndef AED_AIRPORTS_PARSEDATA_H
#define AED_AIRPORTS_PARSEDATA_H

#include "Data.h"
#include "Graph.h"
#include <fstream>
#include <sstream>
#include <algorithm>

class ParseData {
private:
    Graph<AirportAndAirline> dataGraph;

    std::string airportsCSV, airlinesCSV, flightsCSV;
    void parseAirports();
    void parseAirlines();
    void parseFlights();
    void addAirlineToAirport(const Airline& airline);

public:
    ParseData(const std::string& airportsCSV, const std::string& airlinesCSV, const std::string& flightsCSV);
    Graph<AirportAndAirline>& getData() { return dataGraph; }
    Airport* findAirport(const std::string& airportCode);
};



#endif //AED_AIRPORTS_PARSEDATA_H
