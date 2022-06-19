#pragma once
#include <stdbool.h>

typedef struct airline {
    char code[3];
    char name[100];
} Airline;

/**
 * @brief Constructor of an Airline
 * 
 * @param iatacode - code of an Airline
 * @param name - name of an Airline
 * @return Airline - Airline created
 */
Airline airlineCreate(char* iatacode, char* name);

/**
 * @brief Function that shows the information of an Airline
 * 
 * @param airline - Airline to show
 */
void printAirline(Airline airline);
