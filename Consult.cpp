#include "Consult.h"

Consult::Consult(const Graph<Airport> &dataGraph) : consultGraph(dataGraph) {};

int Consult::searchNumberOfAirports() {
    return static_cast<int>(consultGraph.getVertexSet().size());
}

int Consult::searchNumberOfAvailableFlightRoutes() {
    int totalFlightRoutes = 0;
    for (const auto& airport : consultGraph.getVertexSet()) {
        totalFlightRoutes += airport->getOutdegree();
    }
    return totalFlightRoutes;
}

int Consult::searchNumberOfFlightsOutOfAirport(const Airport& airport) {
    int numberOfFlights = 0;

    auto a = consultGraph.findVertex(airport);
    if (a != nullptr) {
        for (const auto& flights : a->getAdj()) {
            numberOfFlights += static_cast<int>(flights.getAirlines().size());
        }
    }
    return numberOfFlights;
}

int Consult::searchNumberOfFlightsToAirport(const Airport &airport) {
    int numberOfFlights = 0;

    auto a = consultGraph.findVertex(airport);
    if (a != nullptr) {
        for (const auto& v : consultGraph.getVertexSet()) {
            for (const auto& flight : v->getAdj()) {
                if (flight.getDest()->getInfo() == airport)
                    numberOfFlights++;
            }
        }
    }
    return numberOfFlights;
}

int Consult::searchNumberOfFlightsOutOfAirportFromDifferentAirlines(const Airport& airport) {
    set<Airline> airlines;

    auto a = consultGraph.findVertex(airport);
    if (a != nullptr) {
        for (const auto& flights : a->getAdj()) {
            for (const auto& airline : flights.getAirlines()) {
                airlines.insert(airline);
            }
        }
    }
    return static_cast<int>(airlines.size());
}

map<string, int> Consult::searchNumberOfFlightsPerCity() {
    map<string, int> flightsPerCity;

    for (auto v : consultGraph.getVertexSet()) {
        v->setVisited(false);
    }

    for (auto v : consultGraph.getVertexSet()) {
        if (!v->isVisited())
            dfsVisitFlightsPerCity(v, flightsPerCity);
    }
    return flightsPerCity;
}

void Consult::dfsVisitFlightsPerCity(Vertex<Airport> *v, map<string, int> &res) {
    v->setVisited(true);
    auto city = v->getInfo().getCity();
    int flightsCount = searchNumberOfFlightsOutOfAirport(v->getInfo());

    auto it = res.find(city);
    if (it != res.end()) {
        res[city] = flightsCount;
    } else {
        res[city] += flightsCount;
    }

    for (const auto &flight : v->getAdj()) {
        auto d = flight.getDest();
        if (!d->isVisited())
            dfsVisitFlightsPerCity(d, res);
    }
}

map<string, int> Consult::searchNumberOfFlightsPerAirline() {
    map<string, int> flightsPerAirline;

    for (auto v : consultGraph.getVertexSet()) {
        v->setVisited(false);
    }

    for (auto v : consultGraph.getVertexSet()) {
        if (!v->isVisited())
            dfsVisitFlightsPerAirline(v, flightsPerAirline);
    }
    return flightsPerAirline;
}

void Consult::dfsVisitFlightsPerAirline(Vertex<Airport> *v, map<string, int> &res) {
    v->setVisited(true);
    for (const auto& flight : v->getAdj()) {
        for (const auto& airline : flight.getAirlines()) {
            res[airline.getName()]++;
        }
    }

    for (const auto &flight : v->getAdj()) {
        auto d = flight.getDest();
        if (!d->isVisited())
            dfsVisitFlightsPerAirline(d, res);
    }
}

int Consult::searchNumberOfCountriesFlownToFromAirport(const Airport& airport) {
    set<string> countries;
    auto a = consultGraph.findVertex(airport);
    if (a != nullptr) {
        for (const auto& flight : a->getAdj()) {
            countries.insert(flight.getDest()->getInfo().getCountry());
        }
    }
    return static_cast<int>(countries.size());
}

int Consult::searchNumberOfCountriesFlownToFromCity(const string &city, const string& country) {
    set<string> countries;
    vector<Vertex<Airport>*> cityAirports;
    for (auto v : consultGraph.getVertexSet()) {
        v->setVisited(false);
    }

    for (auto v : consultGraph.getVertexSet()) {
        if (!v->isVisited())
            dfsVisitCityAirports(city, country, v, cityAirports);
    }

    for (const auto& v : cityAirports) {
        for (const auto& flight : v->getAdj()) {
            countries.insert(flight.getDest()->getInfo().getCountry());
        }
    }
    return static_cast<int>(countries.size());
}

void Consult::dfsVisitCityAirports(const string &city, const string& country, Vertex<Airport> *v, vector<Vertex<Airport>*> &res) {
    v->setVisited(true);
    if (v->getInfo().getCity() == city && v->getInfo().getCountry() == country)
        res.push_back(v);
    for (const auto &flight : v->getAdj()) {
        auto d = flight.getDest();
        if (!d->isVisited())
            dfsVisitCityAirports(city, country, d, res);
    }
}

int Consult::searchNumberOfAirportsAvailableForAirport(const Airport &airport) {
    int numberOfAirports = 0;
    auto a = consultGraph.findVertex(airport);
    if (a != nullptr)
        numberOfAirports = static_cast<int>(a->getAdj().size());
    return numberOfAirports;
}

int Consult::searchNumberOfCitiesAvailableForAirport(const Airport &airport) {
    set<string> cities;
    auto a = consultGraph.findVertex(airport);
    if (a != nullptr) {
        for (auto flight : a->getAdj()) {
            cities.insert(flight.getDest()->getInfo().getCity());
        }
    }
    return static_cast<int>(cities.size());
}




