#pragma once

typedef struct airline {
    char iatacode[3];
    char name[100];
} Airline;

typedef Airline *PtAirline;
