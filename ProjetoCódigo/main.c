#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include "airline.h"
#include "utils.h"
#include "list.h"
#include "map.h"
#include "input.h"

void printCommandsMenu();
void waitFunction();

int main()
{
	PtAirline airlines[14];

	loadar(airlines, 14);

	/*
	srand(time(NULL));

	// commands interpreter
	String command;
	int quit = 0;

	setlocale(LC_ALL, "PT");

	while (!quit)
	{

		printCommandsMenu();
		fgets(command, sizeof(command), stdin);
		// descartar 'newline'. Utilizar esta técnica sempre que for lida uma
		// string para ser utilizada, e.g., nome de ficheiro, chave, etc.. //
		command[strlen(command) - 1] = '\0';

		if (equalsStringIgnoreCase(command, "QUIT"))
		{
			quit = 1; // vai provocar a saída do interpretador //
		}
		else
		{
			printf("Command not found!\n");
			waitFunction();
		}
	}

	printf("Good Bye! ...\n");
	*/
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

void waitFunction()
{
	printf("\nPress enter to continue ...");
	getchar();
}
