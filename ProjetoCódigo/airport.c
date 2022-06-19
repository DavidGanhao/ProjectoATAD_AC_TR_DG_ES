#include "airport.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct airport {
    char iataCode[4];
    char airport[100];
    char city[35];
    char state[3];
    float latitude;
    float longitude;
    int timeZone;
} Airport;

void printAirport(Airport airport){
    printf("Iatacode: %s\n", airport.iataCode);
    printf("Airport: %s\n", airport.airport);
    printf("City: %s\n", airport.city);
    printf("State: %s\n", airport.state);
    printf("Latitude: %.3f\n", airport.latitude);
    printf("Longitude: %.3f\n", airport.longitude);
    printf("Time Zone: %d\n", airport.timeZone);
}

void printAirportForListAP(Airport airport){
    printf("Iatacode: %s\n", airport.iataCode);
    printf("Airport: %s\n", airport.airport);
    printf("City: %s\n", airport.city);
    printf("State: %s\n", airport.state);
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