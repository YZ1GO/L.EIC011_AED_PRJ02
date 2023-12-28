#include "Script.h"

Script::Script(const Graph<Airport>& dataGraph) : consult(dataGraph), travelChosen(false), sourceChosen(false), travelMap() {}

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

void Script::printAirportInfo(const Vertex<Airport>* airport) {
    auto info = airport->getInfo();
    drawBox("AIRPORT INFORMATION");
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
                {makeBold("Travel"), nullptr},
                {"[Exit]", nullptr}
        };

        int mainChoice = showMenu("MAIN MENU", mainMenu);
        if (mainChoice == 3) {
            break;
        }

        if (mainChoice == 1) {
            while (true) {
                vector<MenuItem> networkStatistics = {
                        {makeBold("Global Statistics"), &Script::globalNumber},
                        {makeBold("Airport Statistics"), &Script::searchAirportsMenu},
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
        } else if (mainChoice == 2) {
            while (true) {
                vector<MenuItem> travelMenu = {
                        {makeBold("Best flight option"), &Script::selectSource},
                        {"[Back]", nullptr}
                };

                int searchChoice = showMenu("TRAVEL MENU", travelMenu);
                if (searchChoice == 2) {
                    travelChosen = false;
                    break;  // Go back to the main menu
                }
                if (searchChoice >=1 && searchChoice < 3 && travelMenu[searchChoice - 1].action != nullptr) {
                    (this->*travelMenu[searchChoice - 1].action)();
                }
            }
        }
    }
    clearScreen();
    cout << "Goodbye!" << endl;
}

void Script::searchAirportsMenu() {
    vector<MenuItem> searchAirport = {
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
        drawBox("SEARCH");
        for (int i = 0; i < searchAirport.size(); i++) {
            cout << i + 1 << ". " << searchAirport[i].label << endl;
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
        } else if (choice >= 1 && choice <= searchAirport.size()) {
            (this->*searchAirport[choice - 1].action)();
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
        cout << "\n";

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
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            clearScreen();
            if (choice == airports.size() + 1) {
                return;
            }
            else if (choice <= airports.size() && choice > 0) {
                airportStatistics(airports[choice - 1]);
            }
        } else {
            backToMenu();
            return;
        }
    }
}

void Script::airportStatistics(Vertex<Airport> *airport) {
    while (true) {
        clearScreen();
        printAirportInfo(airport);

        if (travelChosen) {
            if (!sourceChosen) {
                cout << "0. Set airport as source" << endl;
            } else {
                cout << "0. Set airport as destination" << endl;
            }
        }
        cout << "1. See airport statistics" << endl;
        cout << "2. See reachable destinations in a maximum of X stops" << endl;
        cout << "3. [Back]" << endl;

        int choice;
        cout << "\nEnter your choice: ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        clearScreen();
        if (choice == 3) {
            if (sourceChosen) travelMap.clear();
            return;
        } else if (choice == 0 && travelChosen) {
            if (!sourceChosen) {
                cityChosenSource = false;
                travelMap["source"].push_back(airport);
                selectDestiny();
            }
            else {
                cityChosenDestiny = false;
                travelMap["destination"].push_back(airport);
                showBestFlight();
            }
        } else if (choice == 1) {
            givenAirportStatistics(airport);
        } else if (choice == 2) {
            destinationsAvailableWithLayOvers(airport);
        }
    }
}

void Script::searchAirportByAirportCode() {
    clearScreen();
    drawBox("Find airport by airport's code");

    cout << "Enter airport code: ";
    string airportCode;
    cin >> airportCode;

    auto airport = consult.findAirportByCode(airportCode);

    clearScreen();
    if (airport != nullptr) {
        airportStatistics(airport);
    } else {
        cerr << "ERROR: Airport with code: " << makeBold(airportCode) << " not found!" << endl;
        backToMenu();
    }
}

void Script::searchAirportByAirportName() {
    clearScreen();
    drawBox("Search airport by airport's name");

    cout << "Enter airport name: ";
    string name;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, name);

    auto airports = consult.findAirportsByAirportName(name);
    listAndChooseAirport(airports, name, "airport");
}

