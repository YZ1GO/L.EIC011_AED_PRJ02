#include <iostream>
#include "ReadData.h"
#include "file_maker.h"
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

    ParseData parseData;
    Graph<Airport> airports = parseData.ParseAirports("data/airports.csv");
    Graph<Airline> airlines = parseData.ParseAirlines("data/airlines.csv");
    parseData.ParseFlights(airports, "data/flights.csv");

    convertAirportsToTextFile(airports, "text/Airports.txt");
    convertAirlinesToTextFile(airlines, "text/Airlines.txt");

    return 0;
}
