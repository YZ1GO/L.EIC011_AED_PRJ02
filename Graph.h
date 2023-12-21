#ifndef AED_AIRPORTS_GRAPH_H
#define AED_AIRPORTS_GRAPH_H

#include "Data.h"
#include <cstddef>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <string>
#include <set>
#include <unordered_map>

using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

/****************** Structures  ********************/

template <class T>
class Vertex {
    T info;
    vector<Edge<T>> adj;
    bool visited;
    bool processing;
    int indegree;
    int outdegree;
    int num;
    int low;
    int flightsTo = 0;
    int flightsFrom = 0;

    void addEdge(Vertex<T> *dest, double distance);
    bool removeEdgeTo(Vertex<T> *d);

public:
    Vertex(T in);

    T getInfo() const;
    void setInfo(T in);

    bool isVisited() const;
    void setVisited(bool v);

    bool isProcessing() const;
    void setProcessing(bool p);

    const vector<Edge<T>> &getAdj() const;
    void setAdj(const vector<Edge<T>> &adj);

    int getIndegree() const;
    void setIndegree(int indegree);
    void addIndegree();

    int getOutdegree() const;
    void setOutdegree(int outdegree);

    int getNum() const;
    void setNum(int num);

    int getLow() const;
    void setLow(int low);

    int getFlightsTo() const;
    void setFlightsTo(int n);

    int getFlightsFrom() const;
    void setFlightsFrom(int n);

    friend class Graph<T>;
};

template <class T>
class Edge {
    Vertex<T>* dest;
    double distance;
    std::set<Airline> airlines;

public:
    Edge(Vertex<T> *d, double distance);

    Vertex<T> *getDest() const;
    void setDest(Vertex<T> *dest);

    const std::set<Airline>& getAirlines() const;
    void addAirline(const Airline& airline);

    double getDistance() const;
    void setDistance(double distance);

    friend class Graph<T>;
    friend class Vertex<T>;
};

template <class T>
class Graph {
    vector<Vertex<T>*> vertexSet;
    int _index_;
    stack<Vertex<T>> _stack_;
    list<list<T>> _list_sccs_;

    void dfsVisit(Vertex<T> *v, vector<T> &res) const;

public:
    void setAllVertexUnivisited();

    Vertex<T> *findVertex(const T &in) const;
    int getNumVertex() const;
    vector<Vertex<T> * > getVertexSet() const;

    bool addVertex(const T &in);
    bool removeVertex(const T &in);

    bool addEdge(const T &source, const T &dest, double distance);
    bool removeEdge(const T &source, const T &dest);

    vector<T> dfs() const;
    vector<T> dfs(const T & source) const;
    vector<T> bfs(const T &source) const;
    vector<T> topsort() const;
};

/****************** Constructors and functions ********************/

template<class T>
Vertex<T>::Vertex(T in): info(in) {}

template<class T>
T Vertex<T>::getInfo() const { return info; }

template<class T>
void Vertex<T>::setInfo(T in) { Vertex::info = in; }

template <class T>
bool Vertex<T>::isVisited() const { return visited; }

template <class T>
void Vertex<T>::setVisited(bool v) { Vertex::visited = v; }

template<class T>
bool Vertex<T>::isProcessing() const { return processing; }

template<class T>
void Vertex<T>::setProcessing(bool p) { Vertex::processing = p; }

template<class T>
const vector<Edge<T>> &Vertex<T>::getAdj() const { return adj; }

template <class T>
void Vertex<T>::setAdj(const vector<Edge<T>> &adj) { Vertex::adj = adj; }

template<class T>
int Vertex<T>::getIndegree() const { return indegree; }

template<class T>
void Vertex<T>::setIndegree(int indegree) { Vertex::indegree = indegree; }

template<class T>
void Vertex<T>::addIndegree() { Vertex::indegree++; }

template<class T>
int Vertex<T>::getOutdegree() const { return outdegree; }

template<class T>
void Vertex<T>::setOutdegree(int outdegree) { Vertex::outdegree = outdegree; }

template<class T>
int Vertex<T>::getNum() const { return num; }

template<class T>
void Vertex<T>::setNum(int num) { Vertex::num = num; }

template<class T>
int Vertex<T>::getLow() const { return low; }

template<class T>
void Vertex<T>::setLow(int low) { Vertex::low = low; }

template<class T>
int Vertex<T>::getFlightsTo() const { return flightsTo; }

template<class T>
void Vertex<T>::setFlightsTo(int n) { flightsTo = n; }

template<class T>
int Vertex<T>::getFlightsFrom() const { return flightsFrom; }

