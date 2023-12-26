/**
 * @file ListAirports.h
 * @brief Header file containing functionalities to search airports within a graph.
 */

#ifndef AED_AIRPORTS_LISTAIRPORTS_H
#define AED_AIRPORTS_LISTAIRPORTS_H

#include "ParseData.h"

/**
 * @class ListAirports
 * @brief Provides methods to search for airports within a graph.
 *
 * The ListAirports class offers functionalities to find airports based on various attributes,
 * such as airport code, name, city, country, and geographical coordinates.
 */
class ListAirports {
private:
    const Graph<Airport>& searchGraph;  ///< Reference to the graph containing airport data.

    /**
     * @brief Finds airports based on a specified attribute.
     * @tparam T The type of attribute to search for (name, city, country).
     * @param searchName The value of the attribute to search for.
     * @param getAttr Pointer to the member function that retrieves the attribute from Airport class.
     * @return Vector of airport vertices matching the attribute.
     */
    template <typename T>
    vector<Vertex<Airport>*> findAirportsByAttribute(const string& searchName, T (Airport::*getAttr)() const);
public:
    /**
     * @brief Constructor for ListAirports class.
     * @param dataGraph Reference to the graph containing airport data.
     */
    ListAirports(const Graph<Airport>& dataGraph);

    /**
     * @brief Finds an airport vertex based on the airport code.
     * @param airportCode The code of the airport to search for.
     * @return Pointer to the airport vertex if found, nullptr otherwise.
     */
    Vertex<Airport>* findAirportByCode(const string& airportCode);

    /**
     * @brief Finds airports based on the airport name.
     * @param searchName The name of the airport(s) to search for.
     * @return Vector of airport vertices matching the airport name.
     */
    vector<Vertex<Airport>*> findAirportsByAirportName(const string& searchName);

    /**
     * @brief Finds airports based on the city name.
     * @param searchName The name of the city associated with the airport(s) to search for.
     * @return Vector of airport vertices in the specified city.
     */
    vector<Vertex<Airport>*> findAirportsByCityName(const string& searchName);

    /**
     * @brief Finds airports based on the country name.
     * @param searchName The name of the country associated with the airport(s) to search for.
     * @return Vector of airport vertices in the specified country.
     */
    vector<Vertex<Airport>*> findAirportsByCountryName(const string& searchName);

    /**
     * @brief Finds the closest airports to given geographical coordinates.
     * @param coordinates The coordinates (latitude and longitude) for which the closest airports are searched.
     * @return Vector of airport vertices closest to the specified coordinates.
     */
    vector<Vertex<Airport>*> findClosestAirports(const Coordinates& coordinates);
};


#endif //AED_AIRPORTS_LISTAIRPORTS_H
