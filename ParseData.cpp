#include "ParseData.h"

ParseData::ParseData(const std::string& airportsCSV, const std::string& airlinesCSV, const std::string& flightsCSV) {
    this->airportsCSV = airportsCSV;
    this->airlinesCSV = airlinesCSV;
    this->flightsCSV = flightsCSV;
    parseAirports();
    parseFlights();
    parseAirlines();
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
        airportObj.setLocation(latitude, longitude);

        dataGraph.addVertex(airportObj);

    }
    file.close();
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

        Vertex<Airport>* sourceAirport = dataGraph.findVertex(findAirport(source));
        Vertex<Airport>* targetAirport = dataGraph.findVertex(findAirport(target));

        bool edgeExists = false;
        for (auto& e : sourceAirport->getAdj()) {
            auto t = e.getDest();
            if (t->getInfo() == targetAirport->getInfo()) {
                edgeExists = true;
                break;
            }
        }

        if (!edgeExists) {
            double distance = sourceAirport->getInfo().getDistance(targetAirport->getInfo().getLocation());
            dataGraph.addEdge(sourceAirport->getInfo(), targetAirport->getInfo(), distance);
        }

        sourceAirport->setOutdegree(sourceAirport->getOutdegree() + 1);
        targetAirport->setIndegree(targetAirport->getIndegree() + 1);
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

        for (auto& airport : dataGraph.getVertexSet()) {
            for (auto& target : airport->getAdj()) {
                for (auto& flight : target.getAirlines()) {
                    if (flight.getCode() == airlineObj.getCode()) {
                        Edge<Airport>& edge = const_cast<Edge<Airport>&>(target);
                        edge.addAirline(airlineObj);
                        break;
                    }
                }
            }
        }

    }
    file.close();
}



Airport ParseData::findAirport(const string& airportCode) {
    for (auto& v : dataGraph.getVertexSet()) {
        auto airport = v->getInfo();
        if (airport.getCode() == airportCode) {
            return airport;
        }
    }
    return {};
}
