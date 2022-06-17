#pragma once

typedef struct airline {
    char iatacode[3];
    char name[100];
} Airline;


int loadar(Airline* airlines, int howMany);

Airline airlineCreate(char* iatacode, char* name);

void printAirline(Airline airline);