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

void Script::run() {
    clearScreen();

    while (true) {
        vector<MenuItem> mainMenu = {
                {"\033[1mStatistics\033[0m", nullptr},
                {"\033[1mChange\033[0m", nullptr},
                {"[Exit]", nullptr}
        };

        int mainChoice = showMenu("Main Menu", mainMenu);
        if (mainChoice == 3) {
            break;
        }

        if (mainChoice == 1) {
            while (true) {
                vector<MenuItem> networkStatistics = {
                        {"\033[1mAirport Statistics\033[0m", &Script::airportStatistics},
                        {"\033[1mGlobal Statistics\033[0m", &Script::globalNumber},
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
    vector<MenuItem> statisticsMenu = {
            {"\033[1mFind Airport By Code\033[0m", &Script::airportStatisticsByCode},
            //{"\033[1mSearch Airport By Airport Name\033[0m", &Script::numberOfFlights},
            //{"\033[1mSearch Airport By City Name\033[0m", &Script::numberOfFlightRoutes},
            //{"\033[1mSearch Airport By Country Name\033[0m", &Script::numberOfFlightRoutes},
            {"[Back]", &Script::actionGoBack}
    };

    bool exitSubMenu = false;

    while (!exitSubMenu) {
        clearScreen();
        drawBox("Statistics Menu");
        for (int i = 0; i < statisticsMenu.size(); i++) {
            cout << i + 1 << ". " << statisticsMenu[i].label << endl;
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
        if (choice == 5) {
            exitSubMenu = true;
        } else if (choice >= 1 && choice <= statisticsMenu.size()) {
            (this->*statisticsMenu[choice - 1].action)();
        }
    }
}

void Script::airportStatisticsByCode() {
    cout << "Enter airport code: ";
    string airportCode;
    cin >> airportCode;
    auto a = listAirports.findAirportByCode(airportCode);
    if (a != nullptr) {
        printAirportInfo(a);

        cout << "Flight out of this airport: " << consult.searchNumberOfFlightsOutOfAirport(a)
    }
    else { cout << "Airport with code: " << airportCode << " not found!" << endl; }
}

void Script::globalNumber() {
    vector<MenuItem> globalMenu = {
            {"\033[1mAirports\033[0m", &Script::numberOfAirports},
            {"\033[1mFlights\033[0m", &Script::numberOfFlights},
            {"\033[1mFlight Routes\033[0m", &Script::numberOfFlightRoutes},
            {"[Back]", &Script::actionGoBack}
    };

    bool exitSubMenu = false;

    while (!exitSubMenu) {
        clearScreen();
        drawBox("Global Number");
        for (int i = 0; i < globalMenu.size(); i++) {
            cout << i + 1 << ". " << globalMenu[i].label << endl;
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
        } else if (choice >= 1 && choice <= globalMenu.size()) {
            (this->*globalMenu[choice - 1].action)();
        }
    }
}

void Script::numberOfAirports() {
    cout << "Global number of airports: " << consult.searchNumberOfAirports() << endl;
    cout << "\n";
    backToMenu();
}

void Script::numberOfFlights() {
    cout << "Global number of available flights: " << consult.searchNumberOfAvailableFlights() << endl;
    cout << "\n";
    backToMenu();
}

void Script::numberOfFlightRoutes() {
    cout << "Global number of available flight routes: " << consult.searchNumberOfAvailableFlightRoutes() << endl;
    cout << "\n";
    backToMenu();
}

void Script::flightsOutOfAirport(Vertex<Airport>* airport) {
    auto info = airport->getInfo();
    cout << "     Code: " << info.getCode() << endl;
    cout << "     Name: " << info.getName() << endl;
    cout << "     City: " << info.getCity() << endl;
    cout << "  Country: " << info.getCountry() << endl;
    cout << " Location: (" << info.getLocation().latitude << ", " << info.getLocation().longitude << ")" << endl;
}
