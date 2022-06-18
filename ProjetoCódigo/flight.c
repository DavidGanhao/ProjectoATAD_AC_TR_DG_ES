#include "flight.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

Flight createFlight(int day, int dayOfWeek, char* airline, int flightNumber, char* originAirport, char* destinationAirport, Time scheduledDeparture, Time departureTime, int distance, Time scheduleArrival, Time arrivalTime, int scheduledTravelTime){
    Flight flight;
    flight.day = day;
    flight.dayOfWeek = dayOfWeek;
    strcpy(flight.airline, airline);
    flight.flightNumber = flightNumber;
    strcpy(flight.originAirport, originAirport);
    strcpy(flight.destinationAirport, destinationAirport);
    flight.scheduledDeparture = scheduledDeparture;
    flight.departureTime = departureTime;
    flight.departureDelay = timeDiffSpecial(scheduledDeparture, departureTime);
    flight.distance = distance;
    flight.scheduledArrival = scheduleArrival;
    flight.arrivalTime = arrivalTime;
    flight.arrivalDelay = timeDiffSpecial(scheduleArrival, arrivalTime);
    flight.scheduledTravelTime = scheduledTravelTime;
    return flight;
}

void printFlight(Flight flight){
    printf("Day: %d\n", flight.day);
    printf("Day of the week: %s\n",dayOfWeek(flight.dayOfWeek));
    printf("Airline: %s\n", flight.airline);
    printf("Flight Number: %d\n", flight.flightNumber);
    printf("Origin Airport: %s\n", flight.originAirport);
    printf("Destination Airport: %s\n", flight.destinationAirport);
    printf("Scheduled Departure: %02d:%02d\n", flight.scheduledDeparture.hour, flight.scheduledDeparture.min);
    printf("Departure Time: %02d:%02d\n", flight.departureTime.hour, flight.departureTime.min);
    printf("Departure Delay: %d minutes\n", flight.departureDelay);
    printf("Distance: %d km\n", flight.distance);
    printf("Schedule Arrival: %02d:%02d\n", flight.scheduledArrival.hour, flight.scheduledArrival.min);
    printf("Arrival Time: %02d:%02d\n", flight.arrivalTime.hour, flight.arrivalTime.min);
    printf("Arrival Delay: %d minutes\n", flight.arrivalDelay);
    printf("Scheduled Travel Time: %d minutes\n", flight.scheduledTravelTime);
}

char* dayOfWeek(int dayOfWeek){
    switch (dayOfWeek)
    {
    case 1: return "Monday";
    case 2: return "Tuesday";
    case 3: return "Wednesday";
    case 4: return "Thursday";
    case 5: return "Friday";
    case 6: return "Saturday";
    case 7: return "Sunday";
    default: return "UNKNOWN";
    }
}

Time convertCharTokenToTime(char* time){
    Time timeToReturn;
    if(strlen(time) > 4) return timeToReturn;
    int temp = atoi(time);
    int hours = temp/100;
    int minutes = temp-(hours*100);
    timeToReturn.hour = hours;
    timeToReturn.min = minutes;
    return timeToReturn;
}