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
    void parseAirlines();
    void parseAirports();
    void parseFlights();

public:
    ParseData(const std::string& airportsCSV, const std::string& airlinesCSV, const std::string& flightsCSV);
    const Graph<Airport>& getDataGraph() const { return dataGraph; }
    Airline getAirline(const std::string& airlineCode);
    void setupIndegreeOutDegree(); //this function should be in Graph class
};



#endif //AED_AIRPORTS_PARSEDATA_H
