#include "projectMethods.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "input.h"
#include "math.h"
#include "utils.h"
#define AIRLINESIZE 14
#define AIRPORTSIZE 319

int loadar(Airline *airlines, int howMany)
{
    FILE *stream = fopen("csv_data/airlines.csv", "r");
    if (stream == NULL)
    {
        printf("File not found.\n");
        return 0;
    }

    int count = 0;
    char line[1024];
    fgets(line, 1024, stream);
    while (fgets(line, 1024, stream))
    {
        if (count == howMany)
            break;
        char *tmp = strdup(line);
        char **tokens = splitString(tmp, 2, ";");
        airlines[count++] = airlineCreate(tokens[0], tokens[1]);
        free(tokens);
        free(tmp);
    }
    fclose(stream);

    printf("\n\n%d airlines imported\n", count);
    return count;
}
// POR FAZER
int loadap(PtMap airports, int howMany)
{
    if (airports == NULL)
        return 0;
    FILE *stream = fopen("csv_data/airports.csv", "r");
    if (stream == NULL)
    {
        printf("File not found.\n");
        return 0;
    }

    int count = 0;
    char line[1024];
    fgets(line, 1024, stream);
    while (fgets(line, 1024, stream))
    {
        if (count == howMany)
            break;
        char *tmp = strdup(line);
        char **tokens = splitString(tmp, 7, ";");
        char **valueLongitude = splitString(tokens[5], 2, ",");
        char **valueLatitude = splitString(tokens[4], 2, ",");
        float valueLong = atof(valueLongitude[1]);
        float valueLat = atof(valueLatitude[1]);
        valueLong /= pow(10, strlen(valueLongitude[1]));
        valueLat /= pow(10, strlen(valueLatitude[1]));
        mapPut(airports, stringCodeCreate(tokens[0]), createAirport(tokens[0], tokens[1], tokens[2], tokens[3], (valueLat + atof(valueLatitude[0])), (valueLong + atof(valueLongitude[0])), atoi(tokens[6])));
        count++;
        free(tokens);
        free(tmp);
        free(valueLatitude);
        free(valueLongitude);
    }
    fclose(stream);

    printf("\n\n%d airports imported\n", count);
    return count;
}

int loadf(PtMap airports, PtList flights, int howMany)
{
    if (airports == NULL)
        return 0;
    if (flights == NULL)
        return 0;
    if (mapIsEmpty(airports))
    {
        printf("Please load airport data first\n");
        return 0;
    }
    FILE *stream = fopen("csv_data/flights.csv", "r");
    if (stream == NULL)
    {
        printf("File not found.\n");
        return 0;
    }

    int count = 0;
    char line[1024];
    fgets(line, 1024, stream);
    while (fgets(line, 1024, stream))
    {
        if (count == howMany)
            break;
        char *tmp = strdup(line);
        char **tokens = splitString(tmp, 11, ";");
        MapValue originAirport;
        MapValue destinationAirport;
        int error1 = mapGet(airports, stringCodeCreate(tokens[4]), &originAirport);
        int error2 = mapGet(airports, stringCodeCreate(tokens[5]), &destinationAirport);
        if (error1 == MAP_UNKNOWN_KEY || error2 == MAP_UNKNOWN_KEY)
            continue;
        Time scheduleDeparture = convertCharTokenToTime(tokens[6]);
        Time scheduleArrival = convertCharTokenToTime(tokens[9]);
        listAdd(flights, count++, createFlight(atoi(tokens[0]), atoi(tokens[1]), tokens[2], atoi(tokens[3]), tokens[4], tokens[5], scheduleDeparture, convertCharTokenToTime(tokens[7]), atoi(tokens[8]), scheduleArrival, convertCharTokenToTime(tokens[10]), calculateTravelTime((Airport)originAirport, (Airport)destinationAirport, scheduleDeparture, scheduleArrival)));
        free(tokens);
        free(tmp);
    }
    fclose(stream);

    printf("\n\n%d flights imported\n", count);
    return count;
}

