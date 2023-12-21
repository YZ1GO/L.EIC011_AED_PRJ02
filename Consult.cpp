#include "Consult.h"

Consult::Consult(const Graph<Airport> &dataGraph) : consultGraph(dataGraph) {};

int Consult::searchNumberOfAirports() {
    return static_cast<int>(consultGraph.getVertexSet().size());
}

int Consult::searchNumberOfAvailableFlights() {
    int totalFlights = 0;
    for (const auto& airport : consultGraph.getVertexSet())
        totalFlights += airport->getFlightsTo();
    return totalFlights;
}

int Consult::searchNumberOfAvailableFlightRoutes() {
    int totalFlightRoutes = 0;
    for (const auto& airport : consultGraph.getVertexSet())
        totalFlightRoutes += airport->getOutdegree();
    return totalFlightRoutes;
}

int Consult::searchNumberOfFlightsOutOfAirport(const Airport& airport) {
    Vertex<Airport>* vertex = consultGraph.findVertex(airport);
    return (vertex != nullptr) ? vertex->getFlightsFrom() : 0;
}

int Consult::searchNumberOfFlightsToAirport(const Airport &airport) {
    Vertex<Airport>* vertex = consultGraph.findVertex(airport);
    return (vertex != nullptr) ? vertex->getFlightsTo() : 0;
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

    for (auto v : consultGraph.getVertexSet())
        v->setVisited(false);

    for (auto v : consultGraph.getVertexSet())
        if (!v->isVisited())
            dfsVisitFlightsPerCity(v, flightsPerCity);

    return flightsPerCity;
}

void Consult::dfsVisitFlightsPerCity(Vertex<Airport> *v, map<string, int> &res) {
    v->setVisited(true);

    res[v->getInfo().getCity()] += v->getFlightsFrom();

    for (const auto &flight : v->getAdj()) {
        auto d = flight.getDest();
        if (!d->isVisited())
            dfsVisitFlightsPerCity(d, res);
    }
}

