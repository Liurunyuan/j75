#include "DSP280x_Device.h"     // DSP280x Headerfile Include File
#include "DSP280x_Examples.h"   // DSP280x Examples Include File
#include "global.h"


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
	gSysInfo.currentDuty = 0;
	gSysInfo.openLoopTargetDuty = 0;
	gSysInfo.ddtmax = 1;
	gSysInfo.hallErrorCount = 0;
	gSysInfo.maxCurrent = 0;


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
		105,
		130,
		150,
		170,
		190,
		210,
		225,
		245,
		265,
		280,
		300,
		315,
		332,
		351,
		370,
		389,
		407,
		426,
		445,
		467,
		490,
		508,
		530,
		553,
		575,
		600,
		621,
		650,
		675,
		700,
		730,
		765,
		796,
		837,
		875,
		914,
		954,
		996,
		1035,
		1080,
		1125,
		1170,
		1227,
		1295,
		1360,
		1430,
		1500,
		1500,
		1500,
		1500
	},

	{
		84,
		102,
		119,
		134,
		148,
		162,
		176,
		190,
		203,
		216,
		230,
		242,
		255,
		268,
		282,
		295,
		308,
		322,
		336,
		351,
		366,
		381,
		398,
		414,
		430,
		447,
		462,
		480,
		498,
		517,
		536,
		555,
		575,
		595,
		620,
		642,
		664,
		689,
		718,
		748,
		784,
		820,
		853,
		892,
		930,
		970,
		1004,
		1008,
		1045,
		1087
	},

	{
		70,
		86,
		99,
		112,
		124,
		136,
		147,
		158,
		169,
		181,
		192,
		202,
		214,
		225,
		235,
		246,
		257,
		269,
		281,
		292,
		303,
		315,
		327,
		340,
		352,
		363,
		376,
		389,
		402,
		415,
		429,
		440,
		453,
		469,
		486,
		500,
		517,
		536,
		553,
		570,
		588,
		610,
		630,
		653,
		674,
		698,
		716,
		722,
		748,
		775
	},

	{
		59,
		73,
		85,
		95,
		106,
		116,
		126,
		135,
		145,
		154,
		163,
		173,
		182,
		191,
		201,
		210,
		219,
		229,
		238,
		247,
		257,
		267,
		276,
		286,
		295,
		305,
		314,
		324,
		334,
		344,
		354,
		365,
		376,
		388,
		399,
		410,
		421,
		434,
		445,
		458,
		472,
		487,
		503,
		518,
		533,
		548,
		559,
		564,
		579,
		599
	}
};

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

