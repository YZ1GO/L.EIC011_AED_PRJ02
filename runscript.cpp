#include <iostream>
#include "Script.h"

int main() {
    std::string airportsCSV = "data/airports.csv";
    std::string airlinesCSV = "data/airlines.csv";
    std::string flightsCSV = "data/flights.csv";
    ParseData parseData(airportsCSV, airlinesCSV, flightsCSV);
    Script script(parseData.getDataGraph());

    script.run();

    return 0;
}
