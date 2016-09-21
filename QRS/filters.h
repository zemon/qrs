/*
 * filters.h
 *
 *  Created on: 14 Sep 2016
 *      Author: feynman
 */

#ifndef FILTERS_H_
#define FILTERS_H_
#include <stdio.h>
#include <stdlib.h>

int lowPassFilter(int y1, int y2, int x, int x6, int x12);

int modulo(int a, int b);

int highPassFilter(int y1, int x, int x16, int x17, int x32);

int derivativeFilter(int x, int x1, int x3, int x4);

int squareFilter(int x);

int movingWindowIntegration(int sum);

int sumN(int sum, int next, int prev);

#endif /* FILTERS_H_ */
