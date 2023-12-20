#ifndef AED_AEROPORTO_OCONSULT_H
#define AED_AEROPORTO_OCONSULT_H

#include "Data.h"
#include "ParseData.h"
#include <unordered_set>

class OConsult {
private:
    const Graph<Airport>& consultGraph;

    void dfs_art(Vertex<Airport> *v, stack<string> &s, unordered_set<string> &l, int &i);
public:
    OConsult(const Graph<Airport>& dataGraph);
    std::unordered_set<std::string> searchEssentialAirports();

};


#endif //AED_AEROPORTO_OCONSULT_H
