#ifndef AED_AIRPORTS_PARSEDATA_H
#define AED_AIRPORTS_PARSEDATA_H

#include "Data.h"
#include "Graph.h"
#include <fstream>
#include <sstream>
#include <algorithm>

class ParseData {
private:
    Graph<Airport> airportsGraph;
    Graph<Airline> airlinesGraph;

    std::string airportsCSV, airlinesCSV, flightsCSV;
    void parseAirports();
    void parseAirlines();
    void parseFlights();

public:
    ParseData(const std::string& airportsCSV, const std::string& airlinesCSV, const std::string& flightsCSV);
    Graph<Airport>& getAirportsGraph() { return airportsGraph; }
    Graph<Airline>& getAirlinesGraph() { return airlinesGraph; }
    Airport findAirport(const std::string& airportCode);
};



#endif //AED_AIRPORTS_PARSEDATA_H
