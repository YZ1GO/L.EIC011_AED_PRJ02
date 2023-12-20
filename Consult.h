#ifndef AED_AIRPORTS_CONSULT_H
#define AED_AIRPORTS_CONSULT_H

#include "ParseData.h"
#include <map>

class Consult {
private:
    const Graph<Airport>& consultGraph;
public:
    Consult(const Graph<Airport>& dataGraph);

    int searchNumberOfAirports();
    int searchNumberOfAvailableFlightRoutes();

    int searchNumberOfFlightsOutOfAirport(const Airport& airport);
    int searchNumberOfFlightsToAirport(const Airport& airport);
    int searchNumberOfFlightsOutOfAirportFromDifferentAirlines(const Airport& airport);

    map<string, int> searchNumberOfFlightsPerCity();
    void dfsVisitFlightsPerCity(Vertex<Airport> *v, map<string, int> &res);
    map<string, int> searchNumberOfFlightsPerAirline();
    void dfsVisitFlightsPerAirline(Vertex<Airport> *v, map<string, int> &res);

    int searchNumberOfCountriesFlownToFromAirport(const Airport& airport);
    int searchNumberOfCountriesFlownToFromCity(const string& city, const string& country);
    void dfsVisitCityAirports(const string& city, const string& country, Vertex<Airport> *v, vector<Vertex<Airport>*>& res);

    //int searchNumberOfAirportsAvailableForAirport(const Airport& airport);
    //int searchNumberOfCitiesAvailableForAirport(const Airport& airport);
    //int searchNumberOfCountriesAvailableForAirport(const Airport& airport);

    int searchNumberOfReachableAirportsInXStopsFromAirport(const Airport& airport, int layOvers);
};


#endif //AED_AIRPORTS_CONSULT_H
