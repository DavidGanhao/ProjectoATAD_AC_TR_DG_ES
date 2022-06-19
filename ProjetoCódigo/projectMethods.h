/**
 * @file projectMethods.h
 * @brief Definition of all methods that allow the project to run.
 * 
 *  All the complex methods, base methods and info flight methods.
 * 
 * @author David Ganhão, Tomás Ramos e André Caetano.
 * @bug No known bugs.
 */

#pragma once
#include "flight.h"
#include "airline.h"
#include "airport.h"
#include "list.h"
#include "map.h"
#define AIRLINESIZE 14
#define AIRPORTSIZE 319
#define FLIGHTSSIZE 11515

/**
 * @brief Loads all the airports from a file to a map.
 * 
 * @param airports - Map of airports.
 * @param howMany - How many airports desired to add.
 * @return int - The number of airports added.
 */
int loadap(PtMap airports, int howMany);

/**
 * @brief Loads all the airlines from a file to a dinamic array.
 * 
 * @param airlines - Dinamic array of airlines.
 * @param howMany - How many airlines desired to add.
 * @return int - The number of airlines added.
 */
int loadar(Airline* airlines, int howMany);

/**
 * @brief Loads all the flights from a file to a list.
 * 
 * @param airports - All airports.
 * @param flights - List of flights.
 * @param howMany - How many flights desired to add.
 * @return int - The number of flights added.
 */
int loadf(PtMap airports, PtList flights, int howMany);

/**
 * @brief Function used to clear the information existent on the memory. It shows the number
 * of registers that were discarded.
 *
 * @param airlines - Array of airlines referencing airlines.
 * @param airport - map with airports.
 * @param flights - list with flights.
 *
 **/
void clear(Airline* airlines, PtMap airports, PtList flights);

/**
 * @brief Function used to exit the program. Sets all the collection allocated memory free.
 *
 * @param airlines - Array of airlines referencing airlines.
 * @param airport - map with airports.
 * @param flights - list with flights.
 *
 **/
void quit(Airline* airlines, PtMap airports, PtList flights);

/**
 * @brief Function used to show all flights data available. It can do it paginated or randomly.
 *
 * @param flights - list with flights.
 *
 **/
void showAll(PtList flights);

/**
 * @brief Shows 20 flights per page.
 * 
 * @param flights - All flights.
 */
void showPaginated(PtList flights);

/**
 * @brief Shows 100 flights, randomly.
 * 
 * @param flights - All flights. 
 */
void showRandom(PtList flights);

/**
 * @brief Function used to get all the flights from an airport.
 *
 * @param flights - list with flights.
 * @param airport - airport. 
 *
 **/
PtList getFlights(PtList flights, char* airport);

/**
 * @brief Function used to show all the flight data from an airport requested to the user.
 *
 * @param flights - list with flights.
 * @param airport - array of chars referenncing an airport.
 *
 * @return list with the flight data.
 *
 **/
void showWF(PtList flights, char* airport);

/**
 * @brief Function used to show a list of airlines with registered flights.
 *
 * @param flights - list with flights.
 * @param airlines - array of airlines referencing airlines.
 *
 **/
void listAR(PtList flights, Airline* airlines);

/**
 * @brief Function used to show a list of airports with registered flights.
 *
 * @param flights - list with flights.
 * @param airports - map with airports.
 *
 **/
void listAP(PtList flights, PtMap airports);

/**
 * @brief Function that shows the average of distances done in every flight for every day, only week days and only weekends.
 * It also shows the average of the distances done by the flights that departured at an airport requested to the user.
 *
 * @param flights - list with flights.
 * @param airportIataCode - Array of chars referencing to the iatacode of an airport.
 **/
void average(PtList flights, char airportIataCode[4]);

/**
 * @brief Function that shows for every known airline the airport list through were the flights pass.
 *
 * @param flight - list with flights.
 * @param airlines - Array with airlines referencing airlines.
 * @param airports - map with airports.
 *
 **/
void showAP(PtList flights, Airline* airlines, PtMap airports);

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
 * @bug Can't consider the times of arrival and departure.
 **/
void tsp(PtList flights, PtMap airports, int number);

