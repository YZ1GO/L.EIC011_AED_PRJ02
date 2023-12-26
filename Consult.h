#ifndef AED_AIRPORTS_CONSULT_H
#define AED_AIRPORTS_CONSULT_H

#include "ParseData.h"
#include <map>
#include <unordered_set>
#include <limits>
#include <functional>

class Consult {
private:
    const Graph<Airport>& consultGraph;

    void dfsVisitFlightsPerCity(Vertex<Airport> *v, map<string, int> &res);
    void dfsVisitFlightsPerAirline(Vertex<Airport> *v, map<Airline, int> &res);
    void dfsVisitCityAirports(const string& city, const string& country, Vertex<Airport> *v, vector<Vertex<Airport>*>& res);
    void dfsAvailableDestinations(Vertex<Airport>* v, std::function<void(Vertex<Airport>*)> processDestination);
    int searchNumberOfReachableDestinationsInXStopsFromAirport(Vertex<Airport>* airport, int layOvers, const function<string(Vertex<Airport>*)>& attributeExtractor);
    vector<pair<Airport,int>> topTrafficCapacityAirports();
    void dfsEssentialAirports(Vertex<Airport> *v, stack<string> &s, unordered_set<string> &res, int &i);

public:
    Consult(const Graph<Airport>& dataGraph);

    int searchNumberOfAirports();
    int searchNumberOfAvailableFlights();
    int searchNumberOfAvailableFlightRoutes();

    int searchNumberOfFlightsOutOfAirport(Vertex<Airport>* airport);
    int searchNumberOfFlightsToAirport(Vertex<Airport>* airport);
    int searchNumberOfFlightsOutOfAirportFromDifferentAirlines(Vertex<Airport>* airport);

    map<string, int> searchNumberOfFlightsPerCity();
    map<Airline, int> searchNumberOfFlightsPerAirline();

    int searchNumberOfCountriesFlownToFromAirport(Vertex<Airport>* airport);
    int searchNumberOfCountriesFlownToFromCity(const string& city, const string& country);

    int searchNumberOfAirportsAvailableForAirport(Vertex<Airport>* airport);
    int searchNumberOfCitiesAvailableForAirport(Vertex<Airport>* airport);
    int searchNumberOfCountriesAvailableForAirport(Vertex<Airport>* airport);

    int searchNumberOfReachableAirportsInXStopsFromAirport(Vertex<Airport>* airport, int layOvers);
    int searchNumberOfReachableCitiesInXStopsFromAirport(Vertex<Airport>* airport, int layOvers);
    int searchNumberOfReachableCountriesInXStopsFromAirport(Vertex<Airport>* airport, int layOvers);

    vector<pair<Airport,int>> searchTopKAirportGreatestAirTrafficCapacity(const int& k);

    unordered_set<string> searchEssentialAirports();

    void searchMaxTripAndCorrespondingPairsOfAirports();

    vector<vector<Airport>> searchSmallestPathBetweenAirports(const Airport& source, const Airport& target);
};


#endif //AED_AIRPORTS_CONSULT_H
