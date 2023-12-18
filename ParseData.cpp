#include "ParseData.h"

ParseData::ParseData(const std::string& airportsCSV, const std::string& airlinesCSV, const std::string& flightsCSV) {
    this->airportsCSV = airportsCSV;
    this->airlinesCSV = airlinesCSV;
    this->flightsCSV = flightsCSV;
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

        string nonTrimmed;
        Airport airportObj;
        double latitude, longitude;

        getline(ss, nonTrimmed, ',');
        airportObj.setCode(TrimString(nonTrimmed));

        getline(ss, nonTrimmed, ',');
        airportObj.setName(TrimString(nonTrimmed));

        getline(ss, nonTrimmed, ',');
        airportObj.setCity(TrimString(nonTrimmed));

        getline(ss, nonTrimmed, ',');
        airportObj.setCountry(TrimString(nonTrimmed));

        ss >> latitude;
        ss.ignore();
        ss >> longitude;
        airportObj.setLatitude(latitude);
        airportObj.setLongitude(longitude);

        AirportAndAirline airportAndAirline(&airportObj);
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
    getline(file, line); // Skipping header

    while(getline(file, line)){
        stringstream ss(line);

        string nonTrimmed;
        Airline airlineObj;

        getline(ss, nonTrimmed, ',');
        airlineObj.setCode(TrimString(nonTrimmed));

        getline(ss, nonTrimmed, ',');
        airlineObj.setName(TrimString(nonTrimmed));

        getline(ss, nonTrimmed, ',');
        airlineObj.setCallsign(TrimString(nonTrimmed));

        getline(ss, nonTrimmed, ',');
        airlineObj.setCountry(TrimString(nonTrimmed));

        addAirlineToAirport(airlineObj);
    }

    file.close();
}

void ParseData::addAirlineToAirport(const Airline& airline) {
    string airlineCountry = airline.getCountry();

    for (auto& v : dataGraph.getVertexSet()) {
        auto airportAndAirline = v->getInfo();
        if (airportAndAirline.getAirport()->getCountry() == airlineCountry) {
            airportAndAirline.addAirline(airline);
        }
    }
}

void ParseData::parseFlights() {
    ifstream file(flightsCSV);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << flightsCSV << endl;
        return;
    }

    string line;
    getline(file, line); // Skipping header

    while(getline(file, line)) {
        stringstream ss(line);

        string source, target, airlineCode;

        getline(ss, source, ',');
        source = TrimString(source);

        getline(ss, target, ',');
        target = TrimString(target);

        getline(ss, airlineCode, ',');
        airlineCode = TrimString(airlineCode);

        Vertex<AirportAndAirline>* sourceVertex = dataGraph.findVertex(findAirport(source));
        Vertex<AirportAndAirline>* targetVertex = dataGraph.findVertex(findAirport(target));

        if (sourceVertex && targetVertex) {
            double distance = sourceVertex->getInfo().getAirport()->getDistance(*findAirport(target));
            dataGraph.addEdge(sourceVertex->getInfo(), targetVertex->getInfo(), distance);
            sourceVertex->setOutdegree(sourceVertex->getOutdegree() + 1);
            targetVertex->setIndegree(targetVertex->getIndegree() + 1);
        }
    }

    file.close();
}

Airport* ParseData::findAirport(const string& airportCode) {
    for (auto& v : dataGraph.getVertexSet()) {
        auto airport = v->getInfo().getAirport();
        if (airport->getCode() == airportCode) {
            return airport;
        }
    }
    return nullptr;
}
