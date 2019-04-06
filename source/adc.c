/*
 * adc.c
 *
 *  Created on: 2019Äê2ÔÂ14ÈÕ
 *      Author: Administrator
 */
#include "DSP280x_Device.h"     // DSP280x Headerfile Include File
#include "DSP280x_Examples.h"   // DSP280x Examples Include File
#include "global.h"
#include "adc.h"



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
	{8,0},
	{9,0},
	{10,0}
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

	UpdateSingleAnalogInput();
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
