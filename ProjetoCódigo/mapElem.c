/**
 * @file mapElem.c
 * @brief Implements operations for types MapKey and MapValue.
 * 
 * @author Bruno Silva (brunomnsilva@gmail.com)
 * @bug No known bugs.
 */

#include "mapElem.h"
#include <stdio.h>

void mapKeyPrint(MapKey key) {
	printf("%s", key);
}

void mapValuePrint(MapValue value) {
	printf("Airport %s - Code %s\nLocalization: %s, %s, %.2f : %.2f\n"
	, value.airport, value.iatacode, value.state, value.city, value.latitude, value.longitude);
}

int mapKeyCompare(MapKey key1, MapKey key2) {
	// in case of integer keys:
	return (key1 - key2); 
}