#pragma once

typedef struct airline {
    char iatacode[3];
    char name[100];
} Airline;

typedef Airline *PtAirline;


int loadap(PtAirline airlines[], int howMany);

PtAirline airlineCreate(char* iatacode, char* name);

void printAirline(PtAirline airline);