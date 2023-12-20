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
        }

        else if (w->isProcessing()) {
            v->setLow(min(v->getLow(), w->getNum()));
        }
    }

    v->setProcessing(false);
    s.pop();

    if (v->getNum() == 0 && children > 1) {
        l.insert(v->getInfo().getCode());
    }
}

vector <Airport> OConsult::topTrafficCapacityAirports() {
    vector<Airport> res;

    for (const auto v : consultGraph.getVertexSet()) {
        res.push_back(v->getInfo());
    }

    /*
    sort(res.begin(), res.end(), [&](const Airport& a1, const Airport& a2) {
        auto airport1 = consultGraph.findVertex(a1);
        auto airport2 = consultGraph.findVertex(a2);

        //todo
        int traffic1 =
        int traffic2 =

        return traffic1 > traffic2;
    });*/

    return res;
}

vector<Airport> OConsult::searchTopKairportGreatestAirTrafficCapacity(const int& k) {
    vector<Airport> res;
    for (int i = 0; i < topTrafficCapacityAirports().size(); i++) {
        if (i < k) {
            res.push_back(topTrafficCapacityAirports()[i]);
        }
    }

    return res;
}
