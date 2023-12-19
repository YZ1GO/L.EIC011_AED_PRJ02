#include "ParseData.h"

ParseData::ParseData(const std::string& airportsCSV, const std::string& airlinesCSV, const std::string& flightsCSV) {
    this->airportsCSV = airportsCSV;
    this->airlinesCSV = airlinesCSV;
    this->flightsCSV = flightsCSV;
    parseAirlines();
    parseAirports();
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

        Edge<Airport>* foundEdge = nullptr;
        for (auto& e : sourceAirport->getAdj()) {
            auto t = e.getDest();
            if (t->getInfo() == targetAirport->getInfo()) {
                foundEdge = const_cast<Edge<Airport>*>(&e); // Cast away constness
                break;
            }
        }

        // Check if the edge was found and add the airline
        if (foundEdge) {
            foundEdge->addAirline(getAirline(airlineCode));
        } else {
            double distance = sourceAirport->getInfo().getDistance(targetAirport->getInfo().getLocation());
            dataGraph.addEdge(sourceAirport->getInfo(), targetAirport->getInfo(), distance);

            // Increment degrees
            sourceAirport->setOutdegree(sourceAirport->getOutdegree() + 1);
            targetAirport->setIndegree(targetAirport->getIndegree() + 1);

            // Get the newly added edge and add the airline
            for (auto& e : sourceAirport->getAdj()) {
                auto t = e.getDest();
                if (t->getInfo() == targetAirport->getInfo()) {
                    Edge<Airport>& nonConstEdge = const_cast<Edge<Airport>&>(e);
                    nonConstEdge.addAirline(getAirline(airlineCode));
                    break;
                }
            }
        }

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

        airlinesInfo.insert(airlineObj);

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

Airline ParseData::getAirline(const std::string& airlineCode) {
    for (auto it = airlinesInfo.begin(); it != airlinesInfo.end(); ++it) { // Fixed the syntax error here
        if (it->getCode() == airlineCode) return *it;
    }
    return {}; // Return default-constructed Airline if not found
}