void clear(Airline *airlines, PtMap airports, PtList flights)
{
    int airlineSize = 0;
    for (int i = 0; true; i++)
    {
        if (strlen(airlines[i].iatacode) == 0 || strlen(airlines[i].name) == 0)
        {
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
    Airline *newAirlines;
    airlines = newAirlines;
    free(newAirlines);
    mapClear(airports);
    listClear(flights);
}

void quit(Airline *airlines, PtMap airports, PtList flights)
{
    free(airlines);
    mapDestroy(&airports);
    listDestroy(&flights);
    printf("Okey, Goodbye ...\n\n");
}

int calculateTravelTime(Airport originAirport, Airport destinationAirport, Time scheduledDeparture, Time scheduleArrival)
{
    int timeWithoutTimeZone = timeDiffSpecial(scheduledDeparture, scheduleArrival);
    ;
    int minutesToTakeOut = (destinationAirport.timeZone - originAirport.timeZone) * 60;
    return (timeWithoutTimeZone - minutesToTakeOut);
}

void topN(PtList flights, int number)
{
    int size;
    listSize(flights, &size);
    Flight *flightsTemp = (Flight *)malloc(sizeof(Flight) * size);
    for (int i = 0; i < size; i++)
    {
        Flight temp;
        listGet(flights, i, &temp);
        flightsTemp[i] = temp;
    }
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size - 1 - i; j++)
        {
            if (flightsTemp[j].arrivalDelay == flightsTemp[j + 1].arrivalDelay)
            {
                if (flightsTemp[j].flightNumber > flightsTemp[j + 1].flightNumber)
                {
                    swapFlight(&flightsTemp[j], &flightsTemp[j + 1]);
                }
            }
            if (flightsTemp[j].arrivalDelay < flightsTemp[j + 1].arrivalDelay)
            {
                swapFlight(&flightsTemp[j], &flightsTemp[j + 1]);
            }
        }
    }

    printf("\n\nFLIGHTS ORDERED BY ARRIVAL DELAY (%d)\n\n", number);
    timeInfoFlightArrival(flightsTemp, 0, number);
    printf("\n\nFINISHED\n\n");
}

void tsp(PtList flights, PtMap airports, MapKey airportIataCode)
{
    if (flights == NULL || airports == NULL)
    {
        printf("\nImpossible to make operation\n\n");
        return;
    }
}

int travelTimeFromAirportToAirport(PtList flights, char *airportOrigin, char *airportDestiny)
{
}

void ontimeMenu(PtList flights, Airline* airlines)
{
    PtList aux = listCreate();
    bool condition = true;
    int choice = -1;
    int flightSize;
    int airlineSize = AIRLINESIZE;
    listSize(flights, &flightSize);
    while(condition)
    {
        printf("\n\nONTIME MENU\n");
        printf("Insert a tolerance (between 0 and 30 minutes): ");
        if(choice > 30){
            printf("Tolerance out of bounds!");
            return;
        }
        readInteger(&choice);
        printf("\n");
        printf("Airline\t\tOT_Departures\t\tOT_Arrivals\n");
        for(int i = 0; i < airlineSize; i++){
            for(int j = 0; j < flightSize; j++){
            ListElem flight;
            listGet(flights, j, &flight);
            if(strcmp(airlines[i].iatacode, flight.airline) == 0){
                int size; listSize(aux,&size);
                listAdd(aux, size, flight);
            }
            }
            printf(" %s\t\t", airlines[i].iatacode);
            printf(" %4d\t\t", ontimeDeparture(aux, choice));
            printf(" %4d\t\t\n", onTimeArrival(aux, choice));
            listClear(aux);   
        }  
    }
    listDestroy(aux);
}

void showAll(PtList flights)
{
    bool condition = true;
    int choice = -1;
    while (condition)
    {
        printf("\n\nSHOWALL MENU\n");
        printf("1 - Show all flights (paginated by 20)\n");
        printf("2 - Show 100 random flight data\n");
        printf("3 - GO BACK\n> ");
        readInteger(&choice);
        switch (choice)
        {
        case 1:
            showPaginated(flights);
            break;

        case 2:
            showRandom(flights);
            break;
        case 3:
            return;

        default:
            printf("\n\nUnknown answer.\n");
            break;
        }
    }
}

