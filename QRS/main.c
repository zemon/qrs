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
	qrs_params.NPKF = 4000;
	qrs_params.SPKF = 500;



	int sum =0;
	int counter = 0;

	//TODO: fjern et index fra alle arrays, da n ikke bruges før det er regnet ud
	int rawArray[13] = {0};
	int lowPassArray[33] = {0};
	int highPassArray[5] = {0};
	int derivativeFilterArray[30] = {0};
	int finalFilter[3]= {0};
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
		finalFilter[counter%3] = movingWindowIntegration(sum);
		//printf("%d \n",counter);
		if(counter>1){
			peakDetection(&qrs_params, finalFilter[modulo(counter-2,3)], finalFilter[modulo(counter-1,3)],finalFilter[modulo(counter,3)]);

		}

		counter++;

	}
	fclose(file);



	return 0;
}