void Script::searchAirportByCityName() {
    clearScreen();
    drawBox("Search airport by city's name");

    cout << "Enter city name: ";
    string name;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, name);

    auto airports = consult.findAirportsByCityName(name);
    listAndChooseAirport(airports, name, "city");
}

void Script::searchAirportByCountryName() {
    clearScreen();
    drawBox("Search airport by country's name");

    cout << "Enter country name: ";
    string name;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, name);
    cout << "\n";

    auto airports = consult.findAirportsByCountryName(name);
    listAndChooseAirport(airports, name, "country");
}

void Script::searchClosestAirport() {
    while (true) {
        clearScreen();
        drawBox("Search closest Airport");

        double lat, lon;
        cout << "Enter latitude: ";
        cin >> lat;
        cout << "Enter longitude: ";
        cin >> lon;
        cout << "\n";

        if (lat < -90.0 || lat > 90.0 || lon < -180.0 || lon > 180.0) {
            cerr << "ERROR: Invalid coordinates, please enter valid values (latitude: -90.0 ~ 90.0, longitude: -180.0 ~ 180.0)" << endl;
            backToMenu();
        } else {
            Coordinates location;
            location.latitude = lat;
            location.longitude = lon;

            auto airports = consult.findClosestAirports(location);
            cout << "Found " << makeBold(airports.size()) << " airport(s) closest to (" << lat << ", " << lon << ")\n" << endl;

            int index = 1;
            for (auto a : airports) {
                auto info = a->getInfo();
                cout << index++ << ". ";
                printAirportInfoOneline(info);
            }
            cout << index << ". [Back]\n" << endl;

            int choice;
            cout << "Enter your choice: ";
            cin >> choice;
            if (choice == airports.size() + 1) {
                if (sourceChosen) travelMap.clear();
                return;
            } else if (choice <= airports.size() && choice > 0) {
                airportStatistics(airports[choice - 1]);
            }
        }
    }
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
    } else cerr << "ERROR: Invalid number" << endl;
    backToMenu();
}

