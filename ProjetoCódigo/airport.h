#pragma once

typedef struct airport{
    char iatacode[4];
    char airport[100];
    char city[35];
    char state[3];
    float latitude;
    float longitude;
    int timezome;
}Airport;

typedef Airport* PtAirport;