map<string, int> Consult::searchNumberOfFlightsPerAirline() {
    map<string, int> flightsPerAirline;

    for (auto v : consultGraph.getVertexSet())
        v->setVisited(false);

    for (auto v : consultGraph.getVertexSet())
        if (!v->isVisited())
            dfsVisitFlightsPerAirline(v, flightsPerAirline);

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

    for (auto v : consultGraph.getVertexSet())
        v->setVisited(false);

    for (auto v : consultGraph.getVertexSet())
        if (!v->isVisited())
            dfsVisitCityAirports(city, country, v, cityAirports);

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

int Consult::searchNumberOfReachableDestinationsInXStopsFromAirport(const Airport& airport, int layOvers, const function<string(const Airport&)>& attributeExtractor) {
    queue<pair<Vertex<Airport>*, int>> reachableAirports;
    set<string> reachableDestinations;

    auto a = consultGraph.findVertex(airport);
    if (a != nullptr) {
        for (auto v: consultGraph.getVertexSet())
            v->setVisited(false);
        reachableAirports.emplace(a, 0);
        a->setVisited(true);

        while (!reachableAirports.empty()) {
            auto pair = reachableAirports.front();
            reachableAirports.pop();

            Vertex<Airport>* ap = pair.first;
            int stop = pair.second;

            if (stop <= layOvers) {
                for (const auto& flight : ap->getAdj()) {
                    reachableDestinations.insert(attributeExtractor(flight.getDest()->getInfo()));
                }
            }

            for (const auto& flight : ap->getAdj()) {
                auto d = flight.getDest();
                if (!d->isVisited()) {
                    reachableAirports.emplace(d, stop + 1);
                    d->setVisited(true);
                }
            }
        }
    }
    return static_cast<int>(reachableDestinations.size());
}

int Consult::searchNumberOfReachableAirportsInXStopsFromAirport(const Airport& airport, int layOvers) {
    function<string(const Airport&)> extractAirportCode = [](const Airport& airport) { return airport.getCode(); };
    return searchNumberOfReachableDestinationsInXStopsFromAirport(airport, layOvers, extractAirportCode);
}

int Consult::searchNumberOfReachableCitiesInXStopsFromAirport(const Airport& airport, int layOvers) {
    function<string(const Airport&)> extractCity = [](const Airport& airport) { return airport.getCity(); };
    return searchNumberOfReachableDestinationsInXStopsFromAirport(airport, layOvers, extractCity);
}

int Consult::searchNumberOfReachableCountriesInXStopsFromAirport(const Airport& airport, int layOvers) {
    function<string(const Airport&)> extractCountry = [](const Airport& airport) { return airport.getCountry(); };
    return searchNumberOfReachableDestinationsInXStopsFromAirport(airport, layOvers, extractCountry);
}

vector<vector<Airport>> Consult::searchTripGreatestNumberOfStopsBetweenThem(const Airport& source, const Airport& target) {
    vector<vector<Airport>> greatestTrips;
    vector<Airport> currentTrip;
    int maxTrip = 0;

    auto sourceAirport = consultGraph.findVertex(source);
    auto targetAirport = consultGraph.findVertex(target);

    if (sourceAirport == nullptr || targetAirport == nullptr) {
        return greatestTrips;
    }

    for (auto v : consultGraph.getVertexSet()) {
        v->setVisited(false);
    }

    dfs_greatestTrip(sourceAirport, targetAirport, greatestTrips, currentTrip, maxTrip);

    return greatestTrips;
}

void Consult::dfs_greatestTrip(Vertex<Airport>* source, Vertex<Airport>* target, vector<vector<Airport>>& greatestTrips, vector<Airport> currentTrip, int& maxTrip) {
    currentTrip.push_back(source->getInfo());

    if (source->getInfo() == target->getInfo()) {
        if (maxTrip < currentTrip.size()) {
            maxTrip = currentTrip.size();
            greatestTrips.clear();
        }
        if (maxTrip == currentTrip.size()) {
            greatestTrips.push_back(currentTrip);
        }
        return;
    }
    source->setVisited(true);

    for (auto &e : source->getAdj()) {
        auto w = e.getDest();
        if (!w->isVisited()) {
            dfs_greatestTrip(w, target, greatestTrips, currentTrip, maxTrip);
        }
    }
}

vector<vector<Airport>> Consult::searchTripSmallestNumberOfStopsBetweenThem(const Airport& source, const Airport& target) {
    vector<vector<Airport>> smallestTrips;
    vector<Airport> currentTrip;
    int minTrip = numeric_limits<int>::max();

    auto sourceAirport = consultGraph.findVertex(source);
    auto targetAirport = consultGraph.findVertex(target);

    if (sourceAirport == nullptr || targetAirport == nullptr) {
        return smallestTrips;
    }

    for (auto v : consultGraph.getVertexSet()) {
        v->setVisited(false);
    }

    dfs_smallestTrip(sourceAirport, targetAirport, smallestTrips, currentTrip, minTrip);

    return smallestTrips;
}

void Consult::dfs_smallestTrip(Vertex<Airport>* source, Vertex<Airport>* target, vector<vector<Airport>>& smallestTrips, vector<Airport> currentTrip, int& minTrip) {
    currentTrip.push_back(source->getInfo());

    if (source->getInfo() == target->getInfo()) {
        if (minTrip > currentTrip.size()) {
            minTrip = currentTrip.size();
            smallestTrips.clear();
        }
        if (minTrip == currentTrip.size()) {
            smallestTrips.push_back(currentTrip);
        }
        return;
    }
    source->setVisited(true);

    for (auto &e : source->getAdj()) {
        auto w = e.getDest();
        if (!w->isVisited()) {
            dfs_smallestTrip(w, target, smallestTrips, currentTrip, minTrip);
        }
    }
}

vector<pair<Airport,int>> Consult::searchTopKAirportGreatestAirTrafficCapacity(const int& k) {
    vector<pair<Airport,int>> res;
    vector<Vertex<Airport>*> airports;
    for (const auto& airport : consultGraph.getVertexSet()) {
        airports.push_back(airport);
    }

    sort(airports.begin(), airports.end(), [&](const Vertex<Airport>* a1, const Vertex<Airport>* a2) {
        return a1->getFlightsTo() + a1->getFlightsFrom() > a2->getFlightsTo() + a2->getFlightsFrom();
    });

    for (int i = 0; i < airports.size(); i++) {
        int last_totalFlights = 0;
        int totalFlights = airports[i]->getFlightsFrom() + airports[i]->getFlightsTo();
        if (i < k) {
            last_totalFlights = totalFlights;
            res.emplace_back(airports[i]->getInfo(), totalFlights);
        } else if (last_totalFlights == totalFlights) {
            res.emplace_back(airports[i]->getInfo(), totalFlights);
        }
    }
    return res;
}

vector <pair<Airport,int>> Consult::topTrafficCapacityAirports() {
    vector<pair<Airport,int>> res;

    for (const auto v : consultGraph.getVertexSet()) {
        auto airport = v->getInfo();
        int numberFlights = searchNumberOfFlightsOutOfAirport(airport) + searchNumberOfFlightsToAirport(airport);
        res.emplace_back(airport, numberFlights);
    }

    sort(res.begin(), res.end(), [&](const pair<Airport,int>& a1, const pair<Airport,int>& a2) {
        return a1.second > a2.second;
    });

    return res;
}

unordered_set<string> Consult::searchEssentialAirports() {
    unordered_set<string> res;
    stack<string> s;
    int i = 0;

    for (auto v : consultGraph.getVertexSet()) {
        v->setProcessing(false);
        v->setNum(-1);
    }

    for (auto v : consultGraph.getVertexSet()) {
        if (v->getNum() == -1) {
            dfs_articulations(v, s, res, i);
        }
    }

    return res;
}

void Consult::dfs_articulations(Vertex<Airport> *v, stack<string> &s, unordered_set<string> &l, int &i) {
    v->setProcessing(true);
    v->setNum(i);
    v->setLow(i);
    i++;
    s.push(v->getInfo().getCode());

    int children = 0;
    for (auto e : v->getAdj()) {
        auto w = e.getDest();

        if (w->getNum() == -1) {
            children++;
            dfs_articulations(w, s, l, i);
            v->setLow(min(v->getLow(), w->getLow()));

            if (w->getLow() >= v->getNum() && v->getNum() != 0) {
                l.insert(v->getInfo().getCode());
            }
        } else if (w->isProcessing()) {
            v->setLow(min(v->getLow(), w->getNum()));
        }
    }

    v->setProcessing(false);
    s.pop();

    if (v->getNum() == 0 && children > 1) {
        l.insert(v->getInfo().getCode());
    }
}

void Consult::searchMaxTripAndCorrespondingPairsOfAirports() {
    int diameter = 0;
    vector<pair<Airport, Airport>> airportPairs;

    for (const auto& airport : consultGraph.getVertexSet()) {
        unordered_map<Vertex<Airport>*, int> distanceToOtherAirports;
        for (const auto& v : consultGraph.getVertexSet())
            v->setVisited(false);

        distanceToOtherAirports[airport] = 0;

        queue<Vertex<Airport>*> q;
        q.push(airport);
        airport->setVisited(true);

        while (!q.empty()) {
            auto a = q.front();
            q.pop();

            for (const auto& flight : a->getAdj()) {
                auto d = flight.getDest();
                if (!d->isVisited()) {
                    distanceToOtherAirports[d] = distanceToOtherAirports[a] + 1;
                    q.push(d);
                    d->setVisited(true);
                }
            }
        }

        int maxDistance = max_element(distanceToOtherAirports.begin(), distanceToOtherAirports.end(),
                                      [](const auto& p1, const auto& p2) {
                                          return p1.second < p2.second;
        }) -> second;

        if (maxDistance > diameter) {
            diameter = maxDistance;
            airportPairs.clear();
        }

        if (maxDistance == diameter) {
            for (const auto& pair : distanceToOtherAirports) {
                if (pair.second == maxDistance) {
                    airportPairs.emplace_back(airport->getInfo(), pair.first->getInfo());
                }
            }
        }
    }
    cout << "Maximum trip: " << diameter << endl;
    cout << "Pairs of source-destination airports: " << endl;
    for (const auto& pair : airportPairs) {
        cout << "( " << pair.first.getCode() << " -> " << pair.second.getCode() << " )" << endl;
    }
}