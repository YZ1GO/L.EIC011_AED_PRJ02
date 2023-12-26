#include <iostream>
//#include "OutputData.h"
#include "Consult.h"
#include "ListAirports.h"
#include "Script.h"

int main() {
    // File paths for CSV files
    std::string airportsCSV = "data/airports.csv";
    std::string airlinesCSV = "data/airlines.csv";
    std::string flightsCSV = "data/flights.csv";

    // Creating ParseData object and calling the constructor
    ParseData parseData(airportsCSV, airlinesCSV, flightsCSV);
    parseData.setupIndegreeOutdegree();

    const Graph<Airport>& dataGraph = parseData.getDataGraph();

    Script script(dataGraph);

    script.run();
    return 0;
}
