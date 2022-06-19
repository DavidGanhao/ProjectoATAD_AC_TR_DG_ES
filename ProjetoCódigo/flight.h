/**
 * @file flight.h
 * @brief Definition of the flight in C.
 * 
 * Defines the type flight and associated operations.
 * 
 * @author David Ganhão, Tomás Ramos e André Caetano.
 * @bug No known bugs.
 */

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

/**
 * @brief Function used to create a flight.
 * 
 * @param day - integer referencing the day of the flight.
 * @param dayOfWeek - integer referencing the day of the week on which the flight will happen.
 * @param airline - array of chars referencing the airline.
 * @param flightNumber - integer referencing the number of the flight in question.
 * @param originAirport - array de chars referencing the origin airport of the flight corse.
 * @param destinationAirport - array de chars referencing the detination airport of the flight corse.
 * @param scheduledDeparture - time variable referencing the departure schedule.
 * @param departureTime - time variable referencing the departure time.
 * @param distance - integer referencing the distance of the full flight corse.
 * @param scheduleArrival - time variable referencing the schedule arrival.
 * @param arrivalTime - time variable referencing the arrival time.
 * 
 * @return flight
 */ 
Flight createFlight(int day, int dayOfWeek, char* airline, int flightNumber, char* originAirport, char* destinationAirport, Time scheduledDeparture, Time departureTime, int distance, Time scheduleArrival,  Time arrivalTime, int scheduledTravelTime);

/**
 * @brief Function used to print the info of a flight.
 * 
 * @param flight - Flight variable referencing a flight.
 **/
void printFlight(Flight flight);

/**
 * @brief Function used
 * @param flights - Flights to be printed
 * @param start - integer referencing the start of the array
 * @param number - integer referencing the end of the array
 **/
void timeInfoFlightArrival(Flight* flights, int start, int number);

/**
 * @brief Function used to return the day of the week using the number on the parameters.
 * @param dayOfWeek - integer referencing to the day of the week.
 **/
char* dayOfWeek(int dayOfWeek);

/**
 * @brief Converts a string to a value of Time
 * @param time - String to be converted
 * 
 **/
Time convertCharTokenToTime(char* time);

/** 
 * @brief Function used to swap 2 flights.
 * @param flight1 - flight to be swaped.
 * @param flight2 - flight to be swaped.
 * 
 **/
void swapFlight(Flight* flight1, Flight* flight2);