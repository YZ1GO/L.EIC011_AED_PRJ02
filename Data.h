#ifndef AED_AEROPORTO_DATA_H
#define AED_AEROPORTO_DATA_H

#include "Utilities.h"
#include <iostream>
#include <vector>

/***
 * @struct Coordinates
 * @brief Structure to represent geographic coordinates.
 */
struct Coordinates {
    double latitude;
    double longitude;
};

/***
 * @class Airport
 * @brief Class to represent a airport.
 */
class Airport {
private:
    std::string code;       ///< The airport code.
    std::string name;       ///< The airport name.
    std::string city;       ///< The city where the airport is located.
    std::string country;    ///< The country where the airport is located.
    Coordinates location;   ///< The geographic coordinates of the airport.

public:
    /***
     * @brief Default constructor for the Airport class.
     */
    Airport() {}

    /***
     * @brief Constructor for the Airport class.
     * @param c The airport code.
     * @param n The airport name.
     * @param ci The airport city.
     * @param co The airport country.
     * @param l The airport geographic coordinates.
     */
    Airport(const std::string& c, const std::string& n, const std::string& ci, const std::string& co, Coordinates l)
            : code(c), name(n), city(ci), country(co), location(l) {}

    /***
     * @brief Getter method to retrieve the airport code.
     * @return The airport code.
     */
    std::string getCode() const { return code; }

    /***
     * @brief Setter method to set the airport code.
     * @param c The airport code.
     */
    void setCode(const std::string& c) { code = c; }

    /***
     * @brief Getter method to retrieve the airport name.
     * @return The airport name.
     */
    std::string getName() const { return name; }

    /***
     * @brief Setter method to set the airport name.
     * @param n The airport name.
     */
    void setName(const std::string& n) { name = n; }

    /***
     * @brief Getter method to retrieve the city where the airport is located.
     * @return The city where the airport is located.
     */
    std::string getCity() const { return city; }

    /***
     * @brief Setter method to set the city where the airport is located.
     * @param ci The city where the airport is located.
     */
    void setCity(const std::string& ci) { city = ci; }

    /***
     * @brief Getter method to retrieve the country where the airport is located.
     * @return The country where the airport is located.
     */
    std::string getCountry() const { return country; }

    /***
     * @brief Setter method to set the country where the airport is located.
     * @param co The country where the airport is located.
     */
    void setCountry(const std::string& co) { country = co; }

    /***
     * @brief Getter method to retrieve the geographic coordinates of the airport.
     * @return The geographic coordinates of the airport.
     */
    Coordinates getLocation() const { return location; }

    /***
     * Setter method to set the geographic coordinates of the airport.
     * @param latitude The latitude value.
     * @param longitude The longitude value.
     */
    void setLocation(double latitude, double longitude) {
        location.latitude = latitude;
        location.longitude = longitude;
    }

    /***
     * @brief Calculate the distance between the airport's coordinates and another set of coordinates using the Haversine formula.
     * @param other The other set of coordinates.
     * @return The distance between the airport and the provided coordinates in kilometers.
     */
    double getDistance(const Coordinates& other) const { return HarversineDistance(location.latitude, location.longitude, other.latitude, other.longitude); }

    /***
     * @brief Overloaded equality operator to compare two airports based on their codes.
     * @param other The other airport object.
     * @return True if the airports have the same code, otherwise false.
     */
    bool operator==(const Airport& other) const { return code == other.code; }
};

class Airline {
private:
    std::string code;
    std::string name;
    std::string callsign;
    std::string country;

public:
    Airline() {}
    Airline(const std::string& c, const std::string& n, const std::string& cs, const std::string& co)
            : code(c), name(n), callsign(cs), country(co) {}

    std::string getCode() const { return code; }
    void setCode(const std::string& c) { code = c; }

    std::string getName() const { return name; }
    void setName(const std::string& n) { name = n; }

    std::string getCallsign() const { return callsign; }
    void setCallsign(const std::string& cs) { callsign = cs; }

    std::string getCountry() const { return country; }
    void setCountry(const std::string& co) { country = co; }

    bool operator<(const Airline& other) const { return code < other.code; }
    bool operator==(const Airline& other) const { return code == other.code; }
};

#endif //AED_AEROPORTO_DATA_H
