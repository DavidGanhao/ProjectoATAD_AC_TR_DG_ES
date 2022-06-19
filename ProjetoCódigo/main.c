#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include "projectMethods.h"
#include "input.h"
#include "utils.h"

void printCommandsMenu();
void commandsMenuDecision(Airline *airlines, PtMap airports, PtList flights);
void printBaseCommands();
void baseCommandsDecision(Airline *airlines, PtMap airports, PtList flights);
void infoFlightsCommandsMenu();
void complexCommandsDecision(Airline *airlines, PtMap airports, PtList flights);
void complexCommands();
void waitFunction();

int main()
{
	
	srand(time(NULL));
	Airline *airlines = (Airline *)malloc(sizeof(Airline) * 20);
	PtMap airports = mapCreate(20);
	PtList flights = listCreate();
	
	commandsMenuDecision(airlines, airports, flights);
}

void printCommandsMenu()
{
	printf("\n===================================================================================");
	printf("\n                          PROJECT: United States Domestics Flight Data");
	printf("\n===================================================================================");
	printf("\nA. Base commands (LOADAR, LOADAP, LOADF, CLEAR).");
	printf("\nB. Aggregated info about flights (SHOWALL, SHOWF, LISTAR, LISTAP, ONTIME, AVERAGE,");
	printf("\n   SHOWAP, TOPN, TSP).");
	printf("\nC. Complex Indicators require airports and flights data (AIRPORT_S, AIRPORTS).");
	printf("\nD. Exit (QUIT)\n\n");
	printf("COMMAND> ");
}

void infoFlightsCommandsMenu()
{
	printf("\n===================================================================================");
	printf("\n                          PROJECT: United States Domestics Flight Data");
	printf("\n===================================================================================");
	printf("\nA. SHOWALL.");
	printf("\nB. SHOWF.");
	printf("\nC. LISTAR.");
	printf("\nD. LISTAP.");
	printf("\nE. ONTIME.");
	printf("\nF. AVERAGE.");
	printf("\nG. SHOWAP.");
	printf("\nH. TOPN.");
	printf("\nI. TSP.");
	printf("\nJ. GO BACK(QUIT)\n\n");
	printf("COMMAND> ");
}

void flightsMenuDecision(Airline *airlines, PtMap airports, PtList flights)
{
	String command;
	infoFlightsCommandsMenu();
	fgets(command, sizeof(command), stdin);
	command[strlen(command) - 1] = '\0';
	if (equalsStringIgnoreCase(command, "J") || equalsStringIgnoreCase(command, "QUIT"))
	{
		return;
	}
	else if (equalsStringIgnoreCase(command, "A") || equalsStringIgnoreCase(command, "SHOWALL"))
	{
		showAll(flights);
	}
	else if (equalsStringIgnoreCase(command, "B") || equalsStringIgnoreCase(command, "SHOWF"))
	{
		char airport[4];
		printf("What is the airport?\n> ");
		scanf("%s", airport);
		showWF(flights, airport);
	}
	else if (equalsStringIgnoreCase(command, "C") || equalsStringIgnoreCase(command, "LISTAR"))
	{
		listAR(flights, airlines);
	}
	else if (equalsStringIgnoreCase(command, "D") || equalsStringIgnoreCase(command, "LISTAP"))
	{
		listAP(flights, airports);
	}
	else if (equalsStringIgnoreCase(command, "E") || equalsStringIgnoreCase(command, "ONTIME"))
	{
		onTime(flights, airlines);
	}
	else if (equalsStringIgnoreCase(command, "F") || equalsStringIgnoreCase(command, "AVERAGE"))
	{
		char airportIataCode[4];
		printf("What is the airport to calculate the average?\n> ");
		scanf("%s", airportIataCode);
		average(flights, airportIataCode);
	}
	else if (equalsStringIgnoreCase(command, "G") || equalsStringIgnoreCase(command, "SHOWAP"))
	{
		showAP(flights, airlines, airports);
	}
	else if (equalsStringIgnoreCase(command, "H") || equalsStringIgnoreCase(command, "TOPN"))
	{
		int number;
		printf("How many flights to print?\n> ");
		readInteger(&number);
		topN(flights, number);
	}
	else if (equalsStringIgnoreCase(command, "I") || equalsStringIgnoreCase(command, "TSP"))
	{
		tspMenu(flights, airports);
	}
	else
	{
		printf("Command not found!\n");
		waitFunction();
	}
	flightsMenuDecision(airlines, airports, flights);
}

