#ifndef _GLOBAL_H
#define _GLOBAL_H


#define FEED_WATCH_DOG  GpioDataRegs.GPATOGGLE.bit.GPIO23

#define EPWM1_TIMER_TBPRD 2250   		//1124:40k			2250:20k
#define EPWM2_TIMER_TBPRD 2250			//1124:40k			2250:20k
#define EPWM1_TIMER_HALF_TBPRD  1125 	//625:40k			1125:20k
#define EPWM2_TIMER_HALF_TBPRD  1125 	//625:40k			1125:20k

#define SUCCESS 1
#define FAIL 0

#define ENABLE_TX (1)
#define DISABLE_TX (0)

enum{
	UNKNOWN,
	START,
	STOP,
	ALARM,
	INIT
};

typedef struct
{
	Uint16 overCurrent : 1;
	Uint16 overBusVoltage : 1;
	Uint16 overTemperature : 1;
	Uint16 softwareFault : 1;
	Uint16 InitFault : 1;
	Uint16 f : 1;
	Uint16 g : 1;
	Uint16 h : 1;
	Uint16 i : 1;
	Uint16 j : 1;
	Uint16 k : 1;
	Uint16 l : 1;
	Uint16 m : 1;
	Uint16 n : 1;
	Uint16 o : 1;
	Uint16 p : 1;
}ALARMBIT;

typedef union
{
	Uint16 all;
	ALARMBIT bit;
}SYSALARM;



typedef struct{
	Uint16 currentHallPosition;
	Uint16 lastTimeHalllPosition;
	int16 duty;
	int16 dutyUp;
	int16 dutyDown;
	int16 isEcapRefresh;
	int16 targetDuty;
	int16 currentDuty;
}SYSINFO;

typedef struct _DATA{
	Uint16 l : 8;
	Uint16 h : 8;
}DATA;

typedef union _VAR16{
	DATA datahl;
	Uint16 value;
}VAR16;

typedef struct _SYSSTATE{
	int currentstate;
	int targetState;
}SYSSTATE;

extern SYSINFO gSysInfo;
extern SYSALARM gSysAlarm;

void Delay(int time);
void InitGlobalVar(void);
void clearHardwareErro(void);
void enablePwmOutput(void);
void enableEcapInterrupt(void);
void disableEcapInterrupt(void);
void clearScibOverflow(void);
extern SYSSTATE gSysState;
#endif
