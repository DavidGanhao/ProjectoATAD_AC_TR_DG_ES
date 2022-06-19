#pragma once
#include "flight.h"
#include "airline.h"
#include "airport.h"
#include "list.h"
#include "map.h"

int loadap(PtMap airports, int howMany);

int loadar(Airline* airlines, int howMany);

int loadf(PtMap airports, PtList flights, int howMany);

void clear(Airline* airlines, PtMap airports, PtList flights);

void quit(Airline* airlines, PtMap airports, PtList flights);

void showAll(PtList flights);

void showPaginated(PtList flights);

void showRandom(PtList flights);

PtList getFlights(PtList flights, char* airport);

void showWF(PtList flights, char* airport);

void listAR(PtList flights, Airline* airlines);

void listAP(PtList flights, PtMap airports);

void onTime(PtList flights);

void average(PtList flights, Airport airport);

void showAP();

void topN(PtList flights, int number);

void tsp(PtList flights, PtMap airports, MapKey airportIataCode);

int travelTimeFromAirportToAirport(PtList flights, char* airportOrigin, char* airportDestiny);

void airport_s(PtMap airports);

void airportsOrderedCity(PtMap airports, int size, bool ascending, Airport* airportsTemp);

void *airportsOrderedLongitude(PtMap airports, int size, Airport* airportsTemp);

void *airportsOrderedLatitude(PtMap airports, int size, Airport* airportsTemp);

int calculateTravelTime(Airport originAirport, Airport destinationAirport, Time scheduledDeparture, Time scheduleArrival);

PtList flightsAssociatedToAirport(Airport airport, PtList flights);

PtMap airportWithFlights(PtMap airports, PtList flights);

void airportsMethod(PtMap airports, PtList flights);

void ontimeArrival(PtList flights);

void ontimeDeparture(PtList flights);



