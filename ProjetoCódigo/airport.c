#include "airport.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

int loadap(PtMap airports, int howMany){
    
}

void printAirport(PtAirport airport){
    if(airport == NULL)
        printf("\n(AIRPORT NULL)\n\n");
    printf("Iatacode: %-4s; Airport: %-100s; City: %-35s; ",airport->iataCode, airport->airport, airport->city);
    printf("State: %-5s; Latitude: %-5.3f; Longitude: %-5.3f; Time Zone: %-4d\n",airport->state, airport->latitude, airport->longitude, airport->timeZone);
}

PtAirport createAirport(char* iatacode, char* airport, char* city, char* state, float latitude, float longitude, int timeZone){
    PtAirport newAirport = (PtAirport) malloc(sizeof(Airport));
    if(newAirport == NULL) return NULL;
    strcpy(newAirport->iataCode, iatacode);
    strcpy(newAirport->airport, airport);
    strcpy(newAirport->city, city);
    strcpy(newAirport->state, state);
    newAirport->latitude = latitude;
    newAirport->longitude = longitude;
    newAirport->timeZone = timeZone;
    return newAirport;
}