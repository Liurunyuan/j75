/*
 * adc.c
 *
 *  Created on: 2019��2��14��
 *      Author: Administrator
 */
#include "DSP280x_Device.h"     // DSP280x Headerfile Include File
#include "DSP280x_Examples.h"   // DSP280x Examples Include File
#include "global.h"
#include "adc.h"
#include "kalman.h"


int64 tmp[64] = {0};
SysAnalogVar gSysAnalogVar = {0};
/********update anolog variable value******************************/
Uint16 updateU_AN_3V3_A0(void){return GET_U_AN_3V3_A0;}
Uint16 updateAGND_A1(void){return GET_AGND_A1;}
Uint16 updateI_AN_3V3_A2(void){return GET_I_AN_3V3_A2;}
Uint16 updateAGND_A3(void){return GET_AGND_A3;}
Uint16 updateNO_USE_A4(void){return GET_NO_USE_A4;}
Uint16 updateNO_USE_A5(void){return GET_NO_USE_A5;}
Uint16 updateNO_USE_A6(void){return GET_NO_USE_A6;}
Uint16 updateAGND_A7(void){return GET_AGND_A7;}
Uint16 updateT_AN_3V3_B0(void){return GET_T_AN_3V3_B0;}
Uint16 updateNO_USE_B1(void){return GET_NO_USE_B1;}
Uint16 updateNO_USE_B2(void){return GET_NO_USE_B2;}
Uint16 updateNO_USE_B3(void){return GET_NO_USE_B3;}
Uint16 updateHP_I_AN_3V3_B4(void){return GET_HP_I_AN_3V3_B4;}
Uint16 updateAGND_B5(void){return GET_AGND_B5;}
Uint16 updateHPT_AN_3V3_B6(void){return GET_HPT_AN_3V3_B6;}
Uint16 updateAGND_B7(void){return GET_AGND_B7;}


const UV funcptr[] = {

	updateU_AN_3V3_A0,
	updateAGND_A1,
	updateI_AN_3V3_A2,
	updateAGND_A3,
	updateNO_USE_A4,
	updateNO_USE_A5,
	updateNO_USE_A6,
	updateAGND_A7,
	updateT_AN_3V3_B0,
	updateNO_USE_B1,
	updateNO_USE_B2,
	updateNO_USE_B3,
	updateHP_I_AN_3V3_B4,
	updateAGND_B5,
	updateHPT_AN_3V3_B6,
	updateAGND_B7
};
const int anologMaxMinInit[][2] = {
	{0,0},
	{1,0},
	{2,0},
	{3,0},
	{4,0},
	{5,0},
	{6,0},
	{7,0},
	{4096,691},		//temperature max and min
	{9,0},
	{10,0},
	{11,0},
	{12,0},
	{13,0},
	{14,0},
	{15,0},
};
void InitAdcVar(void){
	int index;
	for (index = 0; index < AnalogTotalChannel; ++index) {
		gSysAnalogVar.single.var[index].updateValue = funcptr[index];
		gSysAnalogVar.single.var[index].max = anologMaxMinInit[index][0];
		gSysAnalogVar.single.var[index].min = anologMaxMinInit[index][1];
	}
}

void UpdateSingleAnalogInput(void){
	int index;

	for(index = 0; index < AnalogTotalChannel; ++index){
		gSysAnalogVar.single.var[index].value = gSysAnalogVar.single.var[index].updateValue();
	}

}

void ReadAnalogValue(void){

    if((AdcRegs.ADCASEQSR.bit.SEQ_CNTR==0)&&
              (AdcRegs.ADCST.bit.SEQ1_BSY==0)){

    }
    else{
    	//TODO generate an alarm
    	return;
    }
}

int IsAnalogValueAbnormal(void){
	int index;
	int ret = 1;
	for(index = 0; index < AnalogTotalChannel; ++index){
		if((gSysAnalogVar.single.var[index].value > gSysAnalogVar.single.var[index].max) ||
				(gSysAnalogVar.single.var[index].value < gSysAnalogVar.single.var[index].min)) {
			ret = 0;
		}
	}
	return ret;
}

void updateAndCheckTemperature(void){
	static int count = 0;
	gSysAnalogVar.single.var[T_AN_3V3_B0].value = gSysAnalogVar.single.var[T_AN_3V3_B0].updateValue();
	if((gSysAnalogVar.single.var[T_AN_3V3_B0].value > gSysAnalogVar.single.var[T_AN_3V3_B0].max) ||
				(gSysAnalogVar.single.var[T_AN_3V3_B0].value < gSysAnalogVar.single.var[T_AN_3V3_B0].min)) {
		++count;
		if(count > 5){
			count = 0;
			gSysAlarm.bit.overTemperature = 1;
		}
	}
	else{
		count = 0;
	}
}

void updateAndCheckCurrent(void){
	static int count = 0;
	static int i = 0;

	int j;
	int64 ret;
	gSysAnalogVar.single.var[I_AN_3V3_A2].value = gSysAnalogVar.single.var[I_AN_3V3_A2].updateValue();
	if((gSysAnalogVar.single.var[I_AN_3V3_A2].value > gSysAnalogVar.single.var[I_AN_3V3_A2].max) ||
				(gSysAnalogVar.single.var[I_AN_3V3_A2].value < gSysAnalogVar.single.var[I_AN_3V3_A2].min)) {
		++count;
		if(count > 5){
			count = 0;
			// gSysAlarm.bit.overCurrent = 1;
		}
	}
	else{
		count = 0;
	}

	// if(gSysAnalogVar.single.var[I_AN_3V3_A2].value > gSysInfo.maxCurrent){
	// 	gSysInfo.maxCurrent = gSysAnalogVar.single.var[I_AN_3V3_A2].value;
	// }
	//	gSysInfo.maxCurrent = gSysAnalogVar.single.var[I_AN_3V3_A2].value;
	//	gSysInfo.maxCurrent = (KalmanFilterCurrent(gSysAnalogVar.single.var[I_AN_3V3_A2].value,300,50));
	tmp[i] = (int64)gSysAnalogVar.single.var[I_AN_3V3_A2].value;
	++i;
	if(i >= 64){
	    i = 0;
	    for(j = 0; j < 64; ++j){
	        ret += tmp[j];
	    }
	    ret = ret >> 6;
	    gSysInfo.maxCurrent  = ret;
	}
//	gSysInfo.maxCurrent = (int16)(KalmanFilterCurrent(ret,300,50));
}
