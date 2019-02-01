#ifndef _GLOBAL_H
#define _GLOBAL_H


#define FEED_WATCH_DOG  GpioDataRegs.GPATOGGLE.bit.GPIO23

#define EPWM1_TIMER_TBPRD 1500     //������������ģʽ��6000--10k��3000--20k��4286--14K,120M/2/14K=4286
#define EPWM2_TIMER_TBPRD 1500     //6000--10k��3000--20k��4286--14K
#define EPWM1_TIMER_HALF_TBPRD  750            //
#define EPWM2_TIMER_HALF_TBPRD  750

#define SUCCESS 1
#define FAIL 0

#define ENABLE_TX (1)
#define DISABLE_TX (0)
typedef struct{
	Uint16 currentHallPosition;
	Uint16 lastTimeHalllPosition;
	int16 duty;
}SYSINFO;
typedef struct _DATA{
	Uint16 l : 8;
	Uint16 h : 8;
}DATA;
typedef union _VAR16{
	DATA datahl;
	Uint16 value;
}VAR16;

extern SYSINFO gSysInfo;
extern int gECapCount;
void Delay(int time);
#endif
