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
    */


    OConsult oConsult(parseData.getDataGraph());
    /*
    int i = 1;
    for (const auto& airport : oConsult.searchEssentialAirports()) {
        cout << i++ << ". " << airport << endl;
    }
    */
    int i = 1;
    for (const auto& traffic : oConsult.searchTopKairportGreatestAirTrafficCapacity(2)) {
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
