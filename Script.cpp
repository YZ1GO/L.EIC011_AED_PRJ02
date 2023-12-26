#include "Script.h"

Script::Script(const Graph<Airport>& dataGraph) : consult(dataGraph), listAirports(dataGraph) {}

void Script::drawBox(const string &text) {
    int width = text.length() + 4;
    string horizontalLine(width, '-');
    cout << "+" << horizontalLine << "+" << endl;
    cout << "|  " << text << "  |" << endl;
    cout << "+" << horizontalLine << "+" << endl;
}

int Script::showMenu(const string& menuName, const vector<MenuItem>& menuItems) {
    clearScreen();
    drawBox(menuName);
    for (int i = 0; i < menuItems.size(); i++) {
        cout << i + 1 << ". " << menuItems[i].label << endl;
    }

    int choice;
    cout << "\nEnter your choice: ";
    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return 0;  // Invalid choice (not an integer)
    }

    if (choice >= 1 && choice <= menuItems.size()) {
        return choice;
    } else {
        return 0;  // Invalid choice (out of range)
    }
}

void Script::clearScreen() {
    cout << "\033[2J\033[H";
}

void Script::actionGoBack() {
    clearScreen();
}

void Script::backToMenu() {
    cout << "\n";
    cin.get();
    cout << "Press ENTER to continue...";
    cin.get();
}

void Script::printAirportInfo(Vertex<Airport>* airport) {
    auto info = airport->getInfo();
    drawBox("AIRPORT INFORMATION");
    cout << "     Code: " << info.getCode() << endl;
    cout << "     Name: " << info.getName() << endl;
    cout << "     City: " << info.getCity() << endl;
    cout << "  Country: " << info.getCountry() << endl;
    cout << " Location: (" << info.getLocation().latitude << ", " << info.getLocation().longitude << ")" << endl;
    cout << "\n";
}

void Script::run() {
    clearScreen();

    while (true) {
        vector<MenuItem> mainMenu = {
                {makeBold("Statistics"), nullptr},
                {"[Exit]", nullptr}
        };

        int mainChoice = showMenu("MAIN MENU", mainMenu);
        if (mainChoice == 2) {
            break;
        }

        if (mainChoice == 1) {
            while (true) {
                vector<MenuItem> networkStatistics = {
                        {makeBold("Airport Statistics"), &Script::searchAirportsMenu},
                        {makeBold("Global Statistics"), &Script::globalNumber},
                        {"[Back]", nullptr}
                };

                int searchChoice = showMenu("NETWORK STATISTICS", networkStatistics);
                if (searchChoice == 3) {
                    break;  // Go back to the main menu
                }
                if (searchChoice >=1 && searchChoice < 3 && networkStatistics[searchChoice - 1].action != nullptr) {
                    (this->*networkStatistics[searchChoice - 1].action)();
                }
            }
        }
    }
    clearScreen();
    cout << "Goodbye!" << endl;
}

