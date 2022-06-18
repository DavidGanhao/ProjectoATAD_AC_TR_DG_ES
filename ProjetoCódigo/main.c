#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "input.h"
#include <locale.h>
#include <time.h>
#include "projectMethods.h"
#include "input.h"
#include "stringCode.h"

void printCommandsMenu();
void commandsMenuDecision(Airline *airlines, PtMap airports, PtList flights);
void printBaseCommands();
void baseCommandsDecision(Airline *airlines, PtMap airports, PtList flights);
void waitFunction();

int main()
{
	srand(time(NULL));
	Airline *airlines = (Airline*) malloc(sizeof(Airline)*20);
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

void commandsMenuDecision(Airline *airlines, PtMap airports, PtList flights)
{
	String command;
	printCommandsMenu();
	fgets(command, sizeof(command), stdin);
	command[strlen(command) - 1] = '\0';
	if (equalsStringIgnoreCase(command, "D"))
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
	}
	else if (equalsStringIgnoreCase(command, "C"))
	{
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
	printf("\nD. CLEAR.\n");
	printf("\nE. GO BACK\n\n");
	printf("COMMAND> ");
}

void baseCommandsDecision(Airline *airlines, PtMap airports, PtList flights)
{
	String command;
	printBaseCommands();
	fgets(command, sizeof(command), stdin);
	command[strlen(command) - 1] = '\0';
	if (equalsStringIgnoreCase(command, "E"))
	{
		return;
	}
	else if (equalsStringIgnoreCase(command, "A"))
	{
		int howMany;
		printf("How many airlines?\n");
		readInteger(&howMany);
		loadar(airlines, howMany);
	}
	else if (equalsStringIgnoreCase(command, "B"))
	{
		int howMany;
		printf("How many airports?\n");
		readInteger(&howMany);
		loadap(airports, howMany);
	}
	else if (equalsStringIgnoreCase(command, "C"))
	{
		int howMany;
		printf("How many flights?\n");
		readInteger(&howMany);
		loadf(airports, flights, howMany);
	}
	else if (equalsStringIgnoreCase(command, "D"))
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