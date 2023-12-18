#include "ReadData.h"

using namespace std;

ReadData::ReadData() {}

vector<Airport> ReadData::ReadAirports(const string &airportsCSV) {

    vector<Airport> airports;
    ifstream file(airportsCSV);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << airportsCSV << endl;
        return airports;
    }

    string line;
    getline(file, line);

    while(getline(file, line)){
        stringstream ss(line);

        string nonTrimmed;
        Airport airportObj;

        getline(ss, nonTrimmed, ',');
        airportObj.code = TrimString(nonTrimmed);

        getline(ss, nonTrimmed, ',');
        airportObj.name = TrimString(nonTrimmed);

        getline(ss, nonTrimmed, ',');
        airportObj.city = TrimString(nonTrimmed);

        getline(ss, nonTrimmed, ',');
        airportObj.country = TrimString(nonTrimmed);

        ss >> airportObj.latitude;
        ss.ignore(); // Ignore the comma separator
        ss >> airportObj.longitude;

        airports.push_back(airportObj);
    }
    file.close();
    return airports;
}

vector<Airline> ReadData::ReadAirlines(const string& airlinesCSV) {
    vector<Airline> airlines;
    ifstream file(airlinesCSV);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << airlinesCSV << endl;
        return airlines;
    }

    string line;
    getline(file, line); // Skip header line if present

    while(getline(file, line)){
        stringstream ss(line);

        string nonTrimmed;
        Airline airlineObj;

        getline(ss, nonTrimmed, ',');
        airlineObj.code = TrimString(nonTrimmed);

        getline(ss, nonTrimmed, ',');
        airlineObj.name = TrimString(nonTrimmed);

        getline(ss, nonTrimmed, ',');
        airlineObj.callsign = TrimString(nonTrimmed);

        getline(ss, nonTrimmed, ',');
        airlineObj.country = TrimString(nonTrimmed);

        airlines.push_back(airlineObj);
    }
    file.close();
    return airlines;
}

vector<Flight> ReadData::ReadFlights(const string& flightsCSV) {
    vector<Flight> flights;
    ifstream file(flightsCSV);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << flightsCSV << endl;
        return flights;
    }

    string line;
    getline(file, line);

    while(getline(file, line)){
        stringstream ss(line);

        string src, tgt, ac;
        Flight flightObj;

        getline(ss, src, ',');
        flightObj.source = TrimString(src);

        getline(ss, tgt, ',');
        flightObj.target = TrimString(tgt);

        getline(ss, ac, ',');
        flightObj.airlineCode = TrimString(ac);

        flights.push_back(flightObj);
    }
    file.close();
    return flights;
}