void showPaginated(PtList flights)
{
    bool condition = true;
    int start = 0;
    int choice = -1;
    int size;
    listSize(flights, &size);
    Flight *flightsTemp = (Flight *)malloc(sizeof(Flight) * size);
    for (int i = 0; i < size; i++)
    {
        ListElem flight;
        listGet(flights, i, &flight);
        flightsTemp[i] = (Flight)flight;
    }
    timeInfoFlightArrival(flightsTemp, start, start + 20);
    while (condition)
    {
        printf("\n");
        printf("\n\nSHOWALL PAGINATED\n");
        printf("1. Next 20\n");
        printf("2. Return\n> ");
        readInteger(&choice);
        switch (choice)
        {
        case 1:
            start += 20;
            timeInfoFlightArrival(flightsTemp, start, start + 20);
            break;

        case 2:
            condition = false;
            break;

        default:
            printf("\n\nUnknown answer.\n");
            break;
        }
    }
    free(flightsTemp);
}

void showRandom(PtList flights)
{
    Flight *flightsTemp = (Flight *)malloc(sizeof(Flight) * 100);
    for (int i = 0; i < 100; i++)
    {
        ListElem flight;
        listGet(flights, rand() % 11515 + 1, &flight);
        flightsTemp[i] = (Flight)flight;
    }
    timeInfoFlightArrival(flightsTemp, 0, 100);
    free(flightsTemp);
}

void showWF(PtList flights, char *airport)
{
    if (flights == NULL)
        return;
    if (listIsEmpty(flights))
        return;
    PtList newList = getFlights(flights, airport);
    if (newList == NULL)
        return;
    int size;
    listSize(newList, &size);
    Flight *flightsTemp = (Flight *)malloc(sizeof(Flight) * size);
    for (int i = 0; i < size; i++)
    {
        ListElem flight;
        listGet(newList, i, &flight);
        flightsTemp[i] = (Flight)flight;
    }
    timeInfoFlightArrival(flightsTemp, 0, size);
    listDestroy(&newList);
}

PtList getFlights(PtList flights, char *airport)
{
    PtList newList = listCreate();
    int count = 0;
    int size;
    listSize(flights, &size);
    for (int i = 0; i < size; i++)
    {
        ListElem flight;
        listGet(flights, i, &flight);
        if (strcmp(airport, flight.originAirport) == 0)
        {
            listAdd(newList, count++, flight);
        }
    }
    if (count == 0)
    {
        listDestroy(&newList);
        printf("\n\nFlight data not available for %s.\n", airport);
        return NULL;
    }
    return newList;
}

void listAR(PtList flights, Airline *airlines)
{
    if (flights == NULL)
        return;
    if (listIsEmpty(flights))
        return;
    int flightSize;
    int airlineSize = 14;
    listSize(flights, &flightSize);
    printf("\n\nLIST OF AIRLINES:\n");
    for (int i = 0; i < airlineSize; i++)
    {
        for (int j = 0; j < flightSize; j++)
        {
            ListElem flight;
            listGet(flights, j, &flight);
            if (strcmp(airlines[i].iatacode, flight.airline) == 0)
            {
                printf("Airline: %s\n", airlines[i].name);
                break;
            }
        }
    }
}

void listAP(PtList flights, PtMap airports)
{
    if (flights == NULL || airports == NULL)
        return;
    if (listIsEmpty(flights))
        return;
    if (mapIsEmpty(airports))
        return;
    int flightSize;
    int airportSize = 319;
    listSize(flights, &flightSize);
    MapKey *keys = mapKeys(airports);
    printf("\n\nLIST OF AIRPORTS:\n");
    for (int i = 0; i < airportSize; i++)
    {
        Airport airport;
        mapGet(airports, keys[i], &airport);
        for (int j = 0; j < flightSize; j++)
        {
            ListElem flight;
            listGet(flights, j, &flight);
            if (strcmp(flight.originAirport, keys[i].code) == 0 || strcmp(flight.destinationAirport, keys[i].code) == 0)
            {
                printf("%4s : %s; %s; %s\n", airport.iataCode, airport.airport, airport.city, airport.state);
                break;
            }
        }
    }
}

