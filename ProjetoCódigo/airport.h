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
 * @brief Function used to print the info of an airport.
 * @param airport - Airport variable referencing an airport.
 **/
void printAirport(Airport airport);

/**
 * @brief Function used to create an airport
 * 
 * @param iatacode - array of chars referencing the code of the airport.
 * @param airport - array of chars referencing the airport.
 * @param city - array of chars referencing the city in which the airport is located.
 * @param state - array of chars referencing the state in which the airport is located.
 * @param latitude - float variable referencing the latitude of the airport.
 * @param longitude - float variable referencing the longitude of the airport.
 * @param timeZone - integer variable referencing the timeZone of the airport.
 **/
Airport createAirport(char* iatacode, char* airport, char* city, char* state, float latitude, float longitude, int timeZone);

/**
 * @brief Function used to print only a few piece of information about an airport. (used in function listAP).
 * 
 * @param airport - Airport variable referencing an airport.
 * @return airport created
 **/
void printAirportForListAP(Airport airport);

/**
 * @brief Function used to print the airports info.
 * 
 * @param airports - array of airports.
 * @param start - integer variable referecing to the starting index.
 * @param end - integer variable referencing to the end index.
 * 
 **/
void printAirportsInfo(Airport* airports, int start, int end);

/**
 * @brief Function used to to show agregated information about an airport.
 * 
 * @param airport - Airport variable referencing to an airport.
 * @param numFlights - Integer variable referencing to the number of flights.
 * @param numDepDelays - Integer variable referencing to the number of departures with delay.
 * @param avgDepDelays - Float variable referencing to the average of the departures with delay.
 * 
 **/
void printAirportInfoAgregated(Airport airport, int numFlights, int numDepDelays, float avgDepDelays);

/**
 * @brief Function used to swap airports.
 * 
 * @param x - airport to be swaped.
 * @param y - airport to be swaped.
 **/
void swapAirport(Airport* x, Airport* y);