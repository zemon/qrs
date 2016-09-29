/*
 * qsr.h
 *
 *  Created on: 21 Sep 2016
 *      Author: feynman
 */

#ifndef QRS_H_
#define QRS_H_


typedef struct QRS_params
{
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
   int LastRPeakValue;
   int missCount;


} QRS_params;

void peakDetection(QRS_params *params, int x1, int x2, int x3, int x4, int x5, int time);

void updateThreshholds(QRS_params *params);
int calculateRR(int time, int lastPeak);
int pulse(int rr);

int calculateAverage(int *array);

void updateRRIntervals(QRS_params *params, int RR_Average);

void display(int peakValue, int peakTime, int pulse);

void warning(int peak);


#endif /* QRS_H_ */