void commandsMenuDecision(Airline *airlines, PtMap airports, PtList flights)
{
	String command;
	printCommandsMenu();
	fgets(command, sizeof(command), stdin);
	command[strlen(command) - 1] = '\0';
	if (equalsStringIgnoreCase(command, "D") || equalsStringIgnoreCase(command, "quit"))
	{
		quit(airlines, airports, flights);
		return;
	}
	else if (equalsStringIgnoreCase(command, "A"))
	{
		baseCommandsDecision(airlines, airports, flights);
	}
	else if (equalsStringIgnoreCase(command, "B"))
	{
		flightsMenuDecision(airlines, airports, flights);
	}
	else if (equalsStringIgnoreCase(command, "C"))
	{
		complexCommandsDecision(airlines, airports, flights);
	}
	else
	{
		printf("Command not found!\n");
		waitFunction();
	}
	commandsMenuDecision(airlines, airports, flights);
}

void waitFunction()
{
	printf("\nPress enter to continue ...");
	getchar();
}

void printBaseCommands()
{
	printf("\n===================================================================================");
	printf("\n                          PROJECT: United States Domestics Flight Data");
	printf("\n===================================================================================");
	printf("\nA. LOADAR.");
	printf("\nB. LOADAP.");
	printf("\nC. LOADF.");
	printf("\nD. CLEAR.");
	printf("\nE. GO BACK(QUIT)\n\n");
	printf("COMMAND> ");
}

void baseCommandsDecision(Airline *airlines, PtMap airports, PtList flights)
{
	String command;
	printBaseCommands();
	fgets(command, sizeof(command), stdin);
	command[strlen(command) - 1] = '\0';
	if (equalsStringIgnoreCase(command, "E") || equalsStringIgnoreCase(command, "QUIT"))
	{
		return;
	}
	else if (equalsStringIgnoreCase(command, "A") || equalsStringIgnoreCase(command, "LOADAR"))
	{
		int howMany;
		printf("How many airlines?\n> ");
		readInteger(&howMany);
		loadar(airlines, howMany);
	}
	else if (equalsStringIgnoreCase(command, "B") || equalsStringIgnoreCase(command, "LOADAP"))
	{
		int howMany;
		printf("How many airports?\n> ");
		readInteger(&howMany);
		loadap(airports, howMany);
	}
	else if (equalsStringIgnoreCase(command, "C") || equalsStringIgnoreCase(command, "LOADF"))
	{
		int howMany;
		printf("How many flights?\n> ");
		readInteger(&howMany);
		loadf(airports, flights, howMany);
	}
	else if (equalsStringIgnoreCase(command, "D") || equalsStringIgnoreCase(command, "CLEAR"))
	{
		clear(airlines, airports, flights);
	}
	else
	{
		printf("Command not found!\n");
		waitFunction();
	}
	baseCommandsDecision(airlines, airports, flights);
}

void complexCommands()
{
	printf("\n===================================================================================");
	printf("\n                          PROJECT: United States Domestics Flight Data");
	printf("\n===================================================================================");
	printf("\nA. AIRPORT_S.");
	printf("\nB. AIRPORT.");
	printf("\nC. GO BACK(QUIT)\n\n");
	printf("COMMAND> ");
}

void complexCommandsDecision(Airline *airlines, PtMap airports, PtList flights)
{
	String command;
	complexCommands();
	fgets(command, sizeof(command), stdin);
	command[strlen(command) - 1] = '\0';
	if (equalsStringIgnoreCase(command, "C") || equalsStringIgnoreCase(command, "QUIT"))
	{
		return;
	}
	else if (equalsStringIgnoreCase(command, "A") || equalsStringIgnoreCase(command, "AIRPORT_S"))
	{
		airport_s(airports);
	}
	else if (equalsStringIgnoreCase(command, "B") || equalsStringIgnoreCase(command, "AIRPORT"))
	{
		airportsMethod(airports, flights);
	}
	else
	{
		printf("Command not found!\n");
		waitFunction();
	}
	complexCommandsDecision(airlines, airports, flights);
}
