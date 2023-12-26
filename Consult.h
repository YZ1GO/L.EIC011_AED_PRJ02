#ifndef AED_AIRPORTS_CONSULT_H
#define AED_AIRPORTS_CONSULT_H

#include "ParseData.h"
#include <map>
#include <unordered_set>
#include <limits>
#include <functional>

/**
 * @class Consult
 * @brief Provides functionalities to perform various queries and analyses on Air Travel Flight data.
 *
 * The Consult class offers methods to conduct analyses and queries on airport-related data.
 * It uses the provided graph structure to perform operations like searching for flights per city,
 * per airline, available destinations, traffic statistics, finding paths between airports, etc.
 */
class Consult {
private:
    const Graph<Airport>& consultGraph;     ///< Reference to the airport graph used for consultation.

    /**
     * @brief Performs a depth-first search to count flights per city from a given vertex.
     * @param v Pointer to the vertex initiating the search.
     * @param res Map containing the count of flights per city.
     */
    void dfsVisitFlightsPerCity(Vertex<Airport> *v, map<string, int> &res);

    /**
     * @brief Performs a depth-first search to count flights per airline from a given vertex.
     * @param v Pointer to the vertex initiating the search.
     * @param res Map containing the count of flights per airline.
     */
    void dfsVisitFlightsPerAirline(Vertex<Airport> *v, map<Airline, int> &res);

    /**
     * @brief Initiates a depth-first search to find airports in a specific city and country.
     * @param city The city to search for.
     * @param country The country to search for.
     * @param v Pointer to the vertex initiating the search.
     * @param res Vector containing vertices representing airports in the given city and country.
     */
    void dfsVisitCityAirports(const string& city, const string& country, Vertex<Airport> *v, vector<Vertex<Airport>*>& res);

    /**
     * @brief Initiates a depth-first search to process available destinations from a vertex.
     * @param v Pointer to the vertex initiating the search.
     * @param processDestination Function to process the available destinations.
     */
    void dfsAvailableDestinations(Vertex<Airport>* v, std::function<void(Vertex<Airport>*)> processDestination);

    /**
     * @brief Searches for the number of reachable destinations from an airport in a specified number of stops.
     * @param airport Pointer to the starting airport.
     * @param layOvers Number of layovers or stops to consider.
     * @param attributeExtractor Function to extract an attribute for each reachable destination.
     * @return The count of reachable destinations in 'X' stops (number of layovers).
     */
    int searchNumberOfReachableDestinationsInXStopsFromAirport(Vertex<Airport>* airport, int layOvers, const function<string(Vertex<Airport>*)>& attributeExtractor);

    /**
     * @brief Finds the top airports with the highest air traffic capacity.
     * @return Decreasingly ordered vector of pairs containing airports and their traffic capacities.
     */
    vector<pair<Airport,int>> topTrafficCapacityAirports();

    /**
     * @brief Initiates a depth-first search to identify essential airports.
     * @param v Pointer to the vertex initiating the search.
     * @param s Stack used in the search process.
     * @param res Unordered set containing essential airports found.
     * @param i Counter used in the search process.
     */
    void dfsEssentialAirports(Vertex<Airport> *v, stack<string> &s, unordered_set<string> &res, int &i);

public:
    /**
     * @brief Constructor for Consult class.
     * @param dataGraph Reference to the airport graph used for consultation.
     */
    Consult(const Graph<Airport>& dataGraph);

    /**
     * @brief Counts the total number of airports.
     * @return The number of airports.
     */
    int searchNumberOfAirports();

    /**
     * @brief Counts the total number of available flights.
     * @return The number of available flights.
     */
    int searchNumberOfAvailableFlights();

    /**
     * @brief Counts the total number of available flight routes.
     * @return The number of available flight routes.
     */
    int searchNumberOfAvailableFlightRoutes();

    /**
     * @brief Counts the number of flights departing from a specific airport.
     * @param airport Pointer to the airport vertex.
     * @return The number of flights departing from the airport.
     */
    int searchNumberOfFlightsOutOfAirport(Vertex<Airport>* airport);

    /**
     * @brief Counts the number of flights arriving at a specific airport.
     * @param airport Pointer to the airport vertex.
     * @return The number of flights arriving at the airport.
     */
    int searchNumberOfFlightsToAirport(Vertex<Airport>* airport);

    /**
     * @brief Counts the number of flights departing from a specific airport via different airlines.
     * @param airport Pointer to the airport vertex.
     * @return The number of flights departing from the airport via different airlines.
     */
    int searchNumberOfFlightsOutOfAirportFromDifferentAirlines(Vertex<Airport>* airport);

