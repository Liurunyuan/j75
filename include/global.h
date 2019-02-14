#ifndef _GLOBAL_H
#define _GLOBAL_H


#define FEED_WATCH_DOG  GpioDataRegs.GPATOGGLE.bit.GPIO23

#define EPWM1_TIMER_TBPRD 1250   //1250
#define EPWM2_TIMER_TBPRD 1250	//1250
#define EPWM1_TIMER_HALF_TBPRD  625 //625
#define EPWM2_TIMER_HALF_TBPRD  625 //625

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

void Delay(int time);
#endif