void Script::searchAirportsMenu() {
    vector<MenuItem> statisticsMenu = {
            {makeBold("Search Airport by Code"), &Script::searchAirportByAirportCode},
            {makeBold("Search Airport by Name"), &Script::searchAirportByAirportName},
            {makeBold("Search Airport by City's name"), &Script::searchAirportByCityName},
            {makeBold("Search Airport by Country's name"), &Script::searchAirportByCountryName},
            {makeBold("Search Closest Airport"), &Script::searchClosestAirport},
            {"[Back]", &Script::actionGoBack}
    };

    bool exitSubMenu = false;

    while (!exitSubMenu) {
        clearScreen();
        drawBox("AIRPORT STATISTICS");
        for (int i = 0; i < statisticsMenu.size(); i++) {
            cout << i + 1 << ". " << statisticsMenu[i].label << endl;
        }
        int choice;
        cout << "\nEnter your choice: ";
        if (!(cin >> choice)) {
            // Invalid input (not an integer)
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        clearScreen();
        if (choice == 6) {
            exitSubMenu = true;
        } else if (choice >= 1 && choice <= statisticsMenu.size()) {
            (this->*statisticsMenu[choice - 1].action)();
        }
    }
}

void Script::listAndChooseAirport(vector<Vertex<Airport> *> airports, const string& name, const string& typeName) {
    while (true) {
        clearScreen();
        string title = "Search Airport by " + typeName + "'s name";
        drawBox(title);
        if (typeName == "airport") {
            cout << "Found " << makeBold(airports.size()) << " airport(s) containing " << "\'" << makeBold(name) << "\' in name" << endl;
        }
        if (typeName == "city") {
            cout << "Found " << makeBold(airports.size()) << " airport(s) in " << "\'" << makeBold(name) << "\'" << endl;
        }
        if (typeName == "country") {
            cout << "Found " << makeBold(airports.size()) << " airport(s) in " << "\'" << makeBold(name) << "\'" << endl;
        }

        int i = 1;
        for (auto a : airports) {
            auto info = a->getInfo();
            cout << i++ << ". [" << info.getCode() << "] " << info.getName() << ", " << info.getCity() << ", "
                 << info.getCountry() << endl;
        }

        if (!airports.empty()) {
            cout << i << ". [Back]" << endl;
            int choice;
            cout << "\nEnter your choice: ";
            if (!(cin >> choice)) {
                // Invalid input (not an integer)
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            clearScreen();
            if (choice == airports.size() + 1) {
                break;
            }
            else if (choice <= airports.size()) {
                airportStatistics(airports[choice - 1]);
            }
        }
        else {
            backToMenu();
            cout << "returned"<< endl;
            return;
        }
    }
}

void Script::airportStatistics(Vertex<Airport> *airport) {
    while (true) {
        clearScreen();
        printAirportInfo(airport);

        cout << "1. See reachable destinations in a maximum of X stops" << endl;
        cout << "2. See other statistics" << endl;
        cout << "3. [Back]" << endl;
        cout << "\n";

        int choice;
        cout << "\nEnter your choice: ";
        if (!(cin >> choice)) {
            // Invalid input (not an integer)
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        clearScreen();
        if (choice == 1) {
            destinationsAvailableWithLayOvers(airport);
        } else if (choice == 2) {
            givenAirportStatistics(airport);
        } else if (choice == 3) {
            return;
        }
    }
}

void Script::searchAirportByAirportCode() {
    clearScreen();
    drawBox("Search Airport by airport's code");
    cout << "Enter airport code: ";
    string airportCode;
    cin >> airportCode;
    auto airport = listAirports.findAirportByCode(airportCode);
    clearScreen();
    if (airport != nullptr) {
        airportStatistics(airport);
    }
    else {
        cout << "Airport with code: " << makeBold(airportCode) << " not found!" << endl;
        backToMenu();
    }
}

void Script::searchAirportByAirportName() {
    clearScreen();
    drawBox("Search Airport by airport's name");
    cout << "Enter airport name: ";
    string name;
    cin >> name;
    auto airports = listAirports.findAirportsByAirportName(name);
    listAndChooseAirport(airports, name, "airport");
}

void Script::searchAirportByCityName() {
    clearScreen();
    drawBox("Search Airport by city's name");
    cout << "Enter city name: ";
    string name;
    cin >> name;
    auto airports = listAirports.findAirportsByCityName(name);
    listAndChooseAirport(airports, name, "city");
}

void Script::searchAirportByCountryName() {
    clearScreen();
    drawBox("Search Airport by country's name");
    cout << "Enter country name: ";
    string name;
    cin >> name;
    auto airports = listAirports.findAirportsByCountryName(name);
    listAndChooseAirport(airports, name, "country");
}

void Script::searchClosestAirport() {
    clearScreen();
    drawBox("Search closest Airport");
    double lat, lon;
    cout << "Enter latitude: ";
    cin >> lat;
    cout << "Enter longitude: ";
    cin >> lon;

    Coordinates location;
    location.latitude = lat;
    location.longitude = lon;
    cout << "\n";
    auto airports = listAirports.findClosestAirports(location);
    cout << "Found " << makeBold(airports.size()) << " airport(s) closest to (" << lat << ", " << lon << ")" << endl;
    cout << "\n";
    int i = 1;
    for (auto a : airports) {
        auto info = a->getInfo();
        cout << i++ << ". [" << info.getCode() << "] " << info.getName() << ", " << info.getCity() << ", " << info.getCountry()
        << ", (" << info.getLocation().latitude << "," << info.getLocation().longitude << ")" << endl;
    }
    backToMenu();
}

void Script::destinationsAvailableWithLayOvers(Vertex<Airport>* airport) {
    clearScreen();
    int layOvers;
    cout << "Enter the maximum number of lay-overs: ";
    cin >> layOvers;
    if (layOvers >= 0) {
        clearScreen();
        drawBox("Destinations available with X Lay-Overs");
        cout << "From " << makeBold(airport->getInfo().getCode()) << " in a maximum of " << makeBold(layOvers) << " lay-overs" << endl;
        cout << "\n";
        cout << "Reachable airports: " << makeBold(consult.searchNumberOfReachableAirportsInXStopsFromAirport(airport, layOvers)) << endl;
        cout << "Reachable cities: " << makeBold(consult.searchNumberOfReachableCitiesInXStopsFromAirport(airport, layOvers)) << endl;
        cout << "Reachable countries: " << makeBold(consult.searchNumberOfReachableCountriesInXStopsFromAirport(airport, layOvers)) << endl;
    } else cerr << "ERROR: INVALID NUMBER" << endl;
    backToMenu();
}

void Script::givenAirportStatistics(Vertex<Airport> *airport) {
    clearScreen();
    drawBox("Other Statistics");
    cout << "- Flights out of this airport: " << makeBold(consult.searchNumberOfFlightsOutOfAirport(airport)) << endl;
    cout << "- Flights out of this airport (from different airlines): " << makeBold(consult.searchNumberOfFlightsOutOfAirportFromDifferentAirlines(airport)) << endl;
    cout << "- Number of different countries flown to: " << makeBold(consult.searchNumberOfCountriesFlownToFromAirport(airport)) << endl;
    cout << "- Available airports: " << makeBold(consult.searchNumberOfAirportsAvailableForAirport(airport)) << endl;
    cout << "- Available cities: " << makeBold(consult.searchNumberOfCitiesAvailableForAirport(airport)) << endl;
    cout << "- Available countries: " << makeBold(consult.searchNumberOfCountriesFlownToFromAirport(airport)) << endl;

    backToMenu();
}

void Script::globalNumber() {
    vector<MenuItem> globalMenu = {
            {makeBold("Number of Airports"), &Script::numberOfAirports},
            {makeBold("Number of Flights"), &Script::numberOfFlights},
            {makeBold("Number of Flight Routes"), &Script::numberOfFlightRoutes},
            {"[Back]", &Script::actionGoBack}
    };

    bool exitSubMenu = false;

    while (!exitSubMenu) {
        clearScreen();
        drawBox("GLOBAL STATISTICS");
        for (int i = 0; i < globalMenu.size(); i++) {
            cout << i + 1 << ". " << globalMenu[i].label << endl;
        }
        int choice;
        cout << "\nEnter your choice: ";
        if (!(cin >> choice)) {
            // Invalid input (not an integer)
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        clearScreen();
        if (choice == 4) {
            exitSubMenu = true;
        } else if (choice >= 1 && choice <= globalMenu.size()) {
            (this->*globalMenu[choice - 1].action)();
        }
    }
}

void Script::numberOfAirports() {
    cout << "Global Number of Airports: " << consult.searchNumberOfAirports() << endl;
    backToMenu();
}

void Script::numberOfFlights() {
    cout << "Global Number of Available Flights: " << consult.searchNumberOfAvailableFlights() << endl;
    backToMenu();
}

void Script::numberOfFlightRoutes() {
    cout << "Global Number of Available Flight Routes: " << consult.searchNumberOfAvailableFlightRoutes() << endl;
    backToMenu();
}
