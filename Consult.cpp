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

int Consult::searchNumberOfFlightsOutOfAirport(const string &airportCode) {
    int numberOfFlights = 0;
    return numberOfFlights;
}
