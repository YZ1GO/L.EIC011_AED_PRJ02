#include "ParseData.h"

Graph<Airport> ParseData::ParseAirports(const std::string &airportsCSV) {
    Graph<Airport> airportGraph;

    ifstream file(airportsCSV);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << airportsCSV << endl;
        return airportGraph;
    }

    string line;
    getline(file, line);

    while(getline(file, line)) {
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

        airportGraph.addVertex(airportObj);
    }

    file.close();
    return airportGraph;
}

Graph<Airline> ParseData::ParseAirlines(const string& airlinesCSV) {
    Graph<Airline> airlineGraph;

    ifstream file(airlinesCSV);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << airlinesCSV << endl;
        return airlineGraph;
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
    return airlineGraph;
}

void ParseData::ParseFlights(Graph<Airport>& airportGraph, const string& flightsCSV) {
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