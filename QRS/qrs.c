#include <stdio.h>
#include <stdlib.h>
#include "qrs.h"

void peakDetection(QRS_params *params, int x1, int x2, int x3)
{
	if(x1<x2 && x2>x3){
		params->PEAKS[params->counter%10] = x2;
		printf("%d \n", x2);
		params->counter++;
	}

}

void updateThreshholds(QRS_params *params, int peak){
	params->NPKF = params->NPKF*0.875+0.125*peak;
	params->THRESHOLD1 = params->NPKF+0.25*(params->SPKF-params->NPKF);
	params->THRESHOLD2 = (params->THRESHOLD1)/2;

}
void updateRRIntervals(QRS_params *params, int RR_Average){
	params->RR_LOW = 0.92*RR_Average;
	params->RR_MISS = 1.16*RR_Average;
	params->RR_HIGH = 1.66*RR_Average;
}
