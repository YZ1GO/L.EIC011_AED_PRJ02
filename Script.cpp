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
    cout << "Enter your choice: ";
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
    cout << "     Code: " << info.getCode() << endl;
    cout << "     Name: " << info.getName() << endl;
    cout << "     City: " << info.getCity() << endl;
    cout << "  Country: " << info.getCountry() << endl;
    cout << " Location: (" << info.getLocation().latitude << ", " << info.getLocation().longitude << ")" << endl;
    cout << "\n";
}

void Script::printAirportInfoOneline(const Airport& airport) {
    cout << airport.getCode() << ", " << airport.getName() << ", " << airport.getCity() << ", " << airport.getCountry()
    << ", (" << airport.getLocation().latitude << "," << airport.getLocation().longitude << ")" << endl;
}

void Script::run() {
    clearScreen();

    while (true) {
        vector<MenuItem> mainMenu = {
                {makeBold("Statistics"), nullptr},
                {"[Exit]", nullptr}
        };

        int mainChoice = showMenu("Main Menu", mainMenu);
        if (mainChoice == 2) {
            break;
        }

        if (mainChoice == 1) {
            while (true) {
                vector<MenuItem> networkStatistics = {
                        {makeBold("Global Statistics"), &Script::globalNumber},
                        {makeBold("Airport Statistics"), &Script::airportStatistics},
                        {"[Back]", nullptr}
                };

                int searchChoice = showMenu("Network Statistics", networkStatistics);
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

void Script::airportStatistics() {
    vector<MenuItem> airportStatistics = {
            {makeBold("Find airport by code"), &Script::airportStatisticsByCode},
            {makeBold("Search airport by name"), &Script::listAirportsByName},
            {makeBold("Search closest airport"), &Script::listClosestAirports},
            {"[Back]", &Script::actionGoBack}
    };

    bool exitSubMenu = false;

    while (!exitSubMenu) {
        clearScreen();
        drawBox("Airport Statistics");
        for (int i = 0; i < airportStatistics.size(); i++) {
            cout << i + 1 << ". " << airportStatistics[i].label << endl;
        }
        int choice;
        cout << "Enter your choice: ";
        if (!(cin >> choice)) {
            // Invalid input (not an integer)
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        clearScreen();
        if (choice == 4) {
            exitSubMenu = true;
        } else if (choice >= 1 && choice <= airportStatistics.size()) {
            (this->*airportStatistics[choice - 1].action)();
        }
    }
}

void Script::airportStatisticsByCode() {
    clearScreen();
    cout << "Enter airport code: ";
    string airportCode;
    cin >> airportCode;
    auto airport = listAirports.findAirportByCode(airportCode);
    clearScreen();
    if (airport != nullptr) {
        while (true) {
            printAirportInfo(airport);

            cout << "1. See airport statistics" << endl;
            cout << "2. Find reachable destinations in a maximum of X stops" << endl;
            cout << "3. [Back]" << endl;
            cout << "\n";

            int choice;
            cout << "Enter your choice: ";
            if (!(cin >> choice)) {
                // Invalid input (not an integer)
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            clearScreen();
            if (choice == 1) {
                givenAirportStatistics(airport);
            } else if (choice == 2) {
                destinationsAvailableWithLayOvers(airport);
            } else if (choice == 3) {
                return;
            }
        }
    }
    else {
        cerr << "ERROR: Airport with code: " << makeBold(airportCode) << " not found!" << endl;
    }
    backToMenu();
}

void Script::listAirportsByName() {
    clearScreen();
    drawBox("Search airports");
    cout << "1. By airport name" << endl;
    cout << "2. By city name" << endl;
    cout << "3. By country name" << endl;
    cout << "4. [Back]" << endl;
    cout << "\n";
    cout << "Enter your choice: ";
    int choice;
    int index = 1;
    cin >> choice;
    if (choice == 1) {
        clearScreen();
        cout << "Enter airport name: ";
        string name;
        cin >> name;
        auto airports = listAirports.findAirportsByAirportName(name);
        cout << "Found " << makeBold(airports.size()) << " airport(s) containing " << "\'" << makeBold(name) << "\' in name: " << endl;
        cout << "\n";
        for (auto a : airports) {
            auto info = a->getInfo();
            cout << index++ << ". ";
            printAirportInfoOneline(info);
        }
    } else if (choice == 2) {
        clearScreen();
        cout << "Enter city name: ";
        string name;
        cin >> name;
        auto airports = listAirports.findAirportsByCityName(name);
        cout << "Found " << makeBold(airports.size()) << " airport(s) in " << "\'" << makeBold(name) << "\': " << endl;
        cout << "\n";
        for (auto a : airports) {
            auto info = a->getInfo();
            cout << index++ << ". ";
            printAirportInfoOneline(info);
        }
    } else if (choice == 3) {
        clearScreen();
        cout << "Enter country name: ";
        string name;
        cin >> name;
        auto airports = listAirports.findAirportsByCountryName(name);
        cout << "Found " << makeBold(airports.size()) << " airport(s) in " << "\'" << makeBold(name) << "\': " << endl;
        cout << "\n";
        for (auto a : airports) {
            auto info = a->getInfo();
            cout << index++ << ". ";
            printAirportInfoOneline(info);
        }
    } else if (choice == 4) {
        return;
    }
    backToMenu();
}

void Script::listClosestAirports() {
    clearScreen();
    double lat, lon;
    cout << "Enter latitude: ";
    cin >> lat;
    cout << "Enter longitude: ";
    cin >> lon;
    cout << "\n";

    if (lat < -90.0 || lat > 90.0 || lon < -180.0 || lon > 180.0) {
        cerr << "ERROR: Invalid coordinates, please enter valid values (latitude: -90.0 ~ 90.0, longitude: -180.0 ~ 180.0)" << endl;
    } else {
        Coordinates location;
        location.latitude = lat;
        location.longitude = lon;
        auto airports = listAirports.findClosestAirports(location);
        cout << "Found " << makeBold(airports.size()) << " airport(s) closest to (" << lat << ", " << lon << ")" << endl;
        cout << "\n";
        int i = 1;
        for (auto a : airports) {
            auto info = a->getInfo();
            cout << i++ << ". ";
            printAirportInfoOneline(info);
        }
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
        cout << "From " << makeBold(airport->getInfo().getCode()) << " in a maximum of " << makeBold(layOvers) << " lay-overs" << endl;
        cout << "\n";
        cout << "Reachable airports: " << makeBold(consult.searchNumberOfReachableAirportsInXStopsFromAirport(airport, layOvers)) << endl;
        cout << "Reachable cities: " << makeBold(consult.searchNumberOfReachableCitiesInXStopsFromAirport(airport, layOvers)) << endl;
        cout << "Reachable countries: " << makeBold(consult.searchNumberOfReachableCountriesInXStopsFromAirport(airport, layOvers)) << endl;
    } else cerr << "ERROR: Invalid number" << endl;
    backToMenu();
}

void Script::givenAirportStatistics(Vertex<Airport> *airport) {
    clearScreen();
    cout << "- Flight routes out of this airport: " << makeBold(airport->getAdj().size()) << endl;
    cout << "- Flights out of this airport: " << makeBold(consult.searchNumberOfFlightsOutOfAirport(airport)) << endl;
    cout << "- Flights out of this airport (from different airlines): " << makeBold(consult.searchNumberOfFlightsOutOfAirportFromDifferentAirlines(airport)) << endl;
    cout << "- Number of different countries flown to: " << makeBold(consult.searchNumberOfCountriesFlownToFromAirport(airport)) << endl;
    cout << "- Available airports: " << makeBold(consult.searchNumberOfAirportsAvailableForAirport(airport)) << endl;
    cout << "- Available cities: " << makeBold(consult.searchNumberOfCitiesAvailableForAirport(airport)) << endl;
    cout << "- Available countries: " << makeBold(consult.searchNumberOfCountriesAvailableForAirport(airport)) << endl;

    backToMenu();
}

void Script::globalNumber() {
    vector<MenuItem> globalStatistics = {
            {makeBold("Airports"), &Script::numberOfAirports},
            {makeBold("Flights"), &Script::numberOfFlights},
            {makeBold("Flight routes"), &Script::numberOfFlightRoutes},
            {makeBold("Number of flights per city"), &Script::flightsPerCity},
            {makeBold("Number of flights per airline"), &Script::flightsPerAirline},
            {makeBold("Number of different countries that a given city flies to"), &Script::countriesFlownToFromCity},
            {makeBold("Maximum trip"), &Script::maximumTrip},
            {makeBold("Top airports with greatest air traffic capacity"), &Script::topKAirportAirTraffic},
            {makeBold("Essential airports"), &Script::essentialAirports},
            {"[Back]", &Script::actionGoBack}
    };

    bool exitSubMenu = false;

    while (!exitSubMenu) {
        clearScreen();
        drawBox("Global Statistics");
        for (int i = 0; i < globalStatistics.size(); i++) {
            cout << i + 1 << ". " << globalStatistics[i].label << endl;
        }
        int choice;
        cout << "Enter your choice: ";
        if (!(cin >> choice)) {
            // Invalid input (not an integer)
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        clearScreen();
        if (choice == 10) {
            exitSubMenu = true;
        } else if (choice >= 1 && choice <= globalStatistics.size()) {
            (this->*globalStatistics[choice - 1].action)();
        }
    }
}

void Script::numberOfAirports() {
    cout << "Global number of airports: " << makeBold(consult.searchNumberOfAirports()) << endl;
    backToMenu();
}

void Script::numberOfFlights() {
    cout << "Global number of available flights: " << makeBold(consult.searchNumberOfAvailableFlights()) << endl;
    backToMenu();
}

void Script::numberOfFlightRoutes() {
    cout << "Global number of available flight routes: " << makeBold(consult.searchNumberOfAvailableFlightRoutes()) << endl;
    backToMenu();
}

void Script::flightsPerCity() {
    int index = 1;
    for (const auto& pair : consult.searchNumberOfFlightsPerCity()) {
        cout << index++ << ". [" << pair.second << "] " << pair.first << endl;
    }
    backToMenu();
}

void Script::flightsPerAirline() {
    int index = 1;
    for (const auto& pair : consult.searchNumberOfFlightsPerAirline()) {
        auto airline = pair.first;
        cout << index++ << ". [" << pair.second << "] " <<
        airline.getCode() << ", " << airline.getName() << ", " << airline.getCallsign() << ", " << airline.getCountry() << endl;
    }
    backToMenu();
}

void Script::countriesFlownToFromCity() {
    string city, country;
    cout << "Enter the city name: ";
    cin >> city;
    cout << "Enter the country name: ";
    cin >> country;
    cout << "\n";
    int x = consult.searchNumberOfCountriesFlownToFromCity(city, country);
    if (x == 0) {
        cerr << "ERROR: Invalid city/country name" << endl;
    } else cout << "You can fly to " << makeBold(x) << " different countries from " << city << ", " << country << endl;
    backToMenu();
}

void Script::maximumTrip() {
    cout << "Processing..." << endl;
    cout << "Please wait a few seconds..." << endl;
    consult.searchMaxTripAndCorrespondingPairsOfAirports();
    backToMenu();
}

void Script::topKAirportAirTraffic() {
    cout << "Enter the desired number of airports to display: ";
    int k;
    cin >> k;
    if (k < 1 || k > 3019) {
        cerr << "ERROR: Invalid number" << endl;
    } else {
        int index = 1;
        for (const auto& pair : consult.searchTopKAirportGreatestAirTrafficCapacity(k)) {
            auto airport = pair.first;
            cout << index++ << ". [" << pair.second << "] ";
            printAirportInfoOneline(airport);
        }
        cout << "\n";
        cout << makeBold("NOTE:") << " The number inside the brackets indicates the total count of flights departing from and arriving at that airport." << endl;
    }
    backToMenu();
}

void Script::essentialAirports() {
    clearScreen();
    auto airports = consult.searchEssentialAirports();
    cout << "There are " << makeBold(airports.size()) << " essential airports to the network's circulation capacity" << endl;
    int index = 1;
    for (const auto& airport : airports) {
        cout << index++ << ". " << airport << endl;
    }
    backToMenu();
}