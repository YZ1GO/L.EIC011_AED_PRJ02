#ifndef AED_AIRPORTS_LISTAIRPORTS_H
#define AED_AIRPORTS_LISTAIRPORTS_H

#include "ParseData.h"

class ListAirports {
private:
    const Graph<Airport>& searchGraph;
public:
    ListAirports(const Graph<Airport>& dataGraph);

    Vertex<Airport>* findAirportByCode(const string& airportCode);
    vector<Vertex<Airport>*> findAirportsByName(const string& searchName);
    vector<Vertex<Airport>*> findAirportsByCityName(const string& searchName);
    vector<Vertex<Airport>*> findAirportsByCountryName(const string& searchName);

    vector<Vertex<Airport>*> findClosestAirports(const Coordinates& coordinates);
};


#endif //AED_AIRPORTS_LISTAIRPORTS_H
