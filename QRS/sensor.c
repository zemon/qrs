#include "sensor.h"
#include <stdio.h>
#include <stdlib.h>

int getNextData(FILE *file)

{
	int value;
	fscanf(file,"%i",&value);
   return value;
}

FILE* openfile(const char* filename)
{
   FILE *file = fopen(filename,"r");;

   return file;
}
