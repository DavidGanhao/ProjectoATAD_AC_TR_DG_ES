/**
 * @file mapElem.c
 * @brief Implements operations for types MapKey and MapValue.
 * 
 * @author Bruno Silva (brunomnsilva@gmail.com)
 * @bug No known bugs.
 */

#include "mapElem.h"
#include <string.h>
#include <stdio.h>


void mapKeyPrint(MapKey key) {
	printf("Key -> ");
	stringCodePrint(key);
}

void mapValuePrint(MapValue value) {
	printf("Airport: %s\n", value.airport);
}

bool mapKeyEquals(MapKey key1, MapKey key2) {	
	return (strcmp(key1.code,key2.code)==0); 
}