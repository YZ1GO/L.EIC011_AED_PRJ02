#ifndef AED_AEROPORTO_FILE_MAKER_H
#define AED_AEROPORTO_FILE_MAKER_H

#include "ReadData.h"


void convertAirportsToTextFile(const std::vector<Airport>& airports, const std::string& filename);
void convertAirlinesToTextFile(const std::vector<Airline>& airlines, const std::string& filename);
void convertFlightsToTextFile(const std::vector<Flight>& flights, const std::string& filename);

/*
convertAirportsToTextFile(airports, "data_text/Airports.txt");
convertAirlinesToTextFile(airlines, "data_text/Airlines.txt");
convertFlightsToTextFile(flights, "data_text/Flights.txt");
 */


#endif //AED_AEROPORTO_FILE_MAKER_H
