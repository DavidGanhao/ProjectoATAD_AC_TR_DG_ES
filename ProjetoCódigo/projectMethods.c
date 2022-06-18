#include "projectMethods.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "input.h"

int loadar(Airline* airlines, int howMany){
    FILE* stream = fopen("csv_data/airlines.csv","r");
    if(stream == NULL){
        printf("File not found.\n");
        return 0;
    }

    int count = 0;
    char line[1024];
    fgets(line, 1024, stream);
    while(fgets(line, 1024, stream)){
        if(count == howMany) break;
        char* tmp = strdup(line);
        char** tokens = splitString(tmp, 2, ";");
        airlines[count++] = airlineCreate(tokens[0], tokens[1]);
        free(tokens);
        free(tmp);
    }
    fclose(stream);

    printf("\n%d airlines imported\n", count);
    return count;
}


int loadap(PtMap airports, int howMany){
    if(airports == NULL) return 0;
    FILE* stream = fopen("csv_data/airports.csv","r");
    if(stream == NULL){
        printf("File not found.\n");
        return 0;
    }

    int count = 0;
    char line[1024];
    fgets(line, 1024, stream);
    while(fgets(line, 1024, stream)){
        if(count == howMany) break;
        char* tmp = strdup(line);
        char** tokens = splitString(tmp, 7, ";");
        mapPut(airports, stringCodeCreate(tokens[0]), createAirport(tokens[0], tokens[1], tokens[2], tokens[3], atof(tokens[4]), atof(tokens[5]), atoi(tokens[6])));
        count++;
        free(tokens);
        free(tmp);
    }
    fclose(stream);
    
    printf("\n%d airports imported\n", count);
    return count;
}

int loadf(PtMap airports, PtList flights, int howMany){
    if(airports == NULL) return 0;
    if(flights == NULL) return 0;
    if(mapIsEmpty(airports) == MAP_EMPTY){
        printf("Please load airport data first\n");
        return 0;
    }
    FILE* stream = fopen("csv_data/flights.csv","r");
    if(stream == NULL){
        printf("File not found.\n");
        return 0;
    }

    int count = 0;
    char line[1024];
    fgets(line, 1024, stream);
    while (fgets(line, 1024, stream))
    {
        if(count == howMany) break;
        char* tmp = strdup(line);
        char** tokens = splitString(tmp, 11, ";");
        MapValue originAirport;
        MapValue destinationAirport;
        int error1 = mapGet(airports, stringCodeCreate(tokens[4]), &originAirport);
        int error2 = mapGet(airports, stringCodeCreate(tokens[5]), &destinationAirport);
        if(error1 == MAP_UNKNOWN_KEY || error2 == MAP_UNKNOWN_KEY) continue;
        Time scheduleDeparture = convertCharTokenToTime(tokens[6]);
        Time scheduleArrival = convertCharTokenToTime(tokens[9]);
        listAdd(flights, count++, createFlight(atoi(tokens[0]), atoi(tokens[1]), tokens[2], atoi(tokens[3]), tokens[4], tokens[5],
         scheduleDeparture, convertCharTokenToTime(tokens[7]), atoi(tokens[8]), scheduleArrival,
          convertCharTokenToTime(tokens[10]), calculateTravelTime((Airport) originAirport, (Airport) destinationAirport, scheduleDeparture, scheduleArrival)));
        free(tokens);
        free(tmp);
    }
    fclose(stream);

    printf("\n%d flights imported\n", count);
    return count;

}

void clear(Airline* airlines, PtMap airports, PtList flights){
    int airlineSize = 0;
    for(int i = 0; true; i++){
        if(strlen(airlines[i].iatacode) == 0 || strlen(airlines[i].name) == 0){
            airlineSize = i;
            break;
        }
    }
    int airportSize;
    int flightsSize;
    mapSize(airports, &airportSize);
    listSize(flights, &flightsSize);
    printf("%d records deleted from airlines\n", airlineSize);
    printf("%d records deleted from airports\n", airportSize);
    printf("%d records deleted from flights\n", flightsSize);
    Airline* newAirlines;
    airlines = newAirlines;
    free(newAirlines);
    mapClear(airports);
    listClear(flights);
}

void quit(Airline* airlines, PtMap airports, PtList flights){
    free(airlines);
    mapDestroy(&airports);
    listDestroy(&flights);
    printf("Okey, Goodbye ...\n\n");
}

int calculateTravelTime(Airport originAirport, Airport destinationAirport, Time scheduledDeparture, Time scheduleArrival){
    int timeWithoutTimeZone = timeDiffSpecial(scheduledDeparture, scheduleArrival);;
    int minutesToAdd = (destinationAirport.timeZone - originAirport.timeZone)*60;
    return (timeWithoutTimeZone+minutesToAdd);
}

