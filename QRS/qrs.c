#include <stdio.h>
#include <stdlib.h>
#include "qrs.h"

void peakDetection(QRS_params *params, int x1, int x2, int x3, int time)
{
	int currentRR;
	if(x1<x2 && x2>x3){
		params->PEAKS[params->counter%10] = x2;
		if(params->counter == 0){
			updateThreshholds(params, x2);
		}

		//Calcalte RR peak
		if(x2 > params->THRESHOLD1){
			currentRR = time-params->lastRPeak;
			params->lastRPeak = time;

			//high low check
			if(currentRR > params->RR_LOW && currentRR < params->RR_HIGH){
				params->RPeaks[params->counter%100] = x2;
				params->RecentRR[params->counter%8] = currentRR;
				//TODO - tjek op på counter her
				params->RecentRROK[params->counter] = currentRR;

				//update SPKF
				params->SPKF = x2/8+(x2*7)/8;


			}

		}else{
			updateThreshholds(params, x2);
		}
	params->counter++;
	}

}

void updateThreshholds(QRS_params *params, int peak){
	params->NPKF = params->NPKF*0.875+0.125*peak;
	params->THRESHOLD1 = params->NPKF+0.25*(params->SPKF-params->NPKF);
	params->THRESHOLD2 = (params->THRESHOLD1)/2;
	//printf("%d %d %d", params->NPKF, params->THRESHOLD1, params->THRESHOLD2);

}
void updateRRIntervals(QRS_params *params, int RR_Average){
	params->RR_LOW = 0.92*RR_Average;
	params->RR_MISS = 1.16*RR_Average;
	params->RR_HIGH = 1.66*RR_Average;
}
