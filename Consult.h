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
    void dfsVisitFlightsPerAirline(Vertex<Airport> *v, map<string, int> &res);
    void dfsVisitCityAirports(const string& city, const string& country, Vertex<Airport> *v, vector<Vertex<Airport>*>& res);
    void dfsAvailableDestinations(Vertex<Airport>* v, std::function<void(Vertex<Airport>*)> processDestination);
    int searchNumberOfReachableDestinationsInXStopsFromAirport(const Airport& airport, int layOvers, const function<string(const Airport&)>& attributeExtractor);
    vector<pair<Airport,int>> topTrafficCapacityAirports();
    void dfs_articulations(Vertex<Airport> *v, stack<string> &s, unordered_set<string> &l, int &i);

public:
    Consult(const Graph<Airport>& dataGraph);

    int searchNumberOfAirports();
    int searchNumberOfAvailableFlights();
    int searchNumberOfAvailableFlightRoutes();

    int searchNumberOfFlightsOutOfAirport(const Airport& airport);
    int searchNumberOfFlightsToAirport(const Airport& airport);
    int searchNumberOfFlightsOutOfAirportFromDifferentAirlines(const Airport& airport);

    map<string, int> searchNumberOfFlightsPerCity();
    map<string, int> searchNumberOfFlightsPerAirline();

    int searchNumberOfCountriesFlownToFromAirport(const Airport& airport);
    int searchNumberOfCountriesFlownToFromCity(const string& city, const string& country);

    int searchNumberOfAirportsAvailableForAirport(const Airport& airport);
    int searchNumberOfCitiesAvailableForAirport(const Airport& airport);
    int searchNumberOfCountriesAvailableForAirport(const Airport& airport);

    int searchNumberOfReachableAirportsInXStopsFromAirport(const Airport& airport, int layOvers);
    int searchNumberOfReachableCitiesInXStopsFromAirport(const Airport& airport, int layOvers);
    int searchNumberOfReachableCountriesInXStopsFromAirport(const Airport& airport, int layOvers);

    vector<pair<Airport,int>> searchTopKAirportGreatestAirTrafficCapacity(const int& k);

    unordered_set<string> searchEssentialAirports();

    void searchMaxTripAndCorrespondingPairsOfAirports();
    vector<vector<Airport>> searchSmallestPathBetweenAirports(const Airport& source, const Airport& target);
};


#endif //AED_AIRPORTS_CONSULT_H
