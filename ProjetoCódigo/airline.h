#pragma once
#include <stdbool.h>

typedef struct airline {
    char code[3];
    char name[100];
} Airline;


Airline airlineCreate(char* iatacode, char* name);

void printAirline(Airline airline);
