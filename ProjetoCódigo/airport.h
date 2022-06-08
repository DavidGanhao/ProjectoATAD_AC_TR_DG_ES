#pragma once
#include "map.h"

typedef struct airport {
    char iataCode[4];
    char airport[100];
    char city[35];
    char state[3];
    float latitude;
    float longitude;
    int timeZone;
} Airport;

typedef Airport *PtAirport;

int loadar(PtMap airports, int howMany);

void printAirport(PtAirport airport);

PtAirport createAirport(char* iatacode, char* airport, char* city, char* state, float latitude, float longitude, int timeZone);