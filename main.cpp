#include <iostream>
#include "ReadData.h"

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



int main() {
    ReadData readData;

    vector<Airport> airports = readData.ReadAirports("data/airports.csv");
    convertAirportsToTextFile(airports, "data_text/Airports.txt");

    vector<Airline> airlines = readData.ReadAirlines("data/airlines.csv");
    convertAirlinesToTextFile(airlines, "data_text/Airlines.txt");

    vector<Flight> flights = readData.ReadFlights("data/flights.csv");
    convertFlightsToTextFile(flights, "data_text/Flights.txt");

    return 0;
}
