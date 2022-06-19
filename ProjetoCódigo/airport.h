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

void printAirport(Airport airport);

Airport createAirport(char* iatacode, char* airport, char* city, char* state, float latitude, float longitude, int timeZone);

void printAirportForListAP(Airport airport);

void printAirportsInfo(Airport* airports, int start, int end);

void printAirportInfoAgregated(Airport airport, int numFlights, int numDepDelays, float avgDepDelays);

void swapAirport(Airport* x, Airport* y);