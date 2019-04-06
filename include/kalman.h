/*
 * kalman.h
 *
 *  Created on: 2019Äê2ÔÂ14ÈÕ
 *      Author: Administrator
 */

#ifndef KALMAN_H_
#define KALMAN_H_

#define KALMAN_Q  (1.1)
#define KALMAN_R  (157.2)

double KalmanFilter(const double ResrcData, double ProcessNiose_Q, double MeasureNoise_R);


#endif /* KALMAN_H_ */
