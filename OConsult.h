#ifndef AED_AEROPORTO_OCONSULT_H
#define AED_AEROPORTO_OCONSULT_H

#include "Data.h"
#include "ParseData.h"
#include <unordered_set>

class OConsult {
private:
    const Graph<Airport>& consultGraph;

    void dfs_art(Vertex<Airport> *v, stack<string> &s, unordered_set<string> &l, int &i);
    vector<Airport> topTrafficCapacityAirports();
    int search
public:
    OConsult(const Graph<Airport>& dataGraph);

    unordered_set<string> searchEssentialAirports();
    vector<Airport> searchTopKairportGreatestAirTrafficCapacity(const int& k);
};


#endif //AED_AEROPORTO_OCONSULT_H
