#include "OutputData.h"


void convertAirportsToTextFile(const Graph<Airport>& airportGraph, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }

    for (const auto& a : airportGraph.getVertexSet()) {
        auto airport = a->getInfo();
        outFile << ">> [" << airport.getCode() << "] " << airport.getName() << " <<" << std::endl;
        outFile << "    City       : " << airport.getCity() << std::endl;
        outFile << "    Country    : " << airport.getCountry() << std::endl;
        outFile << "    Coordinates: (" << airport.getLocation().latitude << ", " << airport.getLocation().longitude << ")" << std::endl;
        outFile << "    Flights    : " << std::endl;
        outFile << "    From this airport: " << a->getOutdegree() << std::endl;
        outFile << "    To this airport: " << a->getIndegree() << std::endl;
        for (auto e : a->getAdj()) {
            auto target = e.getDest()->getInfo();
            outFile << airport.getCode() << " -> " << target.getCode() << " by " << e.getAirlineCode() << " airline : " << e.getDistance() << "km" << std::endl;
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
        outFile << ">> [" << airline.getCode() << "] " << airline.getName() << " <<" << std::endl;
        outFile << "    Callsign : " << airline.getCallsign() << std::endl;
        outFile << "    Country  : " << airline.getCountry() << std::endl;
        outFile << std::endl;
    }

    outFile.close();
}

void convertDataGraphToTextFile(const Graph<Airport>& airportGraph, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }

    for (const auto& a : airportGraph.getVertexSet()) {
        auto airport = a->getInfo();
        outFile << ">> [" << airport.getCode() << "] " << airport.getName() << " <<" << std::endl;
        outFile << "    City       : " << airport.getCity() << std::endl;
        outFile << "    Country    : " << airport.getCountry() << std::endl;
        outFile << "    Coordinates: (" << airport.getLocation().latitude << ", " << airport.getLocation().longitude << ")" << std::endl;
        outFile << "    Flights    : " << std::endl;
        outFile << "    From this airport: " << a->getOutdegree() << std::endl;
        outFile << "    To this airport: " << a->getIndegree() << std::endl;
        for (auto e : a->getAdj()) {
            auto target = e.getDest()->getInfo();
            outFile << airport.getCode() << " -> " << target.getCode() << " by " << e.getAirlineCode() << " airline : " << e.getDistance() << "km" << std::endl;
        }
        outFile << std::endl;
    }
    outFile.close();
}

