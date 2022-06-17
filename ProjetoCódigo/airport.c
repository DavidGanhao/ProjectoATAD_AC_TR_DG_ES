#include "airport.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

int loadap(PtMap airports, int howMany){
    return 0;
}

void printAirport(Airport airport){
    printf("Iatacode: %4s\n", airport.iataCode);
    printf("Airport: %100s\n", airport.airport);
    printf("City: %35s\n", airport.city);
    printf("State: %5s\n", airport.state);
    printf("Latitude: %5.3f\n", airport.latitude);
    printf("Longitude: %5.3f\n", airport.longitude);
    printf("Time Zone: %4d\n", airport.timeZone);
}

Airport createAirport(char* iatacode, char* airport, char* city, char* state, float latitude, float longitude, int timeZone){
    Airport newAirport;
    strcpy(newAirport.iataCode, iatacode);
    strcpy(newAirport.airport, airport);
    strcpy(newAirport.city, city);
    strcpy(newAirport.state, state);
    newAirport.latitude = latitude;
    newAirport.longitude = longitude;
    newAirport.timeZone = timeZone;
    return newAirport;
}