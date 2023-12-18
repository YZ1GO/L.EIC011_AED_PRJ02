#ifndef AED_AIRPORTS_PARSEDATA_H
#define AED_AIRPORTS_PARSEDATA_H

#include "Data.h"
#include "Graph.h"
#include <fstream>
#include <sstream>

class ParseData {
public:
    ParseData() {};
    Graph<Airport> ParseAirports(const string& airportsCSV);
    Graph<Airline> ParseAirlines(const string& airlinesCSV);
    void ParseFlights(Graph<Airport>& airportGraph, const string& flightsCSV);
};


#endif //AED_AIRPORTS_PARSEDATA_H
