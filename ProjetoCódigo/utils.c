#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>

#include "utils.h"
#include "input.h"


int equalsStringIgnoreCase(char str1[], char str2[]) {
	/* Apenas faz uma comparacao utilizando o strcmp.
	* Necessita de tansformar primeiro as strings em maiusculas */
	char str1Up[256], str2Up[256];
	strToUpper(str1,str1Up);
	strToUpper(str2,str2Up);
	return (strcmp(str1Up, str2Up) == 0);
}

void strToUpper(const char *orig, char *dest) {
  int len = strlen(orig);
  for(int i=0; i<len; i++) {
    dest[i] = toupper(orig[i]);
  } 
  dest[len] = '\0';
}

void replace(char *str, char what, char by) {
   int len = strlen(str);
   for(int i=0; i<len; i++) {
      if(str[i] == what) {
         str[i] = by;
      }
   }
}
