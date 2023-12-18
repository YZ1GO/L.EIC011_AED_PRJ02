#include "ParseData.h"

ParseData::ParseData(const string& airportsCSV, const string& airlinesCSV, const string& flightsCSV)
        : airportsCSV(airportsCSV), airlinesCSV(airlinesCSV), flightsCSV(flightsCSV) {
    parseAirports();
    parseAirlines();
    parseFlights();
}

void ParseData::parseAirports() {
    ifstream file(airportsCSV);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << airportsCSV << endl;
        return;
    }

    string line;
    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);

        string airlineCountry;
        string nonTrimmed;
        Airport airportObj;

        getline(ss, nonTrimmed, ',');
        airportObj.setCode(TrimString(nonTrimmed));

        getline(ss, nonTrimmed, ',');
        airportObj.setName(TrimString(nonTrimmed));

        getline(ss, nonTrimmed, ',');
        airportObj.setCity(TrimString(nonTrimmed));

        getline(ss, nonTrimmed, ',');
        airportObj.setCountry(TrimString(nonTrimmed));

        ss >> airportObj.setLatitude();
        ss.ignore();
        ss >> airportObj.setLongitude();

        AirportAndAirline airportAndAirline;
        airportAndAirline.setAirport(airportObj);

        dataGraph.addVertex(airportAndAirline);
    }
    file.close();
}

void ParseData::parseAirlines() {
    ifstream file(airlinesCSV);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << airlinesCSV << endl;
        return;
    }

    string line;
    getline(file, line);

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

        airlineGraph.addVertex(airlineObj);
    }

    file.close();
}

void ParseData::addAirlineToAirport(Airline airline) {
    string airlineCountry = airline.getCountry();

    for (auto v : Data) {
        AirportAndAirline& airportAndAirline = v->getInfo();
        if (airportAndAirline.airport.getCountry() == airlineCountry) {
            airportAndAirline.airlines.push_back(airline);
        }
    }
}


void ParseData::ParseFlights() {
    ifstream file(flightsCSV);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << flightsCSV << endl;
        return;
    }

    string line;
    getline(file, line);
    Airport source;
    Airport target;
    Airline airline;

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

        for (auto v : airportGraph.getVertexSet()) {
            auto airport = v->getInfo();
            if (flightObj.source == airport.code) {
                source = airport;
            }
            if (flightObj.target == airport.code) {
                target = airport;
            }
        }
        double distance = HarversineDistance(source.latitude, source.longitude, target.latitude, target.longitude);

        airportGraph.addEdge(source, target, flightObj.airlineCode, distance);
    }

    for (auto v : airportGraph.getVertexSet()) {
        v->setOutdegree(v->getAdj().size());
        for (auto e : v->getAdj()) {
            e.getDest()->addIndegree();
        }
    }

    file.close();
}