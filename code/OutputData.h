/**
 * @file OutputData.h
 * @brief Header file containing functions to output airport data to a text file.
 */

#ifndef AED_AIRPORTS_OUTPUTDATA_H
#define AED_AIRPORTS_OUTPUTDATA_H

#include "ParseData.h"

/**
 * @brief Converts airport graph data into a text file format.
 * @param airportGraph The graph containing airport information.
 * @param filename The name of the file to which the data will be written.
 *
 * This function takes an airport graph and writes its information, including airport codes, names,
 * locations (city, country, coordinates), and flight routes, to a specified text file.
 */
void convertDataGraphToTextFile(const Graph<Airport>& airportGraph, const std::string& filename);

#endif //AED_AIRPORTS_OUTPUTDATA_H
