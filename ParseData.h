#ifndef AED_AIRPORTS_PARSEDATA_H
#define AED_AIRPORTS_PARSEDATA_H

#include "Data.h"
#include "Graph.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <set>

class ParseData {
private:
    Graph<Airport> dataGraph;
    std::set<Airline> airlinesInfo;

    std::string airportsCSV, airlinesCSV, flightsCSV;
    void parseAirports();
    void parseFlights();
    void parseAirlines();

public:
    ParseData(const std::string& airportsCSV, const std::string& airlinesCSV, const std::string& flightsCSV);
    Graph<Airport>& getDataGraph() { return dataGraph; }
    Airport findAirport(const std::string& airportCode);
    Airline getAirline(const std::string& airlineCode);
};



#endif //AED_AIRPORTS_PARSEDATA_H
