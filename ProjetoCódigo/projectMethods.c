/**
 * @file projectMethods.c
 * @brief Implementations of all the methods for this project.
 * 
 * @author David Ganhão, Tomás Ramos e André Caetano.
 * @bug No known bugs.
 */

#include "projectMethods.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "input.h"
#include "math.h"
#include "utils.h"

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

void tsp(PtList flights, PtMap airports, int number)
{
    if (flights == NULL || airports == NULL)
    {
        printf("\nImpossible to make operation\n\n");
        return;
    }
    char airportIataCode[4] = "";
    int indexOfAirport = -1;
    int sizeOfMap;
    PtMap airportWithFlight = airportWithFlights(airports, flights);
    MapKey *keys = mapKeys(airportWithFlight);
    mapSize(airportWithFlight, &sizeOfMap);
    int **travelTimeAirportToAirport = (int **)malloc(sizeof(int *) * sizeOfMap);
    switch (number)
    {
    case 1:
        strcpy(airportIataCode, "ATL");
        break;
    case 2:
        strcpy(airportIataCode, "DEN");
        break;
    case 3:
        strcpy(airportIataCode, "DFW");
        break;
    case 4:
        strcpy(airportIataCode, "JFK");
        break;
    case 5:
        strcpy(airportIataCode, "LAS");
        break;
    case 6:
        strcpy(airportIataCode, "LAX");
        break;
    case 7:
        strcpy(airportIataCode, "MCO");
        break;
    case 8:
        strcpy(airportIataCode, "ORD");
        break;
    case 9:
        strcpy(airportIataCode, "SEA");
        break;
    case 10:
        strcpy(airportIataCode, "SFO");
        break;
    default:
        printf("\n\nERROR\n\n");
        return;
    }
    for (int i = 0; i < sizeOfMap; i++)
    {
        if (equalsStringIgnoreCase(keys[i].code, airportIataCode))
        {
            indexOfAirport = i;
            break;
        }
    }
    for (int j = 0; j < sizeOfMap; j++)
    {
        travelTimeAirportToAirport[j] = (int *)malloc(sizeof(int) * sizeOfMap);
    }
    for (int i = 0; i < sizeOfMap; i++)
    {
        Airport airportOrigin;
        mapGet(airportWithFlight, keys[i], &airportOrigin);
        for (int j = 0; j < sizeOfMap; j++)
        {
            Airport airportDestiny;
            mapGet(airportWithFlight, keys[j], &airportDestiny);
            PtList flightsFromOrigin = flightsAssociatedToAirport(airportOrigin, flights);
            travelTimeAirportToAirport[i][j] = travelTimeFromAirportToAirport(flightsFromOrigin, airportOrigin, airportDestiny);
            listDestroy(&flightsFromOrigin);
        }
    }
    int size = factorial(sizeOfMap) / sizeOfMap;
    int *array = (int *)malloc(sizeof(int) * sizeOfMap);
    for (int i = 0; i < sizeOfMap; i++)
    {
        array[i] = i;
    }
    int **arrayValues = (int **)malloc(sizeof(int *) * size);
    for (int j = 0; j < size; j++)
    {
        arrayValues[j] = (int *)malloc(sizeof(int) * (sizeOfMap + 1));
    }
    permutations(arrayValues, array, 0, sizeOfMap - 1, indexOfAirport);
    int totalTime;
    int index = indexWithMinimumTravelTime(arrayValues, sizeOfMap, travelTimeAirportToAirport, &totalTime);
    int distance = 0;
    printf("\n\n ------- PATH ----------------------\n");
    printf("Ind.   Day   Day Of Week   Airline   Origin   Destination   Scheduled Departure   Scheduled Time   Distance   Schedule Arrival\n");
    for (int i = 0; i < sizeOfMap; i++)
    {   
        Flight flight;

        getFlightByOrigDest(flights, keys[arrayValues[index][i]], keys[arrayValues[index][i+1]], &flight);
        printf("%-3d    %-3d   %-11s   %-7s   %-6s   %-11s          %02d:%02d               %-8d      %-8d      %02d:%02d\n",
        i+1, flight.day, dayOfWeek(flight.dayOfWeek), flight.airline, flight.originAirport, flight.destinationAirport, flight.scheduledDeparture.hour, flight.scheduledDeparture.min,
        flight.scheduledTravelTime, flight.distance, flight.scheduledArrival.hour, flight.scheduledArrival.min);
        distance += flight.distance;
    }
    printf("\n\nTime traveled: %5d Minutes\nDistance traveled: %5d miles\n\n", totalTime, distance);
    printf("\n");

    mapDestroy(&airportWithFlight);
    free(array);
    for (int i = 0; i < size; i++)
    {
        free(arrayValues[i]);
    }
    free(arrayValues);
    free(keys);
    free(travelTimeAirportToAirport);
}

