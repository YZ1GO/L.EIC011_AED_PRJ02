#ifndef AED_AIRPORTS_CONSULT_H
#define AED_AIRPORTS_CONSULT_H

#include "ParseData.h"

class Consult {
private:
    const Graph<Airport>& consultGraph;
public:
    Consult(const Graph<Airport>& dataGraph);

    int searchNumberOfAirports();
    int searchNumberOfAvailableFlightRoutes();

    int searchNumberOfFlightsOutOfAirport(const string& airportCode);

};


#endif //AED_AIRPORTS_CONSULT_H
