#include "OutputData.h"

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
            outFile << airport.code << ", " << target.code << ", " << e.getAirline() << ", " << e.getWeight() << "km" << std::endl;
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
