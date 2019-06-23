/*
 * pid.h
 *
 *  Created on: 2019��2��14��
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


extern volatile int gTargetSpeed;
extern volatile PIDPARA gPidPara;



void InitPidVar(void);
int16 PidOutput(double currentSpeed);
int16 openLoopControl(int16 busVol, int16 targetSpeed);

#endif /* PID_H_ */
