#include <stdio.h>
#include <stdlib.h>
#include "qrs.h"

void peakDetection(QRS_params *params, int x1, int x2, int x3, int x4, int x5, int time)
{
	int currentRR;
	if(x1<	x2 && x2<=x3 && x3>=x4 && x4>x5){

		params->PEAKS[params->counter%50] = x3;
		params->PEAKS[params->counter%50+50] = time;

		//printf("%d\n", x3);

		//printf("%d\n, time");

		//printf("%d  %d\n",time, x2);
		if(params->counter == 0){
			updateThreshholds(params);


		}
		params->counter++;
		//printf("%d\n", params ->THRESHOLD2);
		currentRR = calculateRR(time, params->lastRPeak);
					printf("Pulse %d \n", pulse(currentRR));
		//Calcalte RR peak
		if(x3 > params->THRESHOLD1){





			//high low check
			if(currentRR > params->RR_LOW && currentRR < params->RR_HIGH){
				params->missCount = 0;
				params->RPeaks[params->RPeaks[100]%50] = x3;
				params ->RPeaks[params->RPeaks[100]%50+50] = time;
				params->RPeaks[100]++;
				params->RecentRR[params->RecentRR[8]%8] = currentRR;
				params->RecentRR[8]++;

				//TODO - tjek op på counter her
				params->RecentRROK[params->RecentRROK[8]%8] = currentRR;
				params->RecentRROK[8]++;

				params->lastRPeak = time;

				//update SPKF
				//printf("%d \n", x2, time, params ->SPKF);
				//params->SPKF = x2*0.125+x2*+0.875*params->SPKF;

				params->SPKF = 0.125*x3+0.875*params->SPKF;

				//calculate RR_average1
				params->RR_AVERAGE1 =calculateAverage(params->RecentRR);

				//calculate RR_average2
				params->RR_AVERAGE2 =calculateAverage(params->RecentRROK);

				//printf("average 1: %d average 2 : %d \n",params->RR_AVERAGE1,params->RR_AVERAGE2);

				updateThreshholds(params);
				updateRRIntervals(params,params->RR_AVERAGE2);
				warning(x3);


			}
			else{

				params->missCount++;
				if(params->missCount >=5){
					printf("Your heartrythem is unstable");
					params->missCount = 0;
				}

						//printf("%d \n",currentRR);
				if(currentRR>params->RR_MISS){
					//printf("%d \n",currentRR);
					int i = params->counter-2;
					int peak2 = params->PEAKS[i%50];
					while(peak2<=params->THRESHOLD2){
						i--;
						peak2 =params->PEAKS[i%50];
					}

					//store the new Rpeak
					params->RPeaks[params->RPeaks[100]%50]= peak2;
					params ->RPeaks[params->RPeaks[100]%50+50] = params->PEAKS[i%50+50];
					params->RPeaks[100]++;

					//til at vise searchbacks
					//printf("%d\n", params->RPeaks[params->RPeaks[100]+1]);

					//store the RR interval in recentRR
					params->RecentRR[params->RecentRR[8]%8] = calculateRR(params->PEAKS[i%50+50], params->RPeaks[(params->RPeaks[100]-2)%50+50]);
					params->RecentRR[8]++;

					//printf("test : %d \n",calculateRR(params->PEAKS[i%50+50], params->RPeaks[(params->RPeaks[100]-1)%50+50]));
					params->lastRPeak = params->PEAKS[i%50+50];
					//printf("%d, \n", params->lastRPeak);

					params->SPKF = 0.25*peak2+0.75*params->SPKF;

					params->RR_AVERAGE1 = calculateAverage(params->RecentRR);

					updateRRIntervals(params,params->RR_AVERAGE1);

					updateThreshholds(params);

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
	//printf("Tid: %d RR: %d\n", time,rr);
	return rr;
}
int pulse(int RR){
	//returnerer antallet af millisekunder på et minut / antal millisekunder mellem hjerteslag = puls
	// vores data bliver målt med 250hz, det vil sige vi skal gange vores interal skal ganges med 4 for at få antal millisekunder
	return (60*1000)/(RR*4);
}

void updateThreshholds(QRS_params *params){

	params->THRESHOLD1 = params->NPKF+0.25*(params->SPKF-params->NPKF);
	params->THRESHOLD2 = (params->THRESHOLD1)/2;
	//printf("%d %d %d", params->NPKF, params->THRESHOLD1, params->THRESHOLD2);

}
void updateRRIntervals(QRS_params *params, int RR_Average){
	params->RR_LOW = 0.92*RR_Average;
	params->RR_MISS = 1.66*RR_Average;
	params->RR_HIGH = 1.16*RR_Average;
}

void warning(int peak){
	if(peak<2000){
		printf("Your heatbeat is weak");
	}
}