void Script::givenAirportStatistics(Vertex<Airport> *airport) {
    clearScreen();
    string str = airport->getInfo().getCode() + " Statistics";
    drawBox(str);

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
        drawBox("GLOBAL STATISTICS");
        for (int i = 0; i < globalStatistics.size(); i++) {
            cout << i + 1 << ". " << globalStatistics[i].label << endl;
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
        if (choice == 10) {
            exitSubMenu = true;
        } else if (choice >= 1 && choice <= globalStatistics.size()) {
            (this->*globalStatistics[choice - 1].action)();
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

void Script::flightsPerCity() {
    drawBox("Flights per city");
    int index = 1;
    for (const auto& pair : consult.searchNumberOfFlightsPerCity()) {
        cout << index++ << ". [" << pair.second << "] " << pair.first.first << ", " << pair.first.second << endl;
    }
    backToMenu();
}

void Script::flightsPerAirline() {
    drawBox("Flights per airline");
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
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, city);
    cout << "Enter the country name: ";
    getline(cin, country);
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

    int diameter;
    auto airportPaths = consult.searchMaxTripAndCorrespondingPairsOfAirports(diameter);
    drawBox("Maximum Trip");
    cout << "Maximum trip: " << makeBold(diameter) << endl;
    cout << "Paths of the trip(s): " << endl;
    for (const auto& path : airportPaths) {
        for (size_t i = 0; i < path.size(); ++i) {
            cout << path[i]->getInfo().getCode();
            if (i < path.size() - 1) {
                cout << " \u25B6 ";
            }
        }
        cout << endl;
    }

    backToMenu();
}

void Script::topKAirportAirTraffic() {
    cout << "Enter the desired number of airports to display: ";
    int k;
    cin >> k;
    if (k < 1 || k > consult.searchNumberOfAirports()) {
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

void Script::selectSource() {
    travelChosen = true;
    vector<MenuItem> selectSource = {
            {makeBold("Airport by Code"), &Script::searchAirportByAirportCode},
            {makeBold("Airport by Name"), &Script::searchAirportByAirportName},
            {makeBold("City"), &Script::searchAirportByCityAndCountryName},
            {makeBold("Coordinates"), &Script::searchClosestAirport},
            {"[Back]", &Script::actionGoBack}
    };

    bool exitSubMenu = false;

    while (!exitSubMenu) {
        travelMap.clear();
        clearScreen();
        drawBox("SELECT FLIGHT SOURCE");
        for (int i = 0; i < selectSource.size(); i++) {
            cout << i + 1 << ". " << selectSource[i].label << endl;
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
        if (choice == 5) {
            exitSubMenu = true;
        } else if (choice >= 1 && choice <= selectSource.size()) {
            (this->*selectSource[choice - 1].action)();
        }
    }
}

void Script::selectDestiny() {
    sourceChosen = true;
    vector<MenuItem> destiny = {
            {makeBold("Airport by Code"), &Script::searchAirportByAirportCode},
            {makeBold("Airport by Name"), &Script::searchAirportByAirportName},
            {makeBold("City"), &Script::searchAirportByCityAndCountryName},
            {makeBold("Coordinates"), &Script::searchClosestAirport},
            {"[Back]", &Script::actionGoBack}
    };

    bool exitSubMenu = false;

    while (!exitSubMenu) {
        clearScreen();
        drawBox("SELECT FLIGHT DESTINATION");

        auto it = travelMap.find("source");
        cout << makeBold("Source: ");
        if (cityChosenSource) {
            cout << it->second[0]->getInfo().getCity() << ", " << it->second[0]->getInfo().getCountry() << endl;
        } else {
            printAirportInfoOneline(it->second[0]->getInfo());
        }
        cout << "\n";

        for (int i = 0; i < destiny.size(); i++) {
            cout << i + 1 << ". " << destiny[i].label << endl;
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
        if (choice == 5) {
            sourceChosen = false;
            exitSubMenu = true;
        } else if (choice >= 1 && choice <= destiny.size()) {
            (this->*destiny[choice - 1].action)();
        }
    }
}

void Script::searchAirportByCityAndCountryName() {
    drawBox("Search by city");

    string city, country;
    cout << "Enter city name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, city);
    cout << "Enter country name: ";
    getline(cin, country);

    auto airports = consult.getAirportsInACityAndCountry(city, country);

    if (airports.empty()) {
        cerr << "\nERROR: Invalid city/country name" << endl;
        backToMenu();
    } else {
        while (true) {
            cout << "\nFound " << makeBold(airports.size()) << " airport(s) in " << city << ", " << country << "\n" << endl;

            if (!sourceChosen) {
                cout << "0. Set this city and country as source" << endl;
            } else {
                cout << "0. Set this city and country as destination" << endl;
            }

            int index = 1;
            for (auto& airport : airports) {
                auto info = airport->getInfo();
                cout << index++ << ". [" << info.getCode() << "] " << info.getName() << ", " << info.getCity() << ", "
                     << info.getCountry() << endl;
            }
            cout << index << ". [Back]" << endl;

            int choice;
            cout << "\nEnter your choice: ";
            if (!(cin >> choice)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            clearScreen();
            cityChosenSource = false;
            cityChosenDestiny = false;
            if (choice == 0) {
                if (!sourceChosen) {
                    cityChosenSource = true;
                    travelMap["source"] = airports;
                    selectDestiny();
                }
                else {
                    cityChosenDestiny = true;
                    travelMap["destination"] = airports;
                    showBestFlight();
                }
            } else if (choice == airports.size() + 1) {
                if (sourceChosen) travelMap.clear();
                break;
            } else if (choice <= airports.size() && choice > 0) {
                airportStatistics(airports[choice - 1]);
            }
        }
    }
}

void Script::showBestFlight() {
    clearScreen();
    if (travelMap["source"].empty() || travelMap["destination"].empty()) {
        cerr << "\nERROR: Failure in finding flight" << endl;
        backToMenu();
    } else {
        while (true) {
            clearScreen();
            drawBox("Best Flights");
            auto source = travelMap.find("source");
            auto destination = travelMap.find("destination");

            cout << makeBold("Source: ");
            if (cityChosenSource) {
                cout << source->second[0]->getInfo().getCity() << ", " << source->second[0]->getInfo().getCountry() << endl;
            } else {
                printAirportInfoOneline(source->second[0]->getInfo());
            }

            cout << makeBold("Destination: ");
            if (cityChosenDestiny) {
                cout << destination->second[0]->getInfo().getCity() << ", " << destination->second[0]->getInfo().getCountry() << endl;
            } else {
                printAirportInfoOneline(destination->second[0]->getInfo());
            }

            vector<pair<vector<Vertex<Airport>*>, double>> totalPaths; // Pair of path and distance
            int minLayOvers = numeric_limits<int>::max();

            for (auto sourceAirport : source->second) {
                for (auto destinationAirport : destination->second) {
                    vector<vector<Vertex<Airport>*>> paths = consult.searchSmallestPathBetweenAirports(sourceAirport, destinationAirport);

                    for (auto v : paths) {
                        int currentLayOvers = v.size() - 2;

                        if (currentLayOvers < minLayOvers) {
                            minLayOvers = currentLayOvers;
                            totalPaths.clear();
                        }
                        if (currentLayOvers == minLayOvers) {
                            double distance = 0.0;
                            auto it = v.begin();
                            while (it != v.end() - 1) {
                                distance += consult.getDistanceBetweenAirports(*it, *(it + 1));
                                ++it;
                            }
                            totalPaths.emplace_back( v, distance );
                        }
                    }
                }
            }

            sort(totalPaths.begin(), totalPaths.end(), [](const pair<vector<Vertex<Airport>*>, double>& a, const pair<vector<Vertex<Airport>*>, double>& b) {
                return a.second < b.second;
            });

            cout << "\nBest flight is with " << makeBold(totalPaths[0].first.size() - 2) << " lay-over(s)" << endl;
            int index = 1;
            for (const auto& trip : totalPaths) {
                cout << index++ << ". ";

                double distance = trip.second;
                for (auto it = trip.first.begin(); it != trip.first.end(); ++it) {
                    cout << (*it)->getInfo().getCode();
                    if (next(it) != trip.first.end()) {
                        cout << " \u25B6 ";
                    }
                }
                cout << "   (" << distance << " km)" << endl;
            }
            cout << index << ". [Back]" << endl;
            int choice;
            cout << "\nEnter your choice: ";
            cin >> choice;
            cout << "\n";
            if (choice == index) {
                travelMap.clear();
                sourceChosen = false;
                return; // need to make it return to travel menu
            } else if (choice <= index && choice > 0) {
                printBestFlightDetail(totalPaths[choice - 1]);
            }
        }
    }
}

void Script::printBestFlightDetail(pair<vector<Vertex<Airport>*>,double> trip) {
    clearScreen();
    drawBox("Details about the trip");
    cout << makeBold("Total distance: ") << trip.second << " km\n"<< endl;

    auto itr = trip.first.begin();
    int index = 1;
    while (itr != trip.first.end()) {
        cout << index++ << ". ";
        printAirportInfoOneline((*itr)->getInfo());

        if (itr + 1 != trip.first.end()) {
            cout << "   [Available Airlines]: ";
            auto airlines = consult.airlinesThatOperateBetweenAirports(*itr, *(itr + 1));

            for (auto it = airlines.begin(); it != airlines.end(); ++it) {
                cout << it->getCode();
                if (next(it) != airlines.end()) {
                    cout << ", ";
                } else {
                    cout << endl;
                }
            }
        }
        if (next(itr) != trip.first.end()) {
            cout << "             \u25BC" << endl;
        }
        itr++;
    }
    cout << endl;
    backToMenu();
}

