#ifndef AED_AIRPORTS_PARSEDATA_H
#define AED_AIRPORTS_PARSEDATA_H

#include "Data.h"
#include "Graph.h"
#include <fstream>
#include <sstream>

class ParseData {
private:
    string airportsCSV, airlinesCSV, flightsCSV;
    Graph<AirportAndAirline> dataGraph;
    void parseAirports();
    void parseAirlines();
    void parseFlights();
    void addAirlineToAirport(Airline airline);
public:
    ParseData(const string& airportsCSV, const string& airlinesCSV, const string& flightsCSV);
    Graph<AirportAndAirline> getData() { return this.dataGraph; }
};


#endif //AED_AIRPORTS_PARSEDATA_H
