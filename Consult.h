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
    int searchNumberOfFlightsOutOfAirportFromDifferentAirlines(const string& airportCode);

    set<string, int> searchNumberOfFlightsPerCity();
    set<string, int> searchNumberOfFlightsPerAirline();
    void dfsVisit(Vertex<Airport> *v, set<string, int> &res) const;
};


#endif //AED_AIRPORTS_CONSULT_H