template<class T>
void Vertex<T>::setFlightsFrom(int n) { flightsFrom = n; }

/**************************************************/

template<class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), distance(w) {}

template<class T>
Vertex<T> *Edge<T>::getDest() const { return dest; }

template<class T>
void Edge<T>::setDest(Vertex<T> *d) { Edge::dest = d; }

template<class T>
const std::set<Airline>& Edge<T>::getAirlines() const { return airlines; }

template<class T>
void Edge<T>::addAirline(const Airline& airline) { airlines.insert(airline); }

template<class T>
double Edge<T>::getDistance() const { return distance; }

template<class T>
void Edge<T>::setDistance(double distance) { Edge::distance = distance; }

/**************************************************/

template <class T>
Vertex<T> *Graph<T>::findVertex(const T &in) const {
    for (auto v : vertexSet) {
        if (v->info == in)
            return v;
    }
    return NULL;
}

template <class T>
int Graph<T>::getNumVertex() const { return vertexSet.size(); }

template <class T>
vector<Vertex<T>*> Graph<T>::getVertexSet() const { return vertexSet; }

template <class T>
bool Graph<T>::addVertex(const T &in) {
    if (findVertex(in) != NULL)
        return false;
    vertexSet.push_back(new Vertex<T>(in));
    return true;
}

template <class T>
bool Graph<T>::removeVertex(const T &in) {
    for (auto it = vertexSet.begin(); it != vertexSet.end(); it++)
        if ((*it)->info  == in) {
            auto v = *it;
            vertexSet.erase(it);
            for (auto u : vertexSet)
                u->removeEdgeTo(v);
            delete v;
            return true;
        }
    return false;
}

template <class T>
bool Graph<T>::addEdge(const T &source, const T &dest, double distance) {
    auto v1 = findVertex(source);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    v1->addEdge(v2, distance);
    return true;
}

template <class T>
void Vertex<T>::addEdge(Vertex<T> *d,  double distance) {
    adj.push_back(Edge<T>(d, distance));
}

template <class T>
bool Graph<T>::removeEdge(const T &source, const T &dest) {
    auto v1 = findVertex(source);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    return v1->removeEdgeTo(v2);
}

template <class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {
    for (auto it = adj.begin(); it != adj.end(); it++)
        if (it->dest == d) {
            adj.erase(it);
            return true;
        }
    return false;
}

/****************** DFS ********************/

template <class T>
vector<T> Graph<T>::dfs() const {
    vector<T> res;
    for (auto v : vertexSet)
        v->visited = false;
    for (auto v : vertexSet)
        if (! v->visited)
            dfsVisit(v, res);
    return res;
}

template <class T>
void Graph<T>::dfsVisit(Vertex<T> *v, vector<T> &res) const {
    v->visited = true;
    res.push_back(v->info);
    for (auto &e : v->adj) {
        auto w = e.dest;
        if (!w->visited)
            dfsVisit(w, res);
    }
}

template <class T>
vector<T> Graph<T>::dfs(const T &source) const {
    vector<T> res;
    auto s = findVertex(source);
    if (s == nullptr)
        return res;

    for (auto v : vertexSet)
        v->visited = false;

    dfsVisit(s, res);
    return res;
}

/****************** BFS ********************/

template <class T>
vector<T> Graph<T>::bfs(const T &source) const {
    vector<T> res;
    auto s = findVertex(source);
    if (s == NULL)
        return res;
    queue<Vertex<T> *> q;
    for (auto v : vertexSet)
        v->visited = false;
    q.push(s);
    s->visited = true;
    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        res.push_back(v->info);
        for (auto & e : v->adj) {
            auto w = e.dest;
            if ( ! w->visited ) {
                q.push(w);
                w->visited = true;
            }
        }
    }
    return res;
}

/****************** topsort ********************/

template<class T>
vector<T> Graph<T>::topsort() const {
    vector<T> res;
    queue<Vertex<T>> q;

    for (auto v : vertexSet)
        v->indegree = 0;
    for (auto v : vertexSet) {
        for (auto &e : v->getAdj()) {
            auto d = e.dest;
            d->indegree++;
        }
    }

    for (auto v : vertexSet) {
        if (v->indegree == 0)
            q.push(*v);
    }

    while (!q.empty()) {
        auto vertex = q.front();
        for (auto &e : vertex.getAdj()) {
            e.dest->indegree--;
            if (e.dest->indegree == 0)
                q.push(*e.dest);
        }
        q.pop();
        res.push_back(vertex.getInfo());
    }
    return res;
}

#endif //AED_AIRPORTS_GRAPH_H