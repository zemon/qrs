/*
 * sensor.h
 *
 *  Created on: 12 Sep 2016
 *      Author: feynman
 */

#ifndef SENSOR_H
#define SENSOR_H
#include <stdio.h>
#include <stdlib.h>


FILE* openfile(const char* filename);

int getNextData(FILE *file);

#endif
