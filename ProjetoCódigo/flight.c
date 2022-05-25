#include "flight.h"

typedef struct flight{
    int day;
    int dayOfWeek;
    char airline[3];
    int flightNumber;
    char originAirport[4];
    char destinationAirport[4];
    Time scheduledDeparture;
    Time departureTime;
    int departureDelay; // in minutes
    int scheduledTravelTime; // in minutes
    int distance; // in miles
    Time scheduledArrival;
    Time arrivalTime;
    int arrivalDelay; // in minutes

}Flight;