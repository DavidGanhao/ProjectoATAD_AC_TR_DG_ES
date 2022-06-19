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
 * @brief Método que mostra as informcações relativas de um Airport
 * 
 * @param airport - Airport to show
 */
void printAirport(Airport airport);

/**
 * @brief Function that shows the information of an Airport for the resquested function ListAP 
 * 
 * @param airport - Airport to show
 */
void printAirportForListAP(Airport airport);

/**
 * @brief Function that shows the informcation of an Airport array
 * 
 * @param airports - Airports array
 * @param start - initial index
 * @param end - final index
 */
void printAirportsInfo(Airport* airports, int start, int end);

/**
 * @brief Function that shows the information in aggregate form of an Airport
 * 
 * @param airport - Airport to show
 * @param numFlights - number of flights
 * @param numDepDelays - number of departures delays
 * @param avgDepDelays - average time delays
 */
void printAirportInfoAgregated(Airport airport, int numFlights, int numDepDelays, float avgDepDelays);

/**
 * @brief Function that swaps to Airports
 * 
 * @param x - first Airport to swap
 * @param y - second Airport to swap
 */
void swapAirport(Airport* x, Airport* y);