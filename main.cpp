#include <iostream>
//#include "OutputData.h"
#include "Consult.h"

int main() {
    // File paths for CSV files
    std::string airportsCSV = "data/airports.csv";
    std::string airlinesCSV = "data/airlines.csv";
    std::string flightsCSV = "data/flights.csv";

    // Creating ParseData object and calling the constructor
    ParseData parseData(airportsCSV, airlinesCSV, flightsCSV);
    parseData.setupIndegreeOutdegree();

    //convertDataGraphToTextFile(parseData.getDataGraph(), "text/Global_Data.txt");

    Consult consult(parseData.getDataGraph());
    Coordinates location = *new Coordinates();
    location.latitude = 34.793289;
    location.longitude = 5.738231;
    Airport BSK = Airport("BSK","Biskra","Biskra","Algeria", location);
    location.latitude = 34.6545;
    location.longitude = -112.42;
    Airport PRC = Airport("PRC", "Ernest A Love Fld", "Prescott", "United States", location);
    cout << consult.searchNumberOfAirportsAvailableForAirport(BSK) << endl;
    cout << consult.searchNumberOfCitiesAvailableForAirport(BSK) << endl;
    cout << consult.searchNumberOfCountriesAvailableForAirport(BSK) << endl;
/*
    Airport source, target;
    source.setCode("STZ");
    target.setCode("YHO");
    for (auto trips : consult.searchSmallestPathBetweenAirports(source, target)) {  //expect [12] STZ->SXO->GRP->MQH->BSB->CDG->YUL->YHZ->YYR->YRG->YMN->YSO->YHO
        cout << "[" << trips.size() - 1<< "] ";
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
    source.setCode("STZ");
    target.setCode("SRV");
    for (auto trips : consult.searchSmallestPathBetweenAirports(source, target)) {  //expect [12] STZ->SXO->GRP->MQH->BSB->CDG->LAX->ANC->ANI->CHU->CKD->SLQ->SRV
        cout << "[" << trips.size() - 1<< "] ";
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
    cout << consult.searchNumberOfAirports() << endl;                                         //expect 3019
    cout << consult.searchNumberOfAvailableFlights() << endl;                                 //expect 63832
    cout << consult.searchNumberOfAvailableFlightRoutes() << endl;                            //expect 35480
    cout << consult.searchNumberOfFlightsOutOfAirport(BSK) << endl;                           //expect 4
    cout << consult.searchNumberOfFlightsToAirport(BSK) << endl;                              //expect 4
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
    consult.searchMaxTripAndCorrespondingPairsOfAirports();

Airport s;
s.setCode("MUW");
    cout << consult.searchNumberOfReachableAirportsInXStopsFromAirport(PRC, 1) << endl;       //expect 150
    cout << consult.searchNumberOfReachableAirportsInXStopsFromAirport(s, 1) << endl;       //expect 64
    cout << consult.searchNumberOfReachableCitiesInXStopsFromAirport(BSK, 0) << endl;         //expect 3
    cout << consult.searchNumberOfReachableCitiesInXStopsFromAirport(BSK, 1) << endl;         //expect 159
    cout << consult.searchNumberOfReachableCitiesInXStopsFromAirport(BSK, 2) << endl;         //expect 1065
    cout << consult.searchNumberOfReachableCountriesInXStopsFromAirport(BSK, 0) << endl;      //expect 2
    cout << consult.searchNumberOfReachableCountriesInXStopsFromAirport(BSK, 1) << endl;      //expect 50
    cout << consult.searchNumberOfReachableCountriesInXStopsFromAirport(BSK, 2) << endl;      //expect 192

    Airport source, target;
    source.setCode("NAS");
    target.setCode("AXP");

    for (auto trips : consult.searchSmallestPathBetweenAirports(source, target)) {  //expect NAX->CRI->AXP (3)
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
    for (auto trips : consult.searchSmallestPathBetweenAirports(source, target)) {    //expect NAX->AXP (2) [direct flight]
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


    int i = 1;
    for (const auto& airport : consult.searchEssentialAirports()) {
        cout << i++ << ". " << airport << endl;
    }


    int j = 1;
    for (const auto& traffic : consult.searchTopKAirportGreatestAirTrafficCapacity(192)) {
        cout << j++ << ". [" << traffic.second << "] " << traffic.first.getCode() << endl;
    }*/

    return 0;
}
