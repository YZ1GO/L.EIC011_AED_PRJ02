#include <iostream>
#include "ParseData.h"
#include "OutputData.h"

int main() {
    cout << "main class executed" << endl;
    // File paths for CSV files
    std::string airportsCSV = "data/airports.csv";
    std::string airlinesCSV = "data/airlines.csv";
    std::string flightsCSV = "data/flights.csv";

    // Creating ParseData object and calling the constructor
    ParseData parseData(airportsCSV, airlinesCSV, flightsCSV);

    // Parsing the data
    // Assuming that ParseData constructor initiates parsing within the constructor
    // So, the parsed data should already be available after constructor invocation

    // Now, call convertGraphToText using the parsed data
    convertGraphToText(parseData.getData(), "data_text/graph.txt");

    return 0;
}
