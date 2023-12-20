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