    /**
     * @brief Searches the number of flights per city.
     * @return Map containing the count of flights per city.
     */
    map<string, int> searchNumberOfFlightsPerCity();

    /**
     * @brief Searches the number of flights per airline.
     * @return Map containing the count of flights per airline.
     */
    map<Airline, int> searchNumberOfFlightsPerAirline();

    /**
     * @brief Counts the number of countries flown to from a specific airport.
     * @param airport Pointer to the airport vertex.
     * @return The number of countries flown to from the specified airport.
     */
    int searchNumberOfCountriesFlownToFromAirport(Vertex<Airport>* airport);

    /**
     * @brief Counts the number of countries flown to from a specific city and country.
     * @param city The city name.
     * @param country The country name.
     * @return The number of countries flown to from the specified city and country.
     */
    int searchNumberOfCountriesFlownToFromCity(const string& city, const string& country);

    /**
     * @brief Counts the number of available airports reachable from a specific airport.
     * @param airport Pointer to the airport vertex.
     * @return The number of available airports reachable from the specified airport.
     */
    int searchNumberOfAirportsAvailableForAirport(Vertex<Airport>* airport);

    /**
     * @brief Counts the number of available cities reachable from a specific airport.
     * @param airport Pointer to the airport vertex.
     * @return The number of available cities reachable from the specified airport.
     */
    int searchNumberOfCitiesAvailableForAirport(Vertex<Airport>* airport);

    /**
     * @brief Counts the number of available countries reachable from a specific airport.
     * @param airport Pointer to the airport vertex.
     * @return The number of available countries reachable from the specified airport.
     */
    int searchNumberOfCountriesAvailableForAirport(Vertex<Airport>* airport);

    /**
     * @brief Counts the number of reachable airports in a certain number of stops (layovers) from a specific airport.
     * @param airport Pointer to the airport vertex.
     * @param layOvers The maximum number of layovers.
     * @return The number of reachable airports within the specified layovers.
     */
    int searchNumberOfReachableAirportsInXStopsFromAirport(Vertex<Airport>* airport, int layOvers);

    /**
     * @brief Counts the number of reachable cities in a certain number of stops (layovers) from a specific airport.
     * @param airport Pointer to the airport vertex.
     * @param layOvers The maximum number of layovers.
     * @return The number of reachable cities within the specified layovers.
     */
    int searchNumberOfReachableCitiesInXStopsFromAirport(Vertex<Airport>* airport, int layOvers);

    /**
     * @brief Count the number of reachable countries in a certain number of stops (layovers) from a specific airport.
     * @param airport Pointer to the airport vertex.
     * @param layOvers The maximum number of layovers.
     * @return The number of reachable countries within the specified layovers.
     */
    int searchNumberOfReachableCountriesInXStopsFromAirport(Vertex<Airport>* airport, int layOvers);

    /**
      * @brief Searches for the top 'K' airports with the greatest air traffic capacity.
      * @details Retrieves the top 'K' airports with the greatest air traffic capacity.
      * If there are airports with the same capacity as the 'K+1'th airport, they are also included in the result.
      * @param k The number of top airports to retrieve.
      * @return A vector of pairs containing airports and their corresponding air traffic capacity.
      */
    vector<pair<Airport,int>> searchTopKAirportGreatestAirTrafficCapacity(const int& k);

    /**
     * @brief Searches for essential airports using Tarjan's algorithm for finding strongly connected components.
     * @return An unordered set containing the codes of essential airports.
     */
    unordered_set<string> searchEssentialAirports();

    /**
     * @brief Searches for the maximum trip and corresponding pairs of airports.
     * @details Finds the longest trip possible within the airport network and retrieves all corresponding paths.
     * @return A vector of vectors containing sequences of airports representing the paths of the longest trip(s).
     */
    vector<vector<Airport>> searchMaxTripAndCorrespondingPairsOfAirports(int& diameter);

    /**
     * @brief Searches for the smallest path between two airports.
     * @details Retrieves the smallest path between the specified source and target airports.
     * @param source The starting airport.
     * @param target The destination airport.
     * @return A vector of vectors containing sequences of airports representing the smallest path(s) between the source and target airports.
     */
    vector<vector<Airport>> searchSmallestPathBetweenAirports(const Airport& source, const Airport& target);
};


#endif //AED_AIRPORTS_CONSULT_H
