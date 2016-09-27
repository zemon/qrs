/*
 * qsr.h
 *
 *  Created on: 21 Sep 2016
 *      Author: feynman
 */

#ifndef QRS_H_
#define QRS_H_
// Header file for QRS functionality
// it is recommended to use the structure "QRS_parameters"
// to organize all variables and parameters

typedef struct QRS_params
{ // Structure for QRS parameters
   int SPKF;
   int NPKF;
   int THRESHOLD1;
   int THRESHOLD2;
   int RR_AVERAGE1;
   int RR_AVERAGE2;
   int RR_LOW;
   int RR_HIGH;
   int RR_MISS;
   int PEAKS[100];
   int counter;
   int lastRPeak;
   int RecentRR[9];
   int RecentRROK[9];
   int RPeaks[101];
   // Add parameters that are missing
   // or of use to you

} QRS_params;

// Feel free to change and add methods
void peakDetection(QRS_params *params, int x1, int x2, int x3, int x4, int x5, int time);

void updateThreshholds(QRS_params *params);
int calculateRR(int time, int lastPeak);

int calculateAverage(int *array);

void updateRRIntervals(QRS_params *params, int RR_Average);


#endif /* QRS_H_ */
