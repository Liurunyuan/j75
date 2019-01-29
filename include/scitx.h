#ifndef _SCITX_H
#define _SCITX_H


#define TXMAXQSIZE (900)
#define TOTAL_TX_VAR (8)

typedef void (*updatevalue)(int a, int b,int c);

typedef struct _RS422TXQUE{
	char txBuf[TXMAXQSIZE];
	int front;
	int rear;
}RS422TXQUE;

typedef struct _GRX422TX{
	Uint16 value;
	unsigned char index;
	unsigned char isTx;
	updatevalue updateValue;
}GRX422TX;
void SciTxIsrThread(void);


extern Uint16 gRx422TxEnableFlag[TOTAL_TX_VAR];
#endif
