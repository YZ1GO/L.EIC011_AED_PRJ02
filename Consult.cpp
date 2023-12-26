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

int Consult::searchNumberOfFlightsOutOfAirport(Vertex<Airport>* airport) {
    return airport->getFlightsFrom();
}

int Consult::searchNumberOfFlightsToAirport(Vertex<Airport>* airport) {
    return airport->getFlightsTo();
}

int Consult::searchNumberOfFlightsOutOfAirportFromDifferentAirlines(Vertex<Airport>* airport) {
    set<Airline> airlines;

    for (const auto& flights : airport->getAdj()) {
        for (const auto& airline : flights.getAirlines()) {
            airlines.insert(airline);
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

    for (auto &flight : v->getAdj()) {
        auto d = flight.getDest();
        if (!d->isVisited())
            dfsVisitFlightsPerCity(d, res);
    }
}

map<Airline, int> Consult::searchNumberOfFlightsPerAirline() {
    map<Airline, int> flightsPerAirline;

    for (auto v : consultGraph.getVertexSet())
        v->setVisited(false);

    for (auto v : consultGraph.getVertexSet())
        if (!v->isVisited())
            dfsVisitFlightsPerAirline(v, flightsPerAirline);

    return flightsPerAirline;
}

void Consult::dfsVisitFlightsPerAirline(Vertex<Airport> *v, map<Airline, int> &res) {
    v->setVisited(true);
    for (const auto& flight : v->getAdj()) {
        for (const auto& airline : flight.getAirlines()) {
            res[airline]++;
        }
    }

    for (auto &flight : v->getAdj()) {
        auto d = flight.getDest();
        if (!d->isVisited())
            dfsVisitFlightsPerAirline(d, res);
    }
}

int Consult::searchNumberOfCountriesFlownToFromAirport(Vertex<Airport>* airport) {
    set<string> countries;

    for (const auto& flight : airport->getAdj()) {
        countries.insert(flight.getDest()->getInfo().getCountry());
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
    if (ToLower(v->getInfo().getCity()) == ToLower(city) && ToLower(v->getInfo().getCountry()) == ToLower(country))
        res.push_back(v);
    for (auto &flight : v->getAdj()) {
        auto d = flight.getDest();
        if (!d->isVisited())
            dfsVisitCityAirports(city, country, d, res);
    }
}

void Consult::dfsAvailableDestinations(Vertex<Airport>* v, std::function<void(Vertex<Airport>*)> processDestination) {
    for (auto& flight : v->getAdj()) {
        auto d = flight.getDest();
        if (!d->isVisited()) {
            d->setVisited(true);
            processDestination(d);
            dfsAvailableDestinations(d, processDestination);
        }
    }
}

int Consult::searchNumberOfAirportsAvailableForAirport(Vertex<Airport>* airport) {
    int numberOfAirports = 0;

    for (auto v : consultGraph.getVertexSet())
        v->setVisited(false);

    auto countAirports = [&numberOfAirports](Vertex<Airport>* v) { numberOfAirports++; };

    dfsAvailableDestinations(airport, countAirports);
    return numberOfAirports;
}

int Consult::searchNumberOfCitiesAvailableForAirport(Vertex<Airport>* airport) {
    set<pair<string, string>> cityAndRespectiveCountry;

    for (auto v : consultGraph.getVertexSet())
        v->setVisited(false);

    auto insertCityAndCountry = [&cityAndRespectiveCountry](Vertex<Airport>* v) {
        cityAndRespectiveCountry.insert({v->getInfo().getCity(), v->getInfo().getCountry()}); };

    dfsAvailableDestinations(airport, insertCityAndCountry);
    return static_cast<int>(cityAndRespectiveCountry.size());
}

int Consult::searchNumberOfCountriesAvailableForAirport(Vertex<Airport>* airport) {
    set<string> countries;

    for (auto v : consultGraph.getVertexSet())
        v->setVisited(false);

    auto insertCountries = [&countries](Vertex<Airport>* v) { countries.insert(v->getInfo().getCountry()); };

    dfsAvailableDestinations(airport, insertCountries);
    return static_cast<int>(countries.size());
}

int Consult::searchNumberOfReachableDestinationsInXStopsFromAirport(Vertex<Airport>* airport, int layOvers, const function<string(Vertex<Airport>*)>& attributeExtractor) {
    queue<pair<Vertex<Airport>*, int>> reachableAirports;
    set<string> reachableDestinations;

    for (auto v: consultGraph.getVertexSet())
        v->setVisited(false);

    reachableAirports.emplace(airport, 0);
    airport->setVisited(true);

    while (!reachableAirports.empty()) {
        auto pair = reachableAirports.front();
        reachableAirports.pop();

        Vertex<Airport>* a = pair.first;
        int stop = pair.second;

        if (stop <= layOvers) {
            for (const auto& flight : a->getAdj()) {
                reachableDestinations.insert(attributeExtractor(flight.getDest()));
            }
        }

        for (auto& flight : a->getAdj()) {
            auto d = flight.getDest();
            if (!d->isVisited()) {
                reachableAirports.emplace(d, stop + 1);
                d->setVisited(true);
            }
        }
    }
    return static_cast<int>(reachableDestinations.size());
}

int Consult::searchNumberOfReachableAirportsInXStopsFromAirport(Vertex<Airport>* airport, int layOvers) {
    function<string(Vertex<Airport>*)> extractAirportCode = [](Vertex<Airport>* airport) { return airport->getInfo().getCode(); };
    return searchNumberOfReachableDestinationsInXStopsFromAirport(airport, layOvers, extractAirportCode);
}

int Consult::searchNumberOfReachableCitiesInXStopsFromAirport(Vertex<Airport>* airport, int layOvers) {
    function<string(Vertex<Airport>*)> extractCity = [](Vertex<Airport>* airport) { return airport->getInfo().getCity(); };
    return searchNumberOfReachableDestinationsInXStopsFromAirport(airport, layOvers, extractCity);
}

int Consult::searchNumberOfReachableCountriesInXStopsFromAirport(Vertex<Airport>* airport, int layOvers) {
    function<string(Vertex<Airport>*)> extractCountry = [](Vertex<Airport>* airport) { return airport->getInfo().getCountry(); };
    return searchNumberOfReachableDestinationsInXStopsFromAirport(airport, layOvers, extractCountry);
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

    for (const auto airport : consultGraph.getVertexSet()) {
        int numberFlights = searchNumberOfFlightsOutOfAirport(airport) + searchNumberOfFlightsToAirport(airport);
        res.emplace_back(airport->getInfo(), numberFlights);
    }

    sort(res.begin(), res.end(), [&](const pair<Airport,int>& a1, const pair<Airport,int>& a2) {
        return a1.second > a2.second;
    });

    return res;
}

unordered_set<string> Consult::searchEssentialAirports() {
    unordered_set<string> essentialAirports;
    stack<string> s;
    int index = 0;
    for (auto v : consultGraph.getVertexSet())
        v->setVisited(false);

    for (auto v : consultGraph.getVertexSet()) {
        if (!v->isVisited()) {
            dfsEssentialAirports(v, s, essentialAirports, index);
        }
    }

    return essentialAirports;
}

void Consult::dfsEssentialAirports(Vertex<Airport> *v, stack<string> &s, unordered_set<string> &res, int &i) {
    v->setVisited(true);
    v->setProcessing(true);
    v->setNum(i);
    v->setLow(i);
    i++;
    s.push(v->getInfo().getCode());
    int children = 0;

    for (auto& flight : v->getAdj()) {
        auto d = flight.getDest();
        if (!d->isVisited()) {
            children++;
            dfsEssentialAirports(d, s, res, i);
            v->setLow(min(v->getLow(), d->getLow()));

            if ((v->getNum() != 0 && d->getLow() >= v->getNum()) || (v->getNum() == 0 && children > 1)) {
                res.insert(v->getInfo().getCode());
            }
        } else if (d->isProcessing()) {
            v->setLow(min(v->getLow(), d->getNum()));
        }
    }
    v->setProcessing(false);
    s.pop();
}

void Consult::searchMaxTripAndCorrespondingPairsOfAirports() {
    int diameter = 0;
    vector<vector<Airport>> airportPaths;

    for (const auto& airport : consultGraph.getVertexSet()) {
        unordered_map<Vertex<Airport>*, int> distanceToOtherAirports;
        unordered_map<Vertex<Airport>*, vector<Airport>> pathToOtherAirports;
        for (const auto& v : consultGraph.getVertexSet())
            v->setVisited(false);

        distanceToOtherAirports[airport] = 0;
        pathToOtherAirports[airport] = {airport->getInfo()};

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
                    pathToOtherAirports[d] = pathToOtherAirports[a];
                    pathToOtherAirports[d].emplace_back(d->getInfo());
                    q.push(d);
                    d->setVisited(true);
                }
            }
        }

        auto distanceASC = [](const auto &p1, const auto &p2) { return p1.second < p2.second; };
        int maxDistance = max_element(distanceToOtherAirports.begin(), distanceToOtherAirports.end(), distanceASC)->second;

        if (maxDistance > diameter) {
            diameter = maxDistance;
            airportPaths.clear();
        }

        if (maxDistance == diameter) {
            for (const auto& pair : distanceToOtherAirports) {
                if (pair.second == maxDistance) {
                    airportPaths.emplace_back(pathToOtherAirports[pair.first]);
                }
            }
        }
    }
    cout << "Maximum trip: " << makeBold(diameter) << endl;
    cout << "Paths of the trip(s): " << endl;
    for (const auto& path : airportPaths) {
        for (size_t i = 0; i < path.size(); ++i) {
            cout << path[i].getCode();
            if (i < path.size() - 1) {
                cout << " -> ";
            }
        }
        cout << endl;
    }
}

