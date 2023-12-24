#ifndef AED_AIRPORTS_SCRIPT_H
#define AED_AIRPORTS_SCRIPT_H

#include "Consult.h"
#include "ListAirports.h"

class Script {
public:
    Script(const Graph<Airport>& dataGraph);
    void run();

private:
    struct MenuItem {
        string label;
        void (Script::*action)();
    };

    Consult consult;
    ListAirports listAirports;

    void drawBox(const string& text);
    int showMenu(const string& menuName, const vector<MenuItem>& menuItems);
    void clearScreen();
    void actionGoBack();
    void backToMenu();

    void printAirportInfo(Vertex<Airport>* airport);

    void globalNumber();
    void numberOfAirports();
    void numberOfFlights();
    void numberOfFlightRoutes();

    void flightsOut();
    void flightsOutOfAirport(Vertex<Airport>* airport);

    void flightsPerCity();
    void flightsPerAirline();

    void countriesFlownToFromAirport();
    void countriesFlownToFromCity();

    void destinationsAvailableForAirport();
    void destinationsAvailableWithLayOvers();

    void maximumTrip();
    void topKAirportAirTraffic();
    void essentialAirports();

    void airportStatistics();
    void airportStatisticsByCode();
    void listAirportsByName();

};


#endif //AED_AIRPORTS_SCRIPT_H
