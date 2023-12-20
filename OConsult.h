#ifndef AED_AEROPORTO_OCONSULT_H
#define AED_AEROPORTO_OCONSULT_H

#include "Data.h"
#include "ParseData.h"
#include <unordered_set>
#include <unordered_map>
#include <limits>

class OConsult {
private:
    const Graph<Airport>& consultGraph;

    void dfs_art(Vertex<Airport> *v, stack<string> &s, unordered_set<string> &l, int &i);
    void dfs_greatestTrip(Vertex<Airport>* source, Vertex<Airport>* target, vector<vector<Airport>>& greatestTrips, vector<Airport> currentTrip, int& maxTrip);
    void dfs_smallestTrip(Vertex<Airport>* source, Vertex<Airport>* target, vector<vector<Airport>>& smallestTrips, vector<Airport> currentTrip, int& minTrip);

    vector<pair<Airport,int>> topTrafficCapacityAirports();


public:
    OConsult(const Graph<Airport>& dataGraph);

    unordered_set<string> searchEssentialAirports();
    vector<pair<Airport,int>> searchTopKairportGreatestAirTrafficCapacity(const int& k);
    vector<vector<Airport>> searchTripGreatestNumberOfStopsBetweenThem(const Airport& source, const Airport& target);
    vector<vector<Airport>> searchTripSmallestNumberOfStopsBetweenThem(const Airport& source, const Airport& target);

    int searchNumberOfFlightsOutOfAirport(const Airport& airport);
    int searchNumberOfFlightsToAirport(const Airport& airport);
};


#endif //AED_AEROPORTO_OCONSULT_H
