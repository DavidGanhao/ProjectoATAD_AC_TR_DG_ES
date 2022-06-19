#pragma once
#include <stdbool.h>

typedef struct airport {
    char iataCode[4];
    char airport[100];
    char city[35];
    char state[3];
    float latitude;
    float longitude;
    int timeZone;
} Airport;


/**
 * @brief Function used to create an airport
 * 
 * @param airport - Airport to show
 */
void printAirport(Airport airport);

/**
 * @brief Constructor of an Airport
 * 
 * @param iatacode - code of an Airport
 * @param airport - name of an Airport
 * @param city - city of an Airport
 * @param state - state of an Airport
 * @param latitude - latitude of an Airport
 * @param longitude - longitude of an Airport
 * @param timeZone - timeZone of an Airport
 * @return Airport - Airport created
 */
Airport createAirport(char* iatacode, char* airport, char* city, char* state, float latitude, float longitude, int timeZone);

/**
 * @brief Function used to print the info of an airport.
 * 
 * @param airport - Airport variable referencing an airport.
 */
void printAirportForListAP(Airport airport);

/**
 * @brief Function that shows the informcation of an Airport array
 * 
 * @param airports - array of airports.
 * @param start - integer variable referecing to the starting index.
 * @param end - integer variable referencing to the end index.
 */
void printAirportsInfo(Airport* airports, int start, int end);

/**
 * @brief Function that shows the information in aggregate form of an Airport
 * 
 * @param airport - Airport variable referencing to an airport.
 * @param numFlights - Integer variable referencing to the number of flights.
 * @param numDepDelays - Integer variable referencing to the number of departures with delay.
 * @param avgDepDelays - Float variable referencing to the average of the departures with delay.
 */
void printAirportInfoAgregated(Airport airport, int numFlights, int numDepDelays, float avgDepDelays);

/**
 * @brief Function that swaps to Airports
 * 
 * @param x - first Airport to swap
 * @param y - second Airport to swap.
 * @param y - second Airport to swap
 */
void swapAirport(Airport* x, Airport* y);