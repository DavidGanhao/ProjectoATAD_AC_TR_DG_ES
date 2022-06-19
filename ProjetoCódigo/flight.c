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

void timeInfoFlightArrival(Flight* flights, int start, int number){
    printf("%5s %12s %9s %12s %7s %12s %22s %16s %16s    %8s %22s %16s   %12s\n",
    "Day", "Day of Week", "Airline", "Flight Number", "Origin", "Destination", "Schedule Departure",
    "Departure Time", "Schedule Time", "Distance", "Scheduled Arrival", "Arrival Time", "Arrival Delay");
    for(int i = start; i < number; i++){
        printf("   %-2d  ", flights[i].day);
        printf("  %-10s ", dayOfWeek(flights[i].dayOfWeek));
        printf("    %-2s   ", flights[i].airline);
        printf("   %-6d   ", flights[i].flightNumber);
        printf("    %3s  ", flights[i].originAirport);
        printf("     %3s   ", flights[i].destinationAirport);
        printf("             %02d:%02d         ", flights[i].scheduledDeparture.hour, flights[i].scheduledDeparture.min);
        printf("      %02d:%02d      ", flights[i].departureTime.hour, flights[i].departureTime.min);
        printf("        %-4d      ", flights[i].scheduledTravelTime);
        printf("   %-5d ", flights[i].distance);
        printf("           %02d:%02d         ", flights[i].scheduledArrival.hour, flights[i].scheduledArrival.min);
        printf("      %02d:%02d      ", flights[i].arrivalTime.hour, flights[i].arrivalTime.min);
        printf("    %-6d   \n", flights[i].arrivalDelay);
    }
    
}

void swapFlight(Flight* flight1, Flight* flight2){
    Flight temp = *flight1;
    *flight1 = *flight2;
    *flight2 = temp;
}