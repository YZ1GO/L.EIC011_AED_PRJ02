/**
 * @file
 * @brief Defines the Script class for interacting with the "Air Travel Flight Management System".
 */
#ifndef AED_AIRPORTS_SCRIPT_H
#define AED_AIRPORTS_SCRIPT_H

#include "Consult.h"

/**
 * @class Script
 * @brief Handles the interactive operations for the "Air Travel Flight Management System."
 */
class Script {
public:
    /**
     * @brief Constructor for Script class.
     * @param dataGraph The graph containing airport data for the flight management system.
     */
    Script(const Graph<Airport>& dataGraph);

    /**
     * @brief Initiates the interactive system and displays the main menu.
     * This method serves as the entry point for user interaction.
     */
    void run();
    bool travelChosen{};
    bool sourceChosen{};
    map<string, vector<Vertex<Airport>*>> travelMap;

private:
    /**
     * @struct MenuItem
     * @brief Represents an item in the menu with a label and associated action.
     */
    struct MenuItem {
        string label;               ///< The label or display text for the menu item.
        void (Script::*action)();   ///< The pointer to a member function of the Script class.
    };

    /**
     * @brief Object responsible for handling consultations.
     */
    Consult consult;

    /**
     * @brief Draws a box around the provided text on the screen.
     * @param text The text to be surrounded by a box.
     */
    void drawBox(const string& text);

    /**
     * @brief Displays a menu with the provided items and handles user input.
     * @param menuName The name/title of the menu.
     * @param menuItems The list of MenuItem structures representing the menu items.
     * @return The selected menu item index.
     */
    int showMenu(const string& menuName, const vector<MenuItem>& menuItems);

    /**
     * @brief Clears the screen.
     */
    void clearScreen();

    /**
     * @brief Handles the action for going back in the menu.
     */
    void actionGoBack();

    /**
     * @brief Waits for the user to press the Enter key before returning to the main menu.
     * It prompts the user to press Enter to continue and waits for the input.
     */
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
