#include "airline.h"
#include "input.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

int loadar(Airline* airlines, int howMany){
    FILE* stream = fopen("csv_data/airlines.csv","r");
    if(stream == NULL){
        printf("File not found.\n");
        return 0;
    }

    int count = 0;
    char line[1024];
    while(fgets(line, 1024, stream)){
        if(count == howMany) break;
        char* tmp = strdup(line);
        char** tokens = splitString(tmp, 2, ";");
        airlines[count++] = airlineCreate(tokens[0], tokens[1]);
        free(tokens);
        free(tmp);
    }
    fclose(stream);

    printf("\nAirlines imported\n");
    for(int i = 0; i < count; i++)
        printAirline(airlines[i]);
    return count;
}

Airline airlineCreate(char* iatacode, char* name){
    Airline airline;
    strcpy(airline.iatacode,iatacode);
    strcpy(airline.name, name);
    return airline;
}

void printAirline(Airline airline){
    printf("Iatacode: %3s; Name: %-100s\n",airline.iatacode, airline.name);
}
