#ifndef AED_AIRPORTS_SCRIPT_H
#define AED_AIRPORTS_SCRIPT_H

#include "Consult.h"

class Script {
public:
    Script(const Graph<Airport>& dataGraph);
    void run();
    bool travelChosen{};
    bool sourceChosen{};
    map<string, vector<Vertex<Airport>*>> travelMap;

private:
    struct MenuItem {
        string label;
        void (Script::*action)();
    };

    Consult consult;

    void drawBox(const string& text);
    int showMenu(const string& menuName, const vector<MenuItem>& menuItems);
    void clearScreen();
    void actionGoBack();
    void backToMenu();

    void printAirportInfo(const Vertex<Airport>* airport);
    void printAirportInfoOneline(const Airport& airport);

    void globalNumber();
    void numberOfAirports();
    void numberOfFlights();
    void numberOfFlightRoutes();

    void flightsPerCity();
    void flightsPerAirline();

    void countriesFlownToFromCity();

    void destinationsAvailableWithLayOvers(Vertex<Airport>* airport);
    void givenAirportStatistics(Vertex<Airport>* airport);

    void maximumTrip();
    void topKAirportAirTraffic();
    void essentialAirports();

    void airportStatistics(Vertex<Airport>* airport);
    void listAndChooseAirport(vector<Vertex<Airport> *> airports, const string& name, const string& typeName);
    void searchAirportsMenu();
    void searchAirportByAirportCode();
    void searchAirportByAirportName();
    void searchAirportByCityName();
    void searchAirportByCountryName();
    void searchClosestAirport();

    void selectSource();
    void selectDestiny();
    void searchAirportByCityAndCountryName();
    void showBestFlight();
};


#endif //AED_AIRPORTS_SCRIPT_H
