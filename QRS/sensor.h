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

// Header file for the sensor functionality
// You are free to change and add functions
// as much as you like

FILE* openfile(const char* filename);

int getNextData(FILE *file);

#endif // SENSOR_H
