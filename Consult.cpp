#include "Consult.h"

Consult::Consult(const Graph<Airport> &dataGraph) : consultGraph(dataGraph) {};

int Consult::searchNumberOfAirports() {
    return consultGraph.getVertexSet().size();
}

int Consult::searchNumberOfAvailableFlightRoutes() {
    int totalFlightRoutes = 0;
    for (const auto& airport : consultGraph.getVertexSet()) {
        totalFlightRoutes += airport->getOutdegree();
    }
    return totalFlightRoutes;
}

int Consult::searchNumberOfFlightsOutOfAirport(const string& airportCode) {
    int numberOfFlights = 0;
    Airport temp = *new Airport();
    temp.setCode(airportCode);

    auto airport = consultGraph.findVertex(temp);
    if (airport != nullptr) {
        for (auto flights : airport->getAdj()) {
            numberOfFlights += flights.getAirlines().size();
        }
    }
    return numberOfFlights;
}

int Consult::searchNumberOfFlightsOutOfAirportFromDifferentAirlines(const string &airportCode) {
    Airport temp = *new Airport();
    temp.setCode(airportCode);
    set<Airline> airlines;

    auto airport = consultGraph.findVertex(temp);
    if (airport != nullptr) {
        for (auto flights : airport->getAdj()) {
            for (auto airline : flights.getAirlines()) {
                airlines.insert(airline);
            }
        }
    }
    return airlines.size();
}


set<string, int> Consult::searchNumberOfFlightsPerCity() {
    set<string, int> flightsPerCity;

    for (auto v : consultGraph.getVertexSet()) {
        v->setVisited(false);
    }

    for (auto v : consultGraph.getVertexSet()) {
        if (!v->isVisited())
            dfsVisit(v, flightsPerCity);
    }
    return flightsPerCity;
}

void Consult::dfsVisit(Vertex<Airport> *v, set<string, int> &res) const {
    v->setVisited(true);

}
