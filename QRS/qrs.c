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
				params->RPeaks[params->RPeaks[99]%99] = x2;
				params->RPeaks[99]++;
				params->RecentRR[params->RecentRR[8]%8] = currentRR;
				params->RecentRR[8]++;

				//TODO - tjek op på counter her
				params->RecentRROK[params->RecentRROK[8]%8] = currentRR;
				params->RecentRROK[8]++;


				//update SPKF
				params->SPKF = x2/8+(x2*7)/8;

				//calculate RR_average1
				params->RR_AVERAGE1 =calculateAverage(params->RecentRR);

				//calculate RR_average2
				params->RR_AVERAGE2 =calculateAverage(params->RecentRROK);

				printf("average 1: %d average 2 : %d \n",params->RR_AVERAGE1,params->RR_AVERAGE2);

				updateThreshholds(params,x2);
				updateRRIntervals(params,params->RR_AVERAGE2);

			}
			else{
				if(currentRR>params->RR_MISS){

				}

			}

		}else{
			updateThreshholds(params, x2);
		}
	params->counter++;

	}

}

int calculateAverage(int *array){
	int sum = 0;
	if(array[8]<8){

		for(int i = 0; i< array[8];i++){
			sum+= array[i];
		}
		return  sum/(array[8]);
	}
	else{
		for (int i = 0; i<8;i++){
			sum+= array[i];


		}
		return sum/8;
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
