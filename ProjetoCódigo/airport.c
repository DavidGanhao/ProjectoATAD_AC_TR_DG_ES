#include "airport.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void printAirport(Airport airport){
    printf("Iatacode: %s\n", airport.iataCode);
    printf("Airport: %s\n", airport.airport);
    printf("City: %s\n", airport.city);
    printf("State: %s\n", airport.state);
    printf("Latitude: %.3f\n", airport.latitude);
    printf("Longitude: %.3f\n", airport.longitude);
    printf("Time Zone: %d\n", airport.timeZone);
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

void printAirportForListAP(Airport airport){
    printf("Iatacode: %s\n", airport.iataCode);
    printf("Airport: %s\n", airport.airport);
    printf("City: %s\n", airport.city);
    printf("State: %s\n", airport.state);
}

void printAirportsInfo(Airport* airports, int start, int end){
    printf("%-10s %-70s %-35s %-5s %-8s %-8s %-10s\n", "Iata Code", "Airport", "City", "State", "Latitude", "Longitude", "TimeZone");
    for(int i = start; i < end; i++){
        printf("%-10s ", airports[i].iataCode);
        printf("%-70s ", airports[i].airport);
        printf("%-35s ", airports[i].city);
        printf("%-5s ", airports[i].state);
        printf("%-8.2f ", airports[i].latitude);
        printf("%-8.2f ", airports[i].longitude);
        printf("%-10d \n", airports[i].timeZone);
    }
}

void printAirportInfoAgregated(Airport airport, int numFlights, int numDepDelays, float avgDepDelays){
    printf("%-10s ", airport.iataCode);
    printf("%-70s ", airport.airport);
    printf("%-35s ", airport.city);
    printf("     %-15d ", numFlights);
    printf("       %-20d ", numDepDelays);
    printf("  %-20.2f\n", avgDepDelays);
}

void swapAirport(Airport* x, Airport* y){
    Airport temp = *x;
    *x = *y;
    *y = temp;
}