void showAP(PtList flights, Airline* airlines, PtMap airports)
{
    if(airports == NULL) return;
    if(mapIsEmpty(airports)) return;
    PtMap auxMap = mapCreate(0);
    PtList auxFlights = listCreate();
    if(flights == NULL) return;
    if(listIsEmpty(flights)) return;
    if(airlines == NULL) return;
    int count = 0;
    int flightSize;
    listSize(flights, &flightSize);
    for(int i = 0; i < AIRLINESIZE; i++){
        for(int j = 0; j < flightSize; j++){
            ListElem flight;
            listGet(flights, j, &flight);
            if(strcmp(airlines[i].iatacode, flight.airline) == 0){
                int size; mapSize(auxMap,&size);
                listAdd(auxFlights, size, flight);
            }
        }
        listSize(auxFlights, &flightSize);
        for(int t = 0; t < flightSize; t++){
            ListElem flight;
            listGet(auxFlights, t, &flight);
            MapValue value;
            mapGet(airports, stringCodeCreate(flight.originAirport) , &value);
            mapPut(auxMap, stringCodeCreate(flight.originAirport), value);
            mapGet(airports, stringCodeCreate(flight.destinationAirport), &value);
            mapPut(auxMap, stringCodeCreate(flight.destinationAirport), value);  
        }
        mapSize(airports, &count);
        printf(" %s passes through %d airports.\n", airlines->name, count);
        MapKey* mapKeysAux = mapKeys(auxMap);
        for(int k = 0; k<count; k++){
            printf(" %s\n",mapKeysAux[k]);
        }
        printf("\n");
        listClear(auxFlights);
        mapClear(auxMap);
    }
    listDestroy(&auxFlights);
    mapDestroy(&auxMap);
}

void airport_s(PtMap airports)
{
    bool condition = true;
    int choice = -1;
    int size;
    mapSize(airports, &size);
    Airport *airportsTemp = (Airport *)malloc(sizeof(Airport));
    while (condition)
    {
        printf("\n\nAIRPORTS_S Menu\n");
        printf("1. Sort by City Acending\n");
        printf("2. Sort by City Descending\n");
        printf("3. Sort by Latitude from N to S\n");
        printf("4. Sort by Longitude from E to W\n");
        printf("5. Return\n> ");
        readInteger(&choice);
        switch (choice)
        {
        case 1:
            airportsOrderedCity(airports, size, true, airportsTemp);
            printAirportsInfo(airportsTemp, 0, size);
            break;
        case 2:
            airportsOrderedCity(airports, size, false, airportsTemp);
            printAirportsInfo(airportsTemp, 0, size);
            break;
        case 3:
            airportsOrderedLatitude(airports, size, airportsTemp);
            printAirportsInfo(airportsTemp, 0, size);
            break;
        case 4:
            airportsOrderedLongitude(airports, size, airportsTemp);
            printAirportsInfo(airportsTemp, 0, size);
            break;
        case 5:
            condition = false;
            break;
        default:
            printf("\n\nUnknown command.\n");
            break;
        }
    }
    free(airportsTemp);
}

void airportsOrderedCity(PtMap airports, int size, bool ascending, Airport *airportsTemp)
{
    MapKey *keys = mapKeys(airports);
    for (int i = 0; i < size; i++)
    {
        Airport temp;
        mapGet(airports, keys[i], &temp);
        airportsTemp[i] = temp;
    }
    if (ascending)
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size - 1 - i; j++)
            {
                if (strcmp(airportsTemp[j].city, airportsTemp[j + 1].city) > 0)
                {
                    swapAirport(&airportsTemp[j], &airportsTemp[j + 1]);
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size - 1 - i; j++)
            {
                if (strcmp(airportsTemp[j].city, airportsTemp[j + 1].city) < 0)
                {
                    swapAirport(&airportsTemp[j], &airportsTemp[j + 1]);
                }
            }
        }
    }
}

void *airportsOrderedLongitude(PtMap airports, int size, Airport *airportsTemp)
{
    MapKey *keys = mapKeys(airports);
    for (int i = 0; i < size; i++)
    {
        Airport temp;
        mapGet(airports, keys[i], &temp);
        airportsTemp[i] = temp;
    }
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size - 1 - i; j++)
        {
            if (airportsTemp[j].longitude < airportsTemp[j + 1].longitude)
            {
                swapAirport(&airportsTemp[j], &airportsTemp[j + 1]);
            }
        }
    }
}

void *airportsOrderedLatitude(PtMap airports, int size, Airport *airportsTemp)
{
    MapKey *keys = mapKeys(airports);
    for (int i = 0; i < size; i++)
    {
        Airport temp;
        mapGet(airports, keys[i], &temp);
        airportsTemp[i] = temp;
    }
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size - 1 - i; j++)
        {
            if (airportsTemp[j].latitude < airportsTemp[j + 1].latitude)
            {
                swapAirport(&airportsTemp[j], &airportsTemp[j + 1]);
            }
        }
    }
}

void average(PtList flights, Airport airport){
    int i, j;
}

