#include <iostream>
#include "ParseData.h"
#include "OutputData.h"

int main() {
    // File paths for CSV files
    std::string airportsCSV = "data/airports.csv";
    std::string airlinesCSV = "data/airlines.csv";
    std::string flightsCSV = "data/flights.csv";

    // Creating ParseData object and calling the constructor
    ParseData parseData(airportsCSV, airlinesCSV, flightsCSV);

    convertAirportsToTextFile(parseData.getAirportsGraph(), "text/airports.txt");
    convertAirlinesToTextFile(parseData.getAirlinesGraph(), "text/airlines.txt");

    return 0;
}
