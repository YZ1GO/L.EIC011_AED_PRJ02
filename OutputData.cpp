#include "OutputData.h"

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
        outFile << "    Flights from this airport : " << a->getOutdegree() << std::endl;
        outFile << "    Flights to this airport   : " << a->getIndegree() << std::endl << std::endl;

        for (auto e : a->getAdj()) {
            auto target = e.getDest()->getInfo();
            outFile << "    • " << airport.getCode() << " -> " << target.getCode() << " : " << e.getDistance() << "km" << std::endl;
            outFile << "        by Airlines: " << std::endl;
            int i = 1;
            for (auto airline : e.getAirlines()) {
                outFile << "            " << i++ << ".[" << airline.getCode() << "] " << airline.getCallsign() << std::endl;
            }
            outFile << std::endl;
        }
        outFile << std::endl;
    }
    outFile.close();
}

