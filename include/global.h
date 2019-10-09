#ifndef _GLOBAL_H
#define _GLOBAL_H

#define OPENLOOPDONE 1
#define CLOSELOOPDONE 1

#define MAXSTARTDISTANCE 40
#define MINSTARTDISTANCE -40


#define FEED_WATCH_DOG  GpioDataRegs.GPATOGGLE.bit.GPIO23

#define EPWM1_TIMER_TBPRD 3000   		//1124:40k	 2250:20k   3000:15k
#define EPWM2_TIMER_TBPRD 3000			//1124:40k	 2250:20k	3000:15k
#define EPWM1_TIMER_HALF_TBPRD  1500 	//625 :40k	 1125:20k	1500:15k
#define EPWM2_TIMER_HALF_TBPRD  1500 	//625 :40k	 1125:20k	1500:15k

#define SUCCESS 1
#define FAIL 0

#define ENABLE_TX (1)
#define DISABLE_TX (0)

#define INCLUDE_FEATURE  1
#define EXCLUDE_FEATURE  0


#define SCI_PROTOCAL_401_SUPPORT INCLUDE_FEATURE

enum{
	UNKNOWN,
	START,
	STOP,
	ALARM,
	INIT
};

typedef struct
{
	Uint16 a : 1;
	Uint16 overTemperature : 1;
	Uint16 overBusVoltage : 1;
	Uint16 lowBusVoltage : 1;
	Uint16 overCurrent : 1;
	Uint16 overCurrent2 : 1;
	Uint16 InitFault : 1;
	Uint16 f : 1;
	Uint16 softwareFault : 1;
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

typedef struct
{
	Uint16 txBufferFull : 1;
	Uint16 updateAndCheckTemperature : 1;
	Uint16 updateAndCheckVoltage : 1;
	Uint16 d : 1;
	Uint16 e : 1;
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
}SW_ALARMBIT;

typedef union
{
	Uint16 all;
	ALARMBIT bit;
}SYSALARM;

typedef union
{
	Uint16 all;
	SW_ALARMBIT bit;
}SYS_SW_ALARM;


typedef struct{
	Uint16 currentHallPosition;
	Uint16 lastTimeHalllPosition;
	int16 duty;
	int16 restrictduty;
	int16 dutyUp;
	int16 dutyDown;
	int16 isEcapRefresh;
	int16 closeLooptargetDuty;
	int16 currentDuty;
	Uint16 currentOffset;
	//int32 currentDuty_32bit;
	int16 openLoopTargetDuty;
	int16 ddtmax;
	int16 hallErrorCount;
	int16 maxCurrent;
	int16 aveCurrent;
	int16 repeatPeriod;
	int16 thresholdKiError;
	int16 enableFindTable;
	int16 uiSetOpenLoopDuty;
	int16 dtDuty;
	int16 formularRa;
	int32 curp;
	int16 dutyAddInterval;
	int64 sek;
	int16 speedUI;
	int16 aKi;
	int16 aKp;
	//int16 startDistance;
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

extern volatile SYSINFO gSysInfo;
extern volatile SYSALARM gSysAlarm;
extern volatile SYS_SW_ALARM gSysSWAlarm;
extern volatile SYSSTATE gSysState;

void Delay(int time);
void InitGlobalVar(void);
void clearHardwareErro(void);
void enablePwmOutput(void);
void disablePwmOutput(void);
void enableEcapInterrupt(void);
void disableEcapInterrupt(void);
void clearScibOverflow(void);
void readTZGpioState(void);
void enableSoftwareDog(void);
int findOpenLoopDuty(int busvol, int tarSpeed);
int findOpenLoopDutyByFormula(int busvol, int tarSpeed, int current);
#endif
