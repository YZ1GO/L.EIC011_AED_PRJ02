#ifndef AED_AIRPORTS_OUTPUTDATA_H
#define AED_AIRPORTS_OUTPUTDATA_H

#include "ParseData.h"

//void convertAirportsToTextFile(const Graph<Airport>& airportGraph, const std::string& filename);
//void convertAirlinesToTextFile(const Graph<Airline>& airlineGraph, const std::string& filename);
void convertDataGraphToTextFile(const Graph<Airport>& airportGraph, const std::string& filename);

#endif //AED_AIRPORTS_OUTPUTDATA_H
