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
   int PEAKS[10];
   int counter;
   // Add parameters that are missing
   // or of use to you

} QRS_params;

// Feel free to change and add methods
void peakDetection(QRS_params *params, int x1, int x2, int x3);

void updateThreshholds(QRS_params *params, int peak);


#endif /* QRS_H_ */
