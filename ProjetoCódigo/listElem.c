#include <stdio.h>
#include "listElem.h"

void listElemPrint(ListElem elem) {
	printf("Flight Number: %d\n", elem.flightNumber);
	printf("Airline: %s", elem.airline);
}