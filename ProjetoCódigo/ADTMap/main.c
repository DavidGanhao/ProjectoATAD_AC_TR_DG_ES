/**
 * @file main.c
 * 
 * @brief Provides an example program that uses the
 * ADT Map. This program counts the number of occurences
 * of distinct integers within an array.
 * 
 * Please note that the MapKey and MapValue types
 * must be defined as 'int'.
 * 
 * @author Bruno Silva (brunomnsilva@gmail.com)
 * @bug No known bugs.
 */

#include <stdio.h>
#include <stdlib.h>
#include "map.h"

int main() {

	int vec[] = { 1,1,2,1,4,3,1,2,2,4,4,13,7,5,5,5,9 };

	PtMap map = mapCreate();

	printf("Processing numbers: ");
	// 'sizeof(vec) / sizeof(int)' is possible only due 
	// to static allocation in the scope of this function
	int count;
	for (int i = 0; i < sizeof(vec) / sizeof(int) ; i++) {
		int number = vec[i];
		printf("%d ", number);

		if (mapContains(map, number)) { //existing number
			mapGet(map, number, &count);
			count++;
			mapPut(map, number, count);
		}
		else {	//new number 
			mapPut(map, number, 1);
		}
	}

	/* Print in ordered tabular format */
	int size;
	mapSize(map, &size);
	MapKey *numbers = mapKeys(map);

	// Sort keys with, e.g., Bubble Sort
	for(int i=0; i<size; i++) {
		for(int j=0; j<size-i-1; j++) {
			if( numbers[j] > numbers[j+1] ) {
				int aux = numbers[j];
				numbers[j] = numbers[j+1];
				numbers[j+1] = aux;
			}
		}
	}

	// Print key/value pairs
	printf("\nNumber | Count \n");
	for (int i = 0; i < size; i++) {
		mapGet(map, numbers[i], &count);
		printf("%6d | %d \n", numbers[i], count);
	}

	free(numbers); // free the array, as per documentation

	mapDestroy(&map);	
	
	return EXIT_SUCCESS;
}