void airportsMethod(PtMap airports, PtList flights)
{
    PtMap mapWithAirports = airportWithFlights(airports, flights);
    MapKey *keys = mapKeys(mapWithAirports);
    int size;
    int flightsSize;
    int numDepDelays = 0;
    int totalNumDepDelays = 0;
    float total = 0;
    float avgDepDelays = 0;
    float totalAvg = 0;
    mapSize(mapWithAirports, &size);
    printf("  ---- Airports ----------\n\n");
    printf("%-10s %-70s %-35s %-15s    %-20s     %-20s\n", "Iata Code", "Airport", "City", "Number Flights", "Num. Departure Delays", "Avg. Departure Delays");
    for (int i = 0; i < size; i++)
    {
        MapValue airport;
        mapGet(mapWithAirports, keys[i], &airport);
        PtList list = flightsAssociatedToAirport(airport, flights);
        listSize(list, &flightsSize);
        for (int j = 0; j < flightsSize; j++)
        {
            ListElem flight;
            listGet(list, j, &flight);
            if (flight.departureDelay > 15 && equalsStringIgnoreCase(flight.destinationAirport, airport.iataCode))
            {
                total += flight.departureDelay;
                numDepDelays++;
            }
        }
        avgDepDelays = (total) / numDepDelays;
        printAirportInfoAgregated(airport, flightsSize, numDepDelays, avgDepDelays);
        totalNumDepDelays += numDepDelays;
        totalAvg += avgDepDelays;
        numDepDelays = 0;
        avgDepDelays = 0;
        total = 0;
        listDestroy(&list);
    }
    printf("\n\n%15s %-100s   %25s %-20d    %-25.2f\n\n", "", "ALL AIRPORTS", "", totalNumDepDelays, totalAvg / size);
    mapDestroy(&mapWithAirports);
}

PtMap airportWithFlights(PtMap airports, PtList flights)
{
    PtMap map = mapCreate(20);
    MapKey *keys = mapKeys(airports);
    int numberOfAirports;
    int numberOfFlights;
    mapSize(airports, &numberOfAirports);
    listSize(flights, &numberOfFlights);
    for (int i = 0; i < numberOfAirports; i++)
    {
        MapValue airport;
        mapGet(airports, keys[i], &airport);
        for (int j = 0; j < numberOfFlights; j++)
        {
            ListElem flight;
            listGet(flights, j, &flight);
            if (equalsStringIgnoreCase(flight.destinationAirport, airport.iataCode) || equalsStringIgnoreCase(flight.originAirport, airport.iataCode))
            {
                mapPut(map, stringCodeCreate(airport.iataCode), airport);
                break;
            }
        }
    }
    return map;
}

PtList flightsAssociatedToAirport(Airport airport, PtList flights)
{
    PtList list = listCreate();
    int count = 0;
    int size;
    listSize(flights, &size);
    for (int i = 0; i < size; i++)
    {
        ListElem flight;
        listGet(flights, i, &flight);
        if (strcmp(flight.originAirport, airport.iataCode) == 0 || strcmp(flight.destinationAirport, airport.iataCode) == 0)
        {
            listAdd(list, count++, flight);
        }
    }
    return list;
}

int ontimeDeparture(PtList flights, int number){
    if(flights == NULL) return;
    if(listIsEmpty(flights)) return;
    if(number < 0 || number > 30){
        printf("Number out of bounds! Should be between 0 and 30.");
        return;
    }
    int flightSize;
    listSize(flights, &flightSize);
    int count = 0;
    for(int i = 0; i < flightSize; i++){
        ListElem flight;
        listGet(flights, i, &flight);
        if(timeDiffSpecial(flight.scheduledDeparture, flight.departureTime) <= number){
            count++;
        }
    }
    return count;
}

int ontimeArrival(PtList flights, int number){
    if(flights == NULL) return;
    if(listIsEmpty(flights)) return;
    if(number < 0 || number > 30){
        printf("Number out of bounds! Should be between 0 and 30.");
        return;
    }
    int flightSize;
    listSize(flights, &flightSize);
    int count = 0;
    for(int i = 0; i < flightSize; i++){
        ListElem flight;
        listGet(flights, i, &flight);
        if(timeDiffSpecial(flight.scheduledArrival, flight.arrivalTime) <= number){
            count++;
        }
    }
    return count;
}  