int tspMenu(PtList flights, PtMap airports)
{
    printf("\n ------ TSP -------------\n\n");
    printf(" 1 - ATL - Hartsfield-Jackson Atlanta International Airport\n");
    printf(" 2 - DEN - Denver International Airport\n");
    printf(" 3 - DFW - Dallas/Fort Worth International Airport\n");
    printf(" 4 - JFK - John F, Kennedy International Airport\n");
    printf(" 5 - LAS - McCarran International Airport\n");
    printf(" 6 - LAX - Los Angeles International Airport\n");
    printf(" 7 - MCO - Orlando International Airport\n");
    printf(" 8 - ORD - Chicago O'Hare International Airport\n");
    printf(" 9 - SEA - Seattle-Tacoma International Airport\n");
    printf("10 - SFO - San Francisco International Airport\n");
    int number;
    printf("\nInsert your origin airport:\n> ");
    readInteger(&number);
    tsp(flights, airports, number);
}

int travelTimeFromAirportToAirport(PtList flights, Airport airportOrigin, Airport airportDestiny)
{
    int size;
    listSize(flights, &size);
    for (int i = 0; i < size; i++)
    {
        Flight flight;
        listGet(flights, i, &flight);
        if (equalsStringIgnoreCase(flight.originAirport, airportOrigin.iataCode) && equalsStringIgnoreCase(flight.destinationAirport, airportDestiny.iataCode))
        {
            return flight.scheduledTravelTime;
        }
    }
    return -1;
}

void permutations(int **arrayValues, int *array, int left, int right, int indexBeginning)
{
    static int count = 0;
    if (count == 362880)
    {
        count = 0;
    }
    int i;
    if (left == right)
    {
        if (indexBeginning == array[0])
        {
            for (i = 0; i <= right; i++)
            {
                arrayValues[count][i] = array[i];
            }
            arrayValues[count++][right + 1] = array[0];
        }
        else
            return;
    }
    else
    {
        for (i = left; i <= right; i++)
        {
            swapNumbers((array + left), (array + i));
            permutations(arrayValues, array, left + 1, right, indexBeginning);

            swapNumbers((array + left), (array + i));
        }
    }
}

int getTotalTravelTime(int size, int *array, int **values)
{
    int total = 0;
    int valueOrigin = -1;
    int valueDestiny = -1;
    for (int i = 0; i < size; i++)
    {
        valueOrigin = array[i];
        valueDestiny = array[i + 1];
        if (valueOrigin == -1 || valueDestiny == -1)
            continue;
        total += 90 + values[valueOrigin][valueDestiny];
        valueOrigin = -1;
        valueDestiny = -1;
    }
    return total;
}

