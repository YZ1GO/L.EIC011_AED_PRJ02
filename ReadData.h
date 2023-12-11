#ifndef AED_AEROPORTO_READDATA_H
#define AED_AEROPORTO_READDATA_H

#include "Data.h"
#include <fstream>
#include <sstream>

using namespace std;

class ReadData {
public:
    ReadData();
    vector<Airport> ReadAirports(const string& airportsCSV);
    vector<Airline> ReadAirlines(const string& airlinesCSV);
    vector<Flight> ReadFlights(const string& flightsCSV);
};


#endif //AED_AEROPORTO_READDATA_H