vector<vector<Airport>> Consult::searchSmallestPathBetweenAirports(const Airport& source, const Airport& target) {
    auto sourceVertex = consultGraph.findVertex(source);
    auto targetVertex = consultGraph.findVertex(target);

    vector<vector<Airport>> smallestPaths;
    if (sourceVertex == nullptr || targetVertex == nullptr) {
        return smallestPaths;
    }

    for (auto& v : consultGraph.getVertexSet())
        v->setVisited(false);

    queue<pair<vector<Airport>, Vertex<Airport>*>> q;
    q.push({{source}, sourceVertex});
    sourceVertex->setVisited(true);

    int smallestSize = numeric_limits<int>::max();

    while (!q.empty()) {
        auto current = q.front();
        q.pop();

        for (auto& flight : current.second->getAdj()) {
            auto neighbor = flight.getDest();
            if (neighbor == targetVertex) {
                current.first.emplace_back(neighbor->getInfo());

                if (current.first.size() < smallestSize) {
                    smallestPaths.clear();
                    smallestPaths.push_back(current.first);
                    smallestSize = current.first.size();
                } else if (current.first.size() == smallestSize) {
                    smallestPaths.push_back(current.first);
                }
            } else {
                if (!neighbor->isVisited()) {
                    neighbor->setVisited(true);
                    vector<Airport> newPath = current.first;
                    newPath.emplace_back(neighbor->getInfo());
                    q.emplace(newPath, neighbor);
                }
            }
        }
    }
    return smallestPaths;
}