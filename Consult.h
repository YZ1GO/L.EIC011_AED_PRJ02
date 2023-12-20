#ifndef AED_AIRPORTS_CONSULT_H
#define AED_AIRPORTS_CONSULT_H

#include "ParseData.h"
#include <map>
#include <unordered_set>
#include <limits>

class Consult {
private:
    const Graph<Airport>& consultGraph;

    void dfs_art(Vertex<Airport> *v, stack<string> &s, unordered_set<string> &l, int &i);
    void dfs_greatestTrip(Vertex<Airport>* source, Vertex<Airport>* target, vector<vector<Airport>>& greatestTrips, vector<Airport> currentTrip, int& maxTrip);
    void dfs_smallestTrip(Vertex<Airport>* source, Vertex<Airport>* target, vector<vector<Airport>>& smallestTrips, vector<Airport> currentTrip, int& minTrip);
    vector<pair<Airport,int>> topTrafficCapacityAirports();

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
    int searchNumberOfReachableCitiesInXStopsFromAirport(const Airport& airport, int layOvers);
    int searchNumberOfReachableCountriesInXStopsFromAirport(const Airport& airport, int layOvers);

    unordered_set<string> searchEssentialAirports();
    vector<pair<Airport,int>> searchTopKairportGreatestAirTrafficCapacity(const int& k);
    vector<vector<Airport>> searchTripGreatestNumberOfStopsBetweenThem(const Airport& source, const Airport& target);
    vector<vector<Airport>> searchTripSmallestNumberOfStopsBetweenThem(const Airport& source, const Airport& target);
};


#endif //AED_AIRPORTS_CONSULT_H
