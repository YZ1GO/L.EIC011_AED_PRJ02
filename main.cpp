#include <iostream>
//#include "ReadData.h"
//#include "file_maker.h"
#include "ParseData.h"
#include "OutputData.h"

int main() {
    /*ReadData readData;
    vector<Airport> airports = readData.ReadAirports("data/airports.csv");
    vector<Airline> airlines = readData.ReadAirlines("data/airlines.csv");
    vector<Flight> flights = readData.ReadFlights("data/flights.csv");

    convertAirportsToTextFile(airports, "data_text/Airports.txt");
    convertAirlinesToTextFile(airlines, "data_text/Airlines.txt");
    convertFlightsToTextFile(flights, "data_text/Flights.txt");*/
    /*
    ParseData parseData;
    Graph<Airport> airports = parseData.ParseAirports("data/airports.csv");
    Graph<Airline> airlines = parseData.ParseAirlines("data/airports.csv");
    parseData.ParseFlights(airports, "data/flights.csv");

    convertAirportsToTextFile(airports, "text/Airports.txt");
    convertAirlinesToTextFile(airlines, "text/Airlines.txt");*/

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
