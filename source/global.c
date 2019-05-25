#include "DSP280x_Device.h"     // DSP280x Headerfile Include File
#include "DSP280x_Examples.h"   // DSP280x Examples Include File
#include "global.h"

#define KE (1)
#define RA (0)


volatile SYSINFO gSysInfo = {0};
volatile SYSSTATE gSysState = {0};
volatile SYSALARM gSysAlarm = {0};

void InitGlobalVar(void){
	gSysState.currentstate = INIT;
	gSysState.targetState = INIT;
	gSysInfo.duty = 0;
	gSysInfo.dutyUp = 0;
	gSysInfo.dutyDown = 0;
	gSysInfo.currentHallPosition = 0;
	gSysInfo.lastTimeHalllPosition = 0;
	gSysInfo.isEcapRefresh = 0;
	gSysInfo.closeLooptargetDuty = 0;
	gSysInfo.currentDuty = 50;
	gSysInfo.openLoopTargetDuty = 0;
	gSysInfo.ddtmax = 1;
	gSysInfo.hallErrorCount = 0;
	gSysInfo.maxCurrent = 0;
	gSysInfo.repeatPeriod = 50;
	gSysInfo.thresholdKiError = 1000;
	gSysInfo.enableFindTable = 0;
	gSysInfo.uiSetOpenLoopDuty = 50;
	gSysInfo.dtDuty = 0;
	gSysInfo.formularRa = 0;


	gSysAlarm.all = 0;
}
void Delay(int time){
	int i;
	for(i = 0; i < time; ++i){
		asm(" NOP");
	}
}


void clearHardwareErro(void){
	GpioDataRegs.GPADAT.bit.GPIO29 = 1;
	asm(" NOP");
	asm(" NOP");
	asm(" NOP");
	asm(" NOP");
	asm(" NOP");
	GpioDataRegs.GPADAT.bit.GPIO29 = 0;
	asm(" NOP");
	asm(" NOP");
	asm(" NOP");
	asm(" NOP");
	asm(" NOP");
	GpioDataRegs.GPADAT.bit.GPIO29 = 1;
	asm(" NOP");
	asm(" NOP");
	asm(" NOP");
	asm(" NOP");
	asm(" NOP");
}


void enablePwmOutput(void){
	GpioDataRegs.GPADAT.bit.GPIO31 = 0;
	asm(" NOP");
	asm(" NOP");
	asm(" NOP");
	asm(" NOP");
	asm(" NOP");
}

void disablePwmOutput(void){
	GpioDataRegs.GPADAT.bit.GPIO31 = 1;
	asm(" NOP");
	asm(" NOP");
	asm(" NOP");
	asm(" NOP");
	asm(" NOP");
}

void enableEcapInterrupt(void){
	PieCtrlRegs.PIEIER4.bit.INTx1 = 1;//ECAP1
	PieCtrlRegs.PIEIER4.bit.INTx2 = 1;//ECAP2
	PieCtrlRegs.PIEIER4.bit.INTx3 = 1;//ECAP3
	ECap1Regs.ECCTL2.bit.TSCTRSTOP = 1; 
	ECap2Regs.ECCTL2.bit.TSCTRSTOP = 1; 
	ECap3Regs.ECCTL2.bit.TSCTRSTOP = 1; 
}

void disableEcapInterrupt(void){
	PieCtrlRegs.PIEIER4.bit.INTx1 = 0;//ECAP1
	PieCtrlRegs.PIEIER4.bit.INTx2 = 0;//ECAP2
	PieCtrlRegs.PIEIER4.bit.INTx3 = 0;//ECAP3
	ECap1Regs.ECCTL2.bit.TSCTRSTOP = 0; 
	ECap2Regs.ECCTL2.bit.TSCTRSTOP = 0; 
	ECap3Regs.ECCTL2.bit.TSCTRSTOP = 0; 
}

void clearScibOverflow(void){
	if(ScibRegs.SCIFFRX.bit.RXFFOVF == 1){
		ScibRegs.SCIFFRX.bit.RXFFOVRCLR = 1;
		ScibRegs.SCIFFRX.bit.RXFFOVF = 1;
		gSysAlarm.bit.InitFault = 1;
	}
}

void readTZGpioState(void){
	//this function will remove when TZ is configured
	int gpio14state = -1;

	gpio14state = GpioDataRegs.GPADAT.bit.GPIO14;

	if(gpio14state == 0){
		gSysAlarm.bit.f = 1;
	}
}

inline int BilinearInterpolation(int q11, int q12, int q21, int q22, int x1, int x2, int y1, int y2, int x, int y) 
{
/*
  |      |q12		 |r2		 |q22
y3|------*-----------*-----------*--------
  |		 |			 |			 |
y3|		 |			 |p			 |
  |------*-----------*-----------*--------
  |		 |			 |			 |
  |		 |q11		 |r1		 |q21
y1|------*-----------*-----------*--------
  |		 |			 |			 |
  |		 |			 |			 |
  ---------------------------------------->
		 x1			 x			 x2
*/
    float x2x1, y2y1, x2x, y2y, yy1, xx1;
    x2x1 = x2 - x1;
    y2y1 = y2 - y1;
    x2x = x2 - x;
    y2y = y2 - y;
    yy1 = y - y1;
    xx1 = x - x1;
    return 1 / (x2x1 * y2y1) * (
        q11 * x2x * y2y +
        q21 * xx1 * y2y +
        q12 * x2x * yy1 +
        q22 * xx1 * yy1
    );
}