int indexWithMinimumTravelTime(int **arrayValues, int size, int **values, int *totalTime)
{
    int *arrayToEvaluate = (int *)malloc(sizeof(int) * (size + 1));
    int index = -1;
    int valueToEvaluate = -1;
    for (int i = 0; i < factorial(size) / size; i++)
    {
        for (int j = 0; j < size + 1; j++)
        {
            arrayToEvaluate[j] = arrayValues[i][j];
        }
        int newValue = getTotalTravelTime(size + 1, arrayToEvaluate, values);
        if (valueToEvaluate == -1)
        {
            valueToEvaluate = newValue;
            index = i;
            continue;
        }
        if (valueToEvaluate > newValue)
        {
            valueToEvaluate = newValue;
            index = i;
        }
    }
    *totalTime = valueToEvaluate;
    free(arrayToEvaluate);
    return index;
}

int factorial(int number)
{
    if (number == 0)
    {
        return 1;
    }
    else
    {
        return (number * factorial(number - 1));
    }
}

void swapNumbers(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
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

void showAP(PtList flights, Airline *airlines, PtMap airports)
{
    if (airports == NULL || mapIsEmpty(airports) || flights == NULL || listIsEmpty(flights) || airlines == NULL)
        return;
    PtMap auxMap = mapCreate(20);
    PtList auxFlights = listCreate();
    int count = 0;
    int countAuxFlights = 0;
    int flightSize;
    listSize(flights, &flightSize);
    for (int i = 0; i < AIRLINESIZE; i++)
    {
        for (int j = 0; j < flightSize; j++)
        {
            ListElem flight;
            listGet(flights, j, &flight);

            if (strcmp(airlines[i].iatacode, flight.airline) == 0)
            {
                listAdd(auxFlights, countAuxFlights++, flight);
            }
        }
        for (int t = 0; t < countAuxFlights; t++)
        {
            ListElem flight;
            listGet(auxFlights, t, &flight);
            MapValue value;
            mapGet(airports, stringCodeCreate(flight.originAirport), &value);
            mapPut(auxMap, stringCodeCreate(flight.originAirport), value);
            mapGet(airports, stringCodeCreate(flight.destinationAirport), &value);
            mapPut(auxMap, stringCodeCreate(flight.destinationAirport), value);
        }
        mapSize(auxMap, &count);
        printf("%s passes through %d airports.\n", airlines[i].name, count);
        MapKey *mapKeysAux = mapKeys(auxMap);
        for (int k = 0; k < count; k++)
        {
            printf(" %s\n", mapKeysAux[k].code);
        }
        printf("\n");
        free(mapKeysAux);
        listClear(auxFlights);
        mapClear(auxMap);
        countAuxFlights = 0;
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

void airportsOrderedLongitude(PtMap airports, int size, Airport *airportsTemp)
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

void airportsOrderedLatitude(PtMap airports, int size, Airport *airportsTemp)
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
    free(keys);
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
    free(keys);
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
        if (equalsStringIgnoreCase(flight.originAirport, airport.iataCode) || equalsStringIgnoreCase(flight.destinationAirport, airport.iataCode))
        {
            listAdd(list, count++, flight);
        }
    }
    return list;
}

void onTime(PtList flights, Airline *airlines)
{
    int number;
    printf("\n\n  ---- ON TIME MENU ------------\n\n");
    printf("Insert tolerance (between 0 and 30 minutes): ");
    readInteger(&number);
    if (number < 0 || number > 30)
    {
        printf("\n\nNUMBER INSERTED INVALID\n");
        return;
    }
    printf("\n\nAirline   OT_Departures   OT_Arrivals\n");
    for (int i = 0; i < AIRLINESIZE; i++)
    {
        printf("%-7s   %-13d   %-11d\n", airlines[i].iatacode, ontimeDeparture(flights, airlines[i], number), ontimeArrival(flights, airlines[i], number));
    }
    printf("\n\nEND\n\n");
}

int ontimeDeparture(PtList flights, Airline airline, int number)
{
    if (flights == NULL)
        return 0;
    if (listIsEmpty(flights))
        return 0;
    int flightSize;
    listSize(flights, &flightSize);
    int count = 0;
    for (int i = 0; i < flightSize; i++)
    {
        ListElem flight;
        listGet(flights, i, &flight);
        if (equalsStringIgnoreCase(flight.airline, airline.iatacode) && (flight.departureDelay <= number))
        {
            count++;
        }
    }
    return count;
}

int ontimeArrival(PtList flights, Airline airline, int number)
{
    if (flights == NULL)
        return 0;
    if (listIsEmpty(flights))
        return 0;
    int flightSize;
    listSize(flights, &flightSize);
    int count = 0;
    for (int i = 0; i < flightSize; i++)
    {
        ListElem flight;
        listGet(flights, i, &flight);
        if (equalsStringIgnoreCase(flight.airline, airline.iatacode) && (flight.arrivalDelay <= number))
        {
            count++;
        }
    }
    return count;
}

void average(PtList flights, char airportIataCode[4])
{
    PtList aux = listCreate();
    float everyday, weekDay, weekend;
    float totalDistanceWeekDay = 0, totalDistanceWeekend = 0;
    int size, sizeAux = 0, countWeekDay = 0, countWeekEnd = 0;
    listSize(flights, &size);
    printf("Airport   All Days   Only Week Days   Weekend\n");
    for (int i = 0; i < size; i++)
    {
        ListElem flight;
        listGet(flights, i, &flight);

        if (equalsStringIgnoreCase(airportIataCode, flight.originAirport))
        {
            listAdd(aux, sizeAux, flight);
            sizeAux++;
        }
        if (flight.dayOfWeek >= 1 && flight.dayOfWeek <= 5)
        {
            totalDistanceWeekDay += flight.distance;
            countWeekDay++;
        }
        else if (flight.dayOfWeek == 6 || flight.dayOfWeek == 7)
        {
            totalDistanceWeekend += flight.distance;
            countWeekEnd++;
        }
    }
    everyday = (totalDistanceWeekDay+totalDistanceWeekend) / (countWeekDay+countWeekEnd);
    weekDay = totalDistanceWeekDay / countWeekDay;
    weekend = totalDistanceWeekend / countWeekEnd;

    printf("%-7s   %-8.2f   %-14.2f   %-8.2f\n", " *", everyday, weekDay, weekend);
    everyday = 0;
    weekDay = 0;
    weekend = 0;
    totalDistanceWeekDay = 0;
    totalDistanceWeekend = 0;
    countWeekDay = 0;
    countWeekEnd = 0;

    for (int i = 0; i < sizeAux; i++)
    {
        ListElem flight;
        listGet(aux, i, &flight);

        if (flight.dayOfWeek >= 1 && flight.dayOfWeek <= 5)
        {
            totalDistanceWeekDay += flight.distance;
            countWeekDay++;
        }
        else if (flight.dayOfWeek == 6 || flight.dayOfWeek == 7)
        {
            totalDistanceWeekend += flight.distance;
            countWeekEnd++;
        }
    }
    everyday = (totalDistanceWeekDay+totalDistanceWeekend) / (countWeekDay+countWeekEnd);
    weekDay = totalDistanceWeekDay / countWeekDay;
    weekend = totalDistanceWeekend / countWeekEnd;

    printf("%-7s   %-8.2f   %-14.2f   %-8.2f\n", airportIataCode, everyday, weekDay, weekend);
    listDestroy(&aux);
}

void getFlightByOrigDest(PtList flights, MapKey airportOrig, MapKey airportDest, Flight* flightToReturn){
    int size;
    listSize(flights, &size);
    for(int i = 0; i < size; i++){
        Flight flight;
        listGet(flights, i, &flight);
        if(equalsStringIgnoreCase(airportOrig.code, flight.originAirport) && equalsStringIgnoreCase(airportDest.code, flight.destinationAirport)){
            *flightToReturn = flight;
            break;
        }
    }
}
