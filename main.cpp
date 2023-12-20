#include <iostream>
#include "OutputData.h"
#include "Consult.h"
#include "OConsult.h"

int main() {
    // File paths for CSV files
    std::string airportsCSV = "data/airports.csv";
    std::string airlinesCSV = "data/airlines.csv";
    std::string flightsCSV = "data/flights.csv";

    // Creating ParseData object and calling the constructor
    ParseData parseData(airportsCSV, airlinesCSV, flightsCSV);
    parseData.setupIndegreeOutDegree();

    //convertDataGraphToTextFile(parseData.getDataGraph(), "text/Global_Data.txt");

    Consult consult(parseData.getDataGraph());
    cout << consult.searchNumberOfAirports() << endl;
    cout << consult.searchNumberOfAvailableFlightRoutes() << endl;

    OConsult oConsult(parseData.getDataGraph());
    int i = 1;
    for (const auto& airport : oConsult.searchEssentialAirports()) {
        cout << i++ << ". " << airport << endl;
    }
    return 0;
}
