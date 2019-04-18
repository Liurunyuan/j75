#ifndef _ECAP_H
#define _ECAP_H


void ECap1_Isr(void);
void ECap2_Isr(void);
void ECap3_Isr(void);
int32 CalculateSpeed(Uint32 capCount);
void InitEcapVar(void);


extern Uint64  gECapCount;
extern int16 gMotorSpeedEcap;
#endif
