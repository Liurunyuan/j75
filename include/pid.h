/*
 * pid.h
 *
 *  Created on: 2019Äê2ÔÂ14ÈÕ
 *      Author: Administrator
 */

#ifndef PID_H_
#define PID_H_

typedef struct _PIDPARA{
	int32 kp;
	int32 ki;
	int32 kd;
	int32 targetPid;
}PIDPARA;
extern double gTargetSpeed;
void InitPidVar(void);
int16 PidOutput(double currentSpeed);

#endif /* PID_H_ */
