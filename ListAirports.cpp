#include "ListAirports.h"

ListAirports::ListAirports(const Graph<Airport> &dataGraph) : searchGraph(dataGraph) {};

Vertex<Airport>* ListAirports::findAirportByCode(const string& airportCode) {
    for (auto airport : searchGraph.getVertexSet()) {
        if (airport->getInfo().getCode() == airportCode) {
            return airport;
        }
    }
    return nullptr;
}

vector<Vertex<Airport>*> ListAirports::findAirportsByName(const string& searchName) {
    vector<Vertex<Airport>*> matchingAirports;
    string searchNameLowered = RemoveSpaces(ToLower(searchName));
    for (auto airport : searchGraph.getVertexSet()) {
        auto airportNameLowered = RemoveSpaces(ToLower(airport->getInfo().getName()));
        if (airportNameLowered.find(searchNameLowered) != string::npos) {
            matchingAirports.push_back(airport);
        }
    }

    sort(matchingAirports.begin(), matchingAirports.end(), [](Vertex<Airport>* a, Vertex<Airport>* b) {
        return ToLower(a->getInfo().getName()) < ToLower(b->getInfo().getName());
    });

    return matchingAirports;
}

vector<Vertex<Airport>*> ListAirports::findAirportsByCityName(const string& searchName) {
    vector<Vertex<Airport>*> matchingAirports;
    string searchNameLowered = RemoveSpaces(ToLower(searchName));
    for (auto airport : searchGraph.getVertexSet()) {
        auto cityNameLowered = RemoveSpaces(ToLower(airport->getInfo().getCity()));
        if (cityNameLowered.find(searchNameLowered) != string::npos) {
            matchingAirports.push_back(airport);
        }
    }

    sort(matchingAirports.begin(), matchingAirports.end(), [](Vertex<Airport>* a, Vertex<Airport>* b) {
        return ToLower(a->getInfo().getName()) < ToLower(b->getInfo().getName());
    });

    return matchingAirports;
}

vector<Vertex<Airport>*> ListAirports::findAirportsByCountryName(const string& searchName) {
    vector<Vertex<Airport>*> matchingAirports;
    string searchNameLowered = RemoveSpaces(ToLower(searchName));
    for (auto airport : searchGraph.getVertexSet()) {
        auto countryNameLowered = RemoveSpaces(ToLower(airport->getInfo().getCountry()));
        if (countryNameLowered.find(searchNameLowered) != string::npos) {
            matchingAirports.push_back(airport);
        }
    }

    sort(matchingAirports.begin(), matchingAirports.end(), [](Vertex<Airport>* a, Vertex<Airport>* b) {
        return ToLower(a->getInfo().getName()) < ToLower(b->getInfo().getName());
    });

    return matchingAirports;
}

vector<Vertex<Airport>*> ListAirports::findClosestAirports(const Coordinates& coordinates) {
    vector<Vertex<Airport>*> closestAirports;
    double minDistance = numeric_limits<double>::max();

    for (auto airport : searchGraph.getVertexSet()) {
        auto airportCoordinates = airport->getInfo().getLocation();
        double distance = HarversineDistance(coordinates.latitude, coordinates.longitude, airportCoordinates.latitude, airportCoordinates.longitude);

        if (distance < minDistance) {
            minDistance = distance;
            closestAirports.clear();
            closestAirports.push_back(airport);
        } else if (distance == minDistance) {
            closestAirports.push_back(airport);
        }
    }

    sort(closestAirports.begin(), closestAirports.end(), [](Vertex<Airport>* a, Vertex<Airport>* b) {
        return ToLower(a->getInfo().getName()) < ToLower(b->getInfo().getName());
    });

    return closestAirports;
}

