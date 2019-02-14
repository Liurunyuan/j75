#include "DSP280x_Device.h"     // DSP280x Headerfile Include File
#include "DSP280x_Examples.h"   // DSP280x Examples Include File
#include <string.h>
#include "global.h"
#include "timer0.h"
#include "scitx.h"
#define N (1000)



void EnableScibTxInterrupt(void){
	ScibRegs.SCIFFTX.bit.TXFFINTCLR = 1;
	ScibRegs.SCIFFTX.bit.TXFFIENA = 1;
}

void Timer0_ISR_Thread(void){

	static unsigned char count = 0;

	++count;

	if(count > N){
		PackRS422TxData();
		count = 0;
	}
}

void Timer1_ISR_Thread(void){

	if(gRS422TxQue.front != gRS422TxQue.rear
			&& ScibRegs.SCIFFTX.bit.TXFFST == 0){

		 EnableScibTxInterrupt();
	}
}