/*
	0------------>20V
	1------------>24V
	2------------>28V
	3------------>32V
	---------------------------------------
	0------------>500
	1------------>700
	2------------>900
	3------------>1100
	......
	n------------>500 + n*200
*/
int mapBusVolandSpeed[4][50] = {
	{
		99,
		123,
		142,
		161,
		180,
		199,
		213,
		232,
		251,
		266,
		285,
		299,
		315,
		333,
		351,
		369,
		386,
		404,
		422,
		443,
		465,
		482,
		503,
		525,
		546,
		570,
		589,
		617,
		641,
		665,
		693,
		726,
		756,
		795,
		831,
		868,
		906,
		946,
		983,
		1026,
		1068,
		1111,
		1165,
		1230,
		1292,
		1358,
		1425,
		1425,
		1425,
		1425
	},

	{
		79,
		96,
		113,
		127,
		140,
		153,
		167,
		180,
		192,
		205,
		218,
		229,
		242,
		254,
		267,
		280,
		292,
		305,
		319,
		333,
		347,
		361,
		378,
		393,
		408,
		424,
		438,
		456,
		473,
		491,
		509,
		527,
		546,
		565,
		589,
		609,
		630,
		654,
		682,
		710,
		744,
		779,
		810,
		847,
		883,
		921,
		953,
		957,
		992,
		1032
	},

	{
		66,
		81,
		94,
		106,
		117,
		129,
		139,
		150,
		160,
		171,
		182,
		191,
		203,
		213,
		223,
		233,
		244,
		255,
		266,
		277,
		287,
		299,
		310,
		323,
		334,
		344,
		357,
		369,
		381,
		394,
		407,
		418,
		430,
		445,
		461,
		475,
		491,
		509,
		525,
		541,
		558,
		579,
		598,
		620,
		640,
		663,
		680,
		685,
		710,
		736
	},

	{
		56,
		69,
		80,
		90,
		100,
		110,
		119,
		128,
		137,
		146,
		154,
		164,
		172,
		181,
		190,
		199,
		208,
		217,
		226,
		234,
		244,
		253,
		262,
		271,
		280,
		289,
		298,
		307,
		317,
		326,
		336,
		346,
		357,
		368,
		379,
		389,
		399,
		412,
		422,
		435,
		448,
		462,
		477,
		492,
		506,
		520,
		531,
		535,
		550,
		569
	}
};

double formulaKandBMap[3][2] = {
	{
		-5.91, 8498
	},
	{
		-3.29,5923
	},
	{
		-2.3, 4788
	}
};

int findOpenLoopDutyByFormula(int busvol, int tarSpeed, int current){
	int ret;
	int i = 0;
	double k, b;

	if(current < 59){
		current = 0;
	}
	else
	{
		current = current - 59;
	}

	if(busvol >= 822 & busvol < 983){
		i = 0;
	}
	else if(busvol >= 983 & busvol < 1144){
		i = 1;
	}
	else if(busvol >= 1144 & busvol < 1305){
		i = 2;
	}
	else if(busvol < 822){
		i = 0;
		busvol = 822;
	}
	else if(busvol >= 1305){
		i = 2;
		busvol = 1305;
	}
	else{
	}

	k = formulaKandBMap[i][0];
	b = formulaKandBMap[i][1];

	ret = ((tarSpeed * KE) + ((current * gSysInfo.formularRa) >> 12)) * (k * busvol + b);
	ret = ret >> 15;

	return ret;
}

/*----->20----->24----->28----->32---->*/
int findOpenLoopDuty(int busvol, int tarSpeed){
/*
  |      |q12		 |r2		 |q22
y3|------*-----------*-----------*--------
  |		 |			 |			 |
y3|		 |			 |p			 |
  |------*-----------*-----------*--------
  |		 |			 |			 |
  |		 |q11		 |r1		 |q21
y1|------*-----------*-----------*--------
  |		 |			 |			 |
  |		 |			 |			 |
  ---------------------------------------->
		 x1			 x			 x2
*/
	int ret,i,j;
	int q11, q12, q21, q22, x1, x2, y1, y2;

	if(tarSpeed < 500){
		tarSpeed = 500;
	}
	else if(tarSpeed > 10000){
		tarSpeed = 10000;
	}
	/*
	20V------------->822
	24V------------->983
	28V------------->1144
	32V------------->1305
	y = 40.25k + b
	*/
	if(busvol >= 822 & busvol < 983){
		i = 0;
		x1 = 822;
		x2 = 983;
	}
	else if(busvol >= 983 & busvol < 1144){
		i = 1;
		x1 = 983;
		x2 = 1144;
	}
	else if(busvol >= 1144 & busvol < 1305){
		i = 2;
		x1 = 1144;
		x2 = 1305;
	}
	else if(busvol < 822){
		i = 0;
		x1 = 822;
		x2 = 983;
		busvol = 850;
	}
	else if(busvol >= 1305){
		i = 2;
		x1 = 1144;
		x2 = 1305;
		busvol = 1300;
	}
	else{
	}

	j = (tarSpeed - 500) / 200;
	q11 = mapBusVolandSpeed[i][j];
	q21 = mapBusVolandSpeed[i+1][j];

	q12 = mapBusVolandSpeed[i][j + 1];
	q22 = mapBusVolandSpeed[i+1][j + 1];

	y1 = j * 200 + 500;
	y2 = j * 200 + 700;


	ret = BilinearInterpolation(q11, q12, q21, q22, x1, x2, y1, y2, busvol, tarSpeed);


	return ret;
}

