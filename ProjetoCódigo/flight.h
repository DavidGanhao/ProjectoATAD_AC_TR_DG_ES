#pragma once
#include "time.h"

typedef struct flight {
    int day;
    int dayOfWeek;
    char airline[3];
    int flightNumber;
    char originAirport[4];
    char destinationAirport[4];
    Time scheduledDeparture;
    Time departureTime;
    int departureDelay;
    int scheduledTravelTime;
    int distance;
    Time scheduledArrival;
    Time arrivalTime;
    int arrivalDelay;
} Flight;

Flight createFlight(int day, int dayOfWeek, char* airline, int flightNumber, char* originAirport, char* destinationAirport, Time scheduledDeparture, Time departureTime, int distance, Time scheduleArrival,  Time arrivalTime, int scheduledTravelTime);

void printFlight(Flight flight);

void timeInfoFlightArrival(Flight* flights, int start, int number);

char* dayOfWeek(int dayOfWeek);

Time convertCharTokenToTime(char* time);

void swapFlight(Flight* flight1, Flight* flight2);