/**
 * @brief Calculates the time it takes to go from an airport to another.
 * 
 * @param flights - All flights.
 * @param airportOrigin - Origin airport.
 * @param airportDestiny - Destiny airport.
 * @return int - Travel time.
 */
int travelTimeFromAirportToAirport(PtList flights, Airport airportOrigin, Airport airportDestiny);

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
void airportsOrderedCity(PtMap airports, int size, bool ascending, Airport* airportsTemp);

/**
 * @brief Function that orders the airports by longitude.
 * 
 * @param airports - map with airports.
 * @param size - Integer variable referencing a size.
 * @param airportsTemp - Array of airports referencing airports.
 * 
 **/
void airportsOrderedLongitude(PtMap airports, int size, Airport* airportsTemp);

/**
 * @brief Function that orders the airports by latitude.
 * 
 * @param airports - map with airports.
 * @param size - Integer variable referencing a size.
 * @param airportsTemp - Array of airports referencing airports.
 * 
 **/
void airportsOrderedLatitude(PtMap airports, int size, Airport* airportsTemp);

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

/**
 * @brief Function that returns the number of flights that arrived on time or in a tolerance between 0 an 30 minutes.
 *
 * @param flights - list with flights.
 * @param number - integer variable referecing to a number.
 *
 * @return number of flights on time (arrival)
 *
 **/
int ontimeArrival(PtList flights, Airline airline, int number);

/**
 * @brief Function that returns the number of flights that departured on time or in a tolerance between 0 an 30 minutes.
 *
 * @param flights - list with flights.
 * @param number - integer variable referecing to a number.
 *
 * @return number of flights on time (departure)
 **/
int ontimeDeparture(PtList flights, Airline airline, int number);

/**
 * @brief Calculates all the possibles results from the start of an index. The results appear in this order {indexBeginning numberBetween indexBeginning}
 * 
 * @param arrayValues - Array thats gonna contain all the possible results.
 * @param array - Array with the possible resutls.
 * @param left - Where we begin the permutations.
 * @param right - Where we end the permutations.
 * @param indexBeginning - The index that must be at the begin of the permutation.
 */
void permutations(int** arrayValues, int* array, int left, int right, int indexBeginning);

/**
 * @brief Calculates the factorial of an number.
 * 
 * @param number - Number to calculate the factorial.
 * @return int - Number calculated.
 */
int factorial(int number);

/**
 * @brief Swaps two numbers.
 * 
 * @param x - Number to swap.
 * @param y - Number to swap.
 */
void swapNumbers(int* x, int*y);

/**
 * @brief Get the Total Travel Time of an array of index.
 * 
 * @param size - Size of the array.
 * @param array - Array of indexes to calculate the travel time.
 * @param values - Matrix containing all the possible results.
 * @return int - Travel time.
 */
int getTotalTravelTime(int size, int* array, int** values);

/**
 * @brief Returns the index of the minimumTravelTime array.
 * 
 * @param arrayValues - Contains all the possible results.
 * @param size - Size of the array.
 * @param values - Matrix containing all the possible results.
 * @param totalTime - Pointer that receives the total time of travel.
 * @return int - Index of the minimum travel time array.
 */
int indexWithMinimumTravelTime(int** arrayValues, int size, int** values, int* totalTime);

/**
 * @brief Displays menu that the user can select one of the options, where it returns the number of the option.
 * 
 * @return int - Number of the option.
 */
int tspMenu();

/**
 * @brief It calculates the number of flights that were on time on their flight, either on departure and either on arrival. This calculations is done to all airlines and to a single one separated.
 * 
 * @param flights - All flights.
 * @param airlines - All airlines.
 */
void onTime(PtList flights, Airline* airlines);

/**
 * @brief Get the Flight By the airport of origin and destination.
 * 
 * @param flights - List of flights.
 * @param airportOrig - IataCode from the airport of origin.
 * @param airportDest - IataCode from the airport of destination.
 * @param flightToReturn - Flight sent by reference.
 */
void getFlightByOrigDest(PtList flights, MapKey airportOrig, MapKey airportDest, Flight* flightToReturn);



