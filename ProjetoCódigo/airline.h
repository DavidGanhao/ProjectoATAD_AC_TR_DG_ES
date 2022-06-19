#pragma once
#include <stdbool.h>

typedef struct airline {
    char iatacode[3];
    char name[100];
} Airline;

/**
 * @brief Constructor of an Airline
 * 
 * @param iatacode code of the Airline
 * @param name name of the Airline
 * @return Created Airline
 */
Airline airlineCreate(char* iatacode, char* name);

void printAirline(Airline airline);
