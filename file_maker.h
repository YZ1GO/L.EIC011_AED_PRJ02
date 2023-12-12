#ifndef AED_AEROPORTO_FILE_MAKER_H
#define AED_AEROPORTO_FILE_MAKER_H

#include "ReadData.h"


void convertAirportsToTextFile(const std::vector<Airport>& airports, const std::string& filename);
void convertAirlinesToTextFile(const std::vector<Airline>& airlines, const std::string& filename);
void convertFlightsToTextFile(const std::vector<Flight>& flights, const std::string& filename);



#endif //AED_AEROPORTO_FILE_MAKER_H
