#ifndef AED_AEROPORTO_OCONSULT_H
#define AED_AEROPORTO_OCONSULT_H

#include "Data.h"
#include "ParseData.h"
#include <unordered_set>
#include <unordered_map>
#include <limits>

class OConsult {
private:
    const Graph<Airport>& consultGraph;




public:
    OConsult(const Graph<Airport>& dataGraph);



    int searchNumberOfFlightsOutOfAirport(const Airport& airport);
    int searchNumberOfFlightsToAirport(const Airport& airport);
};


#endif //AED_AEROPORTO_OCONSULT_H
