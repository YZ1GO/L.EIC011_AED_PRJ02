#include "OConsult.h"

using namespace std;

OConsult::OConsult(const Graph<Airport> &dataGraph) : consultGraph(dataGraph) {};

unordered_set<string> OConsult::searchEssentialAirports() {
    unordered_set<string> res;
    stack<string> s;
    int i = 0;

    for (auto v : consultGraph.getVertexSet()) {
        v->setProcessing(false);
        v->setNum(-1);
    }

    for (auto v : consultGraph.getVertexSet()) {
        if (v->getNum() == -1) {
            dfs_art(v, s, res, i);
        }
    }

    return res;
}

void OConsult::dfs_art(Vertex<Airport> *v, stack<string> &s, unordered_set<string> &l, int &i) {
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
            dfs_art(w, s, l, i);
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

vector <pair<Airport,int>> OConsult::topTrafficCapacityAirports() {
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

vector<pair<Airport,int>> OConsult::searchTopKairportGreatestAirTrafficCapacity(const int& k) {
    vector<pair<Airport,int>> res;
    vector<Vertex<Airport>*> airports;
    for (const auto& airport : consultGraph.getVertexSet()) {
        airports.push_back(airport);
    }

    sort(airports.begin(), airports.end(), [&](const Vertex<Airport>* a1, const Vertex<Airport>* a2) {
        return a1->getFlightsTo() + a1->getFlightsFrom() > a2->getFlightsTo() + a2->getFlightsFrom();
    });

    for (int i = 0; i < airports.size(); i++) {
        int last_totalFlights;
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

int OConsult::searchNumberOfFlightsOutOfAirport(const Airport& airport) {
    int numberOfFlights = 0;

    auto a = consultGraph.findVertex(airport);
    if (a != nullptr) {
        for (const auto& flights : a->getAdj()) {
            numberOfFlights += flights.getAirlines().size();
        }
    }
    return numberOfFlights;
}

int OConsult::searchNumberOfFlightsToAirport(const Airport& targetAirport) {
    int numberOfFlights = 0;

    auto a = consultGraph.findVertex(targetAirport);
    if (a != nullptr) {
        for (const auto& airport : consultGraph.getVertexSet()) {
            for (const auto& flight : airport->getAdj()) {
                auto target = flight.getDest();
                if (target->getInfo() == targetAirport) {
                    numberOfFlights += flight.getAirlines().size();
                }
            }
        }
    }
    return numberOfFlights;
}