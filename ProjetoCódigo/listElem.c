#include "listElem.h"
#include <stdio.h>

void listElemPrint(ListElem elem) {
	printf("FLIGHT NUMBER %d\nAirline: %s\nOrigin airport: %s\nDestination airport: \n"
    , elem.flightNumber, elem.airline, elem.originAirport, elem.destinationAirport);
}