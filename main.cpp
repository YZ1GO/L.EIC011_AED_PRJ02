#include <iostream>
//#include "OutputData.h"
#include "Consult.h"
#include "OConsult.h"

int main() {
    // File paths for CSV files
    std::string airportsCSV = "data/airports.csv";
    std::string airlinesCSV = "data/airlines.csv";
    std::string flightsCSV = "data/flights.csv";

    // Creating ParseData object and calling the constructor
    ParseData parseData(airportsCSV, airlinesCSV, flightsCSV);
    parseData.setupIndegreeOutDegree();

    //convertDataGraphToTextFile(parseData.getDataGraph(), "text/Global_Data.txt");

    Consult consult(parseData.getDataGraph());
    Coordinates location = *new Coordinates();
    location.latitude = 34.793289;
    location.longitude = 5.738231;
    Airport BSK = Airport("BSK","Biskra","Biskra","Algeria", location);
    location.latitude = 34.6545;
    location.longitude = -112.42;
    Airport PRC = Airport("PRC", "Ernest A Love Fld", "Prescott", "United States", location);
    /*
    cout << consult.searchNumberOfAirports() << endl;                                         //expect 3019
    cout << consult.searchNumberOfAvailableFlightRoutes() << endl;                            //expect 35480
    cout << consult.searchNumberOfFlightsOutOfAirport(BSK) << endl;                           //expect 4
    cout << consult.searchNumberOfFlightsToAirport(BSK) << endl;                              //expect 3
    cout << consult.searchNumberOfFlightsOutOfAirportFromDifferentAirlines(BSK) << endl;      //expect 2
    for (const auto& pair : consult.searchNumberOfFlightsPerCity()) {
        cout << pair.first << ": " << pair.second << endl;
    }
     for (const auto& pair : consult.searchNumberOfFlightsPerAirline()) {
        cout << pair.first << ": " << pair.second << endl;
    }
    cout << consult.searchNumberOfCountriesFlownToFromAirport(BSK) << endl;                   //expect 2
    cout << consult.searchNumberOfCountriesFlownToFromCity("London", "Canada") << endl;       //expect 2
    cout << consult.searchNumberOfAirportsAvailableForAirport(BSK) << endl;                   //expect 3
    cout << consult.searchNumberOfReachableAirportsInXStopsFromAirport(PRC, 1) << endl;       //expect 150
    cout << consult.searchNumberOfReachableAirportsInXStopsFromAirport(BSK, 2) << endl;       //expect 8839
    */

    /*
    Airport source, target;
    source.setCode("NAS");
    target.setCode("AXP");
    OConsult oConsult(parseData.getDataGraph());

    for (auto trips : oConsult.searchTripGreatestNumberOfStopsBetweenThem(source, target)) {  //expect NAX->CRI->AXP (3)
        cout << "[" << trips.size() << "] ";
        auto it = trips.begin();
        while (it != trips.end()) {
            cout << it->getCode();
            if (next(it) != trips.end()) {
                cout << "->";
            }
            ++it;
        }
        cout << endl;
    }
    for (auto trips : oConsult.searchTripSmallestNumberOfStopsBetweenThem(source, target)) {    //expect NAX->AXP (2) [direct flight]
        cout << "[" << trips.size() << "] ";
        auto it = trips.begin();
        while (it != trips.end()) {
            cout << it->getCode();
            if (next(it) != trips.end()) {
                cout << "->";
            }
            ++it;
        }
        cout << endl;
    }*/

    /*
    int i = 1;
    for (const auto& airport : oConsult.searchEssentialAirports()) {
        cout << i++ << ". " << airport << endl;
    }


    int i = 1;
    for (const auto& traffic : oConsult.searchTopKairportGreatestAirTrafficCapacity(192)) {
        cout << i++ << ". [" << traffic.second << "] " << traffic.first.getCode() << endl;
    }

    /*
    Airport airport;
    airport.setCode("AOK");
    OConsult oConsult(parseData.getDataGraph());
    cout << oConsult.searchNumberOfFlightsOutOfAirport(airport) << endl;
    cout << oConsult.searchNumberOfFlightsToAirport(airport) << endl;
    */

    return 0;
}
