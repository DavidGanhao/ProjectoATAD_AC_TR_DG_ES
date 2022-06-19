#include "airline.h"
#include "input.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>


Airline airlineCreate(char* iatacode, char* name){
    Airline airline;
    strcpy(airline.code,iatacode);
    strcpy(airline.name, name);
    return airline;
}


void printAirline(Airline airline){
    printf("Iatacode: %3s; Name: %-100s\n",airline.code, airline.name);
}
