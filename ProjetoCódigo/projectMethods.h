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

PtList getWF(PtList flights);

void showWF(PtList flights);

void listAR(PtList flights);

void listAP(PtList flights, PtMap airports);

void onTime(PtList flights);

void average(PtList flights, Airport airport);

void showAP();

void topN(PtList flights, int number);

void tsp(PtList flights, Airport airport);

void airport_s(PtMap airports);

int calculateTravelTime(Airport originAirport, Airport destinationAirport, Time scheduledDeparture, Time scheduleArrival);



