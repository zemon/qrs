#include "filters.h"
#include <stdio.h>
#include <stdlib.h>

// Feel free to change return statement and arguments
int lowPassFilter(int y1, int y2, int x, int x6, int x12)
{
	//printf("%d %d %d %d %d\n",y1,y2,x,x6,x12);
	return 2*y1-y2+(x-2*x6+x12)/32;

}

int highPassFilter(int y1, int x, int x16, int x17, int x32){

	return y1-x/32+x16-x17+(x32)/32;
}
int derivativeFilter(int x,int x1, int x3, int x4){
	return squareFilter((2*x+x1-x3-2*x4)/8);
}
int squareFilter(int x){
	return x*x;
}
//TODO: en sum hvor vi trækker det sidste tal fra og lægger det nye til, i stedet for at køre arrayet igennem
int movingWindowIntegration(int sum){

	return sum/30;
}
int sumN(int sum , int next, int prev){
	return sum = sum-prev+next;
}
int modulo(int a, int b){

	int r = a % b;
	    return r < 0 ? r + b : r;
}

