#include "file_maker.h"
#include <vector>

void convertAirportsToTextFile(const std::vector<Airport>& airports, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }

    for (const auto& airport : airports) {
        outFile << ">> [" << airport.code << "] " << airport.name << " <<" << std::endl;
        outFile << "    City     : " << airport.city << std::endl;
        outFile << "    Country  : " << airport.country << std::endl;
        outFile << "    Latitude : " << airport.latitude << std::endl;
        outFile << "    Longitude: " << airport.longitude << std::endl;
        outFile << std::endl;
    }
    outFile.close();
}

void convertAirlinesToTextFile(const std::vector<Airline>& airlines, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }

    for (const auto& airline : airlines) {
        outFile << ">> [" << airline.code << "] " << airline.name << " <<" << std::endl;
        outFile << "    Callsign : " << airline.callsign << std::endl;
        outFile << "    Country  : " << airline.country << std::endl;
        outFile << std::endl;
    }

    outFile.close();
}


void convertFlightsToTextFile(const std::vector<Flight>& flights, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }

    for (const auto& flight : flights) {
        outFile << "[" << flight.source << "] -> [" << flight.target << "] by [" << flight.airlineCode << "]" << std::endl;
    }

    outFile.close();
}

