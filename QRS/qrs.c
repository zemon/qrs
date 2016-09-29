#include <stdio.h>
#include <stdlib.h>
#include "qrs.h"

void peakDetection(QRS_params *params, int x1, int x2, int x3, int x4, int x5, int time)
{
	int currentRR;
	if(x1<	x2 && x2<=x3 && x3>=x4 && x4>x5){

		params->PEAKS[params->counter%50] = x3;
		params->PEAKS[params->counter%50+50] = time;

		if(params->counter == 0){
			updateThreshholds(params);


		}
		params->counter++;
		currentRR = calculateRR(time, params->lastRPeak);

		//Calcalte RR peak
		if(x3 > params->THRESHOLD1){





			//high low check
			if(currentRR > params->RR_LOW && currentRR < params->RR_HIGH){
				params->missCount = 0;
				params->LastRPeakValue = x3;
				params->RecentRR[params->RecentRR[8]%8] = currentRR;
				params->RecentRR[8]++;

				params->RecentRROK[params->RecentRROK[8]%8] = currentRR;
				params->RecentRROK[8]++;

				params->lastRPeak = time;

				params->SPKF = 0.125*x3+0.875*params->SPKF;

				//calculate RR_average1
				params->RR_AVERAGE1 =calculateAverage(params->RecentRR);

				//calculate RR_average2
				params->RR_AVERAGE2 =calculateAverage(params->RecentRROK);

				updateThreshholds(params);
				updateRRIntervals(params,params->RR_AVERAGE2);
				display(params->lastRPeak,params->lastRPeak, pulse(currentRR) );
				warning(x3);


			}
			else{

				params->missCount++;
				if(params->missCount >=5){
					printf("Your heartrythem is unstable\n");
					params->missCount = 0;
				}


				if(currentRR>params->RR_MISS){

					int i = params->counter-2;
					int peak2 = params->PEAKS[i%50];
					while(peak2<=params->THRESHOLD2){
						i--;
						peak2 =params->PEAKS[i%50];
					}

					//store the RR interval in recentRR
					currentRR =calculateRR(params->PEAKS[i%50+50], params->lastRPeak);

					//store the new Rpeak
					params->LastRPeakValue= peak2;
					params ->lastRPeak =params->PEAKS[i%50+50];

					params->RecentRR[params->RecentRR[8]%8] =currentRR;
					params->RecentRR[8]++;

					params->lastRPeak = params->PEAKS[i%50+50];

					params->SPKF = 0.25*peak2+0.75*params->SPKF;

					params->RR_AVERAGE1 = calculateAverage(params->RecentRR);

					updateRRIntervals(params,params->RR_AVERAGE1);

					updateThreshholds(params);

					display(params-> lastRPeak,params-> lastRPeak, pulse(currentRR) );
					warning(peak2);




				}


			}

		}else{
			params->NPKF = params->NPKF*0.875+0.125*x3;
			updateThreshholds(params);
		}


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
int calculateRR(int time, int lastPeak){
	int rr = time-lastPeak;
	return rr;
}
int pulse(int RR){
	return (60*1000)/(RR*4);
}

void display(int peakValue, int peakTime, int pulse){
	printf("Peak værdi: %d peak tid: %d puls: %d \n", peakValue, peakTime, pulse);
}

void updateThreshholds(QRS_params *params){

	params->THRESHOLD1 = params->NPKF+0.25*(params->SPKF-params->NPKF);
	params->THRESHOLD2 = (params->THRESHOLD1)/2;
}
void updateRRIntervals(QRS_params *params, int RR_Average){
	params->RR_LOW = 0.92*RR_Average;
	params->RR_MISS = 1.66*RR_Average;
	params->RR_HIGH = 1.16*RR_Average;
}

void warning(int peak){
	if(peak<2000){
		printf("Your heatbeat is weak \n");
	}
}
