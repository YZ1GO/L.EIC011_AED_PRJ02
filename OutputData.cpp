#include "OutputData.h"

/*
void convertAirportsToTextFile(const Graph<Airport>& airportGraph, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }

    for (const auto& a : airportGraph.getVertexSet()) {
        auto airport = a->getInfo();
        outFile << ">> [" << airport.code << "] " << airport.name << " <<" << std::endl;
        outFile << "    City     : " << airport.city << std::endl;
        outFile << "    Country  : " << airport.country << std::endl;
        outFile << "    Latitude : " << airport.latitude << std::endl;
        outFile << "    Longitude: " << airport.longitude << std::endl;
        outFile << "    Flights: " << std::endl;
        outFile << "    To this airport: " << a->getIndegree() << std::endl;
        outFile << "    From this airport: " << a->getOutdegree() << std::endl;
        for (auto e : a->getAdj()) {
            auto target = e.getDest()->getInfo();
            outFile << airport.code << " -> " << target.code << " by " << e.getAirline() << " airline : " << e.getWeight() << "km" << std::endl;
        }
        outFile << std::endl;
    }
    outFile.close();
}

void convertAirlinesToTextFile(const Graph<Airline>& airlineGraph, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }

    for (const auto& al : airlineGraph.getVertexSet()) {
        auto airline = al->getInfo();
        outFile << ">> [" << airline.code << "] " << airline.name << " <<" << std::endl;
        outFile << "    Callsign : " << airline.callsign << std::endl;
        outFile << "    Country  : " << airline.country << std::endl;
        outFile << std::endl;
    }

    outFile.close();
}
*/
void convertGraphToText(const Graph<AirportAndAirline>& g, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }

    for (auto v : g.getVertexSet()) {
        auto airport = v->getInfo().getAirport();
        auto airlines = v->getInfo().getAirlines();
        outFile << ">> [" << airport->getCode() << "] " << airport->getName() << " <<" << std::endl;
        outFile << "    City     : " << airport->getCity() << std::endl;
        outFile << "    Country  : " << airport->getCountry() << std::endl;
        outFile << "    Latitude : " << airport->getLatitude() << std::endl;
        outFile << "    Longitude: " << airport->getLongitude() << std::endl;

        outFile << "    Airlines at this airport:" << std::endl;

        for (auto airline : airlines) {
            outFile << "        - [" << airline.getCode() << "] " << airline.getName() << " - Callsign: " << airline.getCallsign() << std::endl;
        }


        outFile << "    Flights from/to this airport: " << std::endl;
        for (auto& edge : v->getAdj()) {
            auto targetAirport = edge.getDest()->getInfo().getAirport();
            outFile << "        " << airport->getCode() << " -> " << targetAirport->getCode() << " by " << edge.getAirline() << " airline : " << edge.getWeight() << "km" << std::endl;
        }

        outFile << std::endl;
    }

    outFile.close();
}


