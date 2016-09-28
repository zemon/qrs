#include <stdio.h>
#include "sensor.h"
#include "filters.h"
#include "qrs.h"


int main(int argc, char *argv[])
{
	static const char filename[] = "ECG.txt";
	FILE *file = openfile(filename);
	struct QRS_params qrs_params;
	qrs_params.counter=0;
	qrs_params.NPKF = 4500;
	qrs_params.SPKF = 1500;
	qrs_params.lastRPeak = 0;
	qrs_params.RR_HIGH = 30000;
	qrs_params.RR_LOW = 0;
	qrs_params.RR_MISS = 35000;
	qrs_params.RecentRR[8] = 0;
	qrs_params.RecentRROK[8] = 0;
	qrs_params.RPeaks[100] = 0;
	qrs_params.THRESHOLD1 = 5000;
	qrs_params.THRESHOLD2 = 5000;




	int sum =0;
	int counter = 0;

	//TODO: fjern et index fra alle arrays, da n ikke bruges før det er regnet ud
	int rawArray[13] = {0};
	int lowPassArray[33] = {0};
	int highPassArray[5] = {0};
	int derivativeFilterArray[30] = {0};
	int finalFilter[5]= {0};

	//printf("%d", lowPassArray[modulo(counter-3,33)]);
	while(!feof (file)){

		//Read the next datapoint
		rawArray[counter%13] = getNextData(file);

		//Lowpass filter
		// TODO: Metoder til insert og get fra vores circular arrays
		lowPassArray[modulo(counter,33)]=lowPassFilter(lowPassArray[modulo(counter-1,33)],lowPassArray[modulo(counter-2,33)],
				rawArray[modulo(counter,13)],rawArray[modulo(counter-6,13)],rawArray[modulo(counter-12,13)]);


		//Highpass filter
		highPassArray[modulo(counter,5)]= highPassFilter(highPassArray[modulo(counter-1,5)],lowPassArray[counter%33],
				lowPassArray[modulo(counter-16,33)],lowPassArray[modulo(counter-17,33)],lowPassArray[modulo(counter-32,33)]);

		derivativeFilterArray[counter%30] = derivativeFilter(highPassArray[counter%5],highPassArray[modulo(counter-1,5)],
				highPassArray[modulo(counter-3,5)],highPassArray[modulo(counter-4,5)]);

		sum = sumN(sum, derivativeFilterArray[counter%30],derivativeFilterArray[(counter+1)%30]);
		finalFilter[counter%5] = movingWindowIntegration(sum);


		//printf("%d \n",finalFilter[modulo(counter-1,5)]);

		//Til visualissere threshodls
		//printf("%d\n", qrs_params.THRESHOLD1);

		if(counter>3){
			peakDetection(&qrs_params, finalFilter[modulo(counter-4,5)], finalFilter[modulo(counter-3,5)],
					finalFilter[modulo(counter-2,5)], finalFilter[modulo(counter-1,5)],
					finalFilter[modulo(counter,5)], counter);

		}

		counter++;

	}

	/*for(int i = 0; i<qrs_params.RPeaks[100];i++){
		printf("%d\n",qrs_params.RPeaks[i+50]);
	}


	*/

//, qrs_params.RPeaks[i]
	//printf("%d \n", qrs_params.counter);
	fclose(file);



	return 0;
}


