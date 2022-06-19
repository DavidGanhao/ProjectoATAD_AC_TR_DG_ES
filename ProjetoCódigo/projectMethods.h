#pragma once
#include "flight.h"
#include "airline.h"
#include "airport.h"
#include "list.h"
#include "map.h"

/**
 * @brief Function used to clear the information existent on the memory. It shows the number
 * of registers that were discarded.
 *
 * @param airlines - Array of airlines referencing airlines.
 * @param airport - map with airports.
 * @param flights - list with flights.
 *
 **/
void clear(Airline *airlines, PtMap airports, PtList flights);

/**
 * @brief Function used to exit the program. Sets all the collection allocated memory free.
 *
 * @param airlines - Array of airlines referencing airlines.
 * @param airport - map with airports.
 * @param flights - list with flights.
 *
 **/
void quit(Airline *airlines, PtMap airports, PtList flights);

/**
 * @brief Function used to show all flights data available. It can do it paginated or randomly.
 *
 * @param flights - list with flights.
 *
 **/
void showAll(PtList flights);

/**
 * @brief Function used to
 *
 * @param flights - list with flights.
 *
 **/
PtList getWF(PtList flights);

/**
 * @brief Function used to show all the flight data from an airport requested to the user.
 *
 * @param flights - list with flights.
 * @param airport - array of chars referenncing an airport.
 *
 * @return list with the flight data.
 *
 **/
void showWF(PtList flights, char *airport);

/**
 * @brief Function used to show a list of airlines with registered flights.
 *
 * @param flights - list with flights.
 * @param airlines - array of airlines referencing airlines.
 *
 **/
void listAR(PtList flights, Airline *airlines);

/**
 * @brief Function used to show a list of airports with registered flights.
 *
 * @param flights - list with flights.
 * @param airports - map with airports.
 *
 **/
void listAP(PtList flights, PtMap airports);

/**
 * @brief Function that returns the number of flights that departured on time or in a tolerance between 0 an 30 minutes.
 *
 * @param flights - list with flights.
 * @param number - integer variable referecing to a number.
 *
 * @return number of flights on time (departure)
 **/
int onTimeDeparture(PtList flights, int number);

/**
 * @brief Function that returns the number of flights that arrived on time or in a tolerance between 0 an 30 minutes.
 *
 * @param flights - list with flights.
 * @param number - integer variable referecing to a number.
 *
 * @return number of flights on time (arrival)
 *
 **/
int onTimeArrival(PtList flights, int number);

/**
 * @brief Function that shows the average of distances done in every flight for every day, only week days and only weekends.
 * It also shows the average of the distances done by the flights that departured at an airport requested to the user.
 *
 * @param flights - list with flights.
 * @param airportIataCode - Array of chars referencing to the iatacode of an airport.
 **/
void average(PtList flights, char *airportIataCode);

/**
 * @brief Function that shows for every known airline the airport list through were the flights pass.
 *
 * @param flight - list with flights.
 * @param airlines - Array with airlines referencing airlines.
 * @param airports - map with airports.
 *
 **/
void showAP(PtList flights, Airline *airlines, PtMap airports);

/**
 * @brief Function that shows in a decrescent way the data of N flights by the arrival delay time.
 *
 * @param flights - list with flights.
 * @param number - Integer variable referencing a number.
 *
 **/
void topN(PtList flights, int number);

/**
 * @brief Function that calculates all the possible ways in which a flight corse happens and in which the flight ends
 * at the origin airport.
 * It also shows the fastest possible flight in that case.
 * The minimum wait time in between each flight is an hour an a half.
 * 
 * @param flights - list of flights.
 * @param airport - Airport variable referencing an airport.
 * @param airportIataCode - IataCode of the Airport
 **/
void tsp(PtList flights, PtMap airports, MapKey airportIataCode);

/**
 * @brief Function that shows tha airport data ordered by an atribute requested to the user.
 * 
 * @param airports - map with airports.
 * 
 **/
void airport_s(PtMap airports);

/**
 * @brief Function that orders the airports by the city.
 * 
 * @param airports - map with airports.
 * @param size - Integer variable referencing a size.
 * @param ascending - boolean variable referencing ascending or descending bu true or false.
 * @param airportsTemp - Array of airports referencing airports.
 * 
 */
void airportsOrderedCity(PtMap airports, int size, bool ascending, Airport *airportsTemp);

/**
 * @brief Function that orders the airports by longitude.
 * 
 * @param airports - map with airports.
 * @param size - Integer variable referencing a size.
 * @param airportsTemp - Array of airports referencing airports.
 * 
 **/
void *airportsOrderedLongitude(PtMap airports, int size, Airport *airportsTemp);

/**
 * @brief Function that orders the airports by latitude.
 * 
 * @param airports - map with airports.
 * @param size - Integer variable referencing a size.
 * @param airportsTemp - Array of airports referencing airports.
 * 
 **/
void *airportsOrderedLatitude(PtMap airports, int size, Airport *airportsTemp);

/**
 * @brief Function that calculates the travel time of a flight.
 * 
 * @param originAirport - Airport variable referencing the originAirport.
 * @param destinationAirport - Airport variable referencing the destinationAirport.
 * @param scheduledDeparture - Time variable referencing the schedule departure.
 * @param scheduleArrival - Time variable referencing the schedule arrival.
 * 
 * @return time calculated.
 * 
 **/
int calculateTravelTime(Airport originAirport, Airport destinationAirport, Time scheduledDeparture, Time scheduleArrival);

/**
 * @brief Function that shows a list of flights associated to an airport.
 * 
 * @param airport - Airport variable referencing an airport.
 * @param flights - list with flights.
 * 
 * @return list with flights.
 * 
 **/
PtList flightsAssociatedToAirport(Airport airport, PtList flights);

/**
 * @brief Function that shows a map with the airports with flights.
 * 
 * @param airports - map with airports.
 * @param flights - list with flights.
 * 
 * @return map with airports with flights
 * 
 **/
PtMap airportWithFlights(PtMap airports, PtList flights);

/**
 * @brief Function that 
 * 
 * @param airports - map with airports.
 * @param fights - list with flights.
 **/
void airportsMethod(PtMap airports, PtList flights);
