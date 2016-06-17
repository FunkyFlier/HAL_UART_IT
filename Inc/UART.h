/*
 * UART.h
 *
 *  Created on: Jun 6, 2016
 *      Author: work
 */

#ifndef UART_H_
#define UART_H_

#include "stm32f4xx_hal.h"
#include <string.h>
#include <stdbool.h>
#include "stdint.h"
#include <stdio.h>
/*
//#define UART_1
//#define UART_2
//#define UART_3
//#define UART_4
//#define UART_5
//#define UART_6
//#define UART_7
//#define UART_8

 */
#define UART_1
#define UART_2
#define UART_6


#define LOOP_BACK_DEMO

#define UART_RING_BUF_SIZE_RX 128
#define UART_RING_BUF_SIZE_TX 128

typedef struct{
	uint8_t* buffer;
	uint16_t size;
	volatile int writeIdx,writeIdxTemp;
	volatile int readIdx,readIdxTemp;
	volatile int availableWrite,availableRead;
}RingBuffer_t;

typedef struct{
	uint8_t* buffer0;//must have two buffers otherwise there is the potential the data can be changed between transmits;
	uint8_t* buffer1;
	uint8_t* buffer;
	volatile bool useBuffer0;
	volatile bool writing;
	uint16_t size;
	volatile uint16_t writeIdx;
}DoubleBuffer_t;
typedef struct {
	UART_HandleTypeDef *uartHandler;
	RingBuffer_t *rxBuffer;
	DoubleBuffer_t *txBuffer;
	uint8_t* ISRBuf;
	bool RXOverRun;
	bool TXOverRun;
} UART_STRUCT;



void UARTInit();

int UARTWriteBuffer(UART_STRUCT*, uint8_t*, int);
int UARTGetBuffer(UART_STRUCT*, uint8_t*, int);
int UARTAvailabe(UART_STRUCT*);
void UARTLoopDemo();

void RingBufferCreate(RingBuffer_t *, uint8_t *, int );
int RingBufferWrite(RingBuffer_t *, uint8_t *, int );
int RingBufferRead(RingBuffer_t *, uint8_t *, int );
int RingBufferAvailable(RingBuffer_t *);

#define DoubleBufferFree(T) ((T)->size - (T)->writeIdx)
#define DoubleBufferAvailable(T) ((T)->writeIdx)
#define DoubleBufferCommitWrite(T,A) ((T)->writeIdx += A)

#define RingBufferFree(B) ((B)->size - RingBufferAvailable(B))
#define RingWriteIdxToEnd(B) ((B)->size - (B)->writeIdx)
#define RingReadIdxToEnd(B) ((B)->size - (B)->readIdx)
#define RingBufferCommitRead(B, A) ((B)->readIdx = ((B)->readIdx + (A)) % (B)->size)
#define RingBufferCommitWrite(B, A) ((B)->writeIdx = ((B)->writeIdx + (A)) % (B)->size)

#ifdef LOOP_BACK_DEMO
uint8_t loopBackBuffer[UART_RING_BUF_SIZE_RX];
int numBytes;
#endif

#ifdef UART_1
UART_STRUCT UART_1_STRUCT;
uint8_t UART_1_RX_BUFFER[UART_RING_BUF_SIZE_RX];
uint8_t UART_1_TX_BUFFER1[UART_RING_BUF_SIZE_TX];
uint8_t UART_1_TX_BUFFER2[UART_RING_BUF_SIZE_TX];
uint8_t ISRBuffer_1[1];
RingBuffer_t UART_1_RX_RING;
DoubleBuffer_t UART_1_TX_DB;
extern UART_HandleTypeDef huart1;
#ifdef LOOP_BACK_DEMO
uint8_t loopBackUART1Buffer[UART_RING_BUF_SIZE_RX];
RingBuffer_t loopBackUART1;
#endif
#endif
#ifdef UART_2
UART_STRUCT UART_2_STRUCT;
uint8_t UART_2_RX_BUFFER[UART_RING_BUF_SIZE_RX];
uint8_t UART_2_TX_BUFFER1[UART_RING_BUF_SIZE_TX];
uint8_t UART_2_TX_BUFFER2[UART_RING_BUF_SIZE_TX];
uint8_t ISRBuffer_2[1];
RingBuffer_t UART_2_RX_RING;
DoubleBuffer_t UART_2_TX_DB;
extern UART_HandleTypeDef huart2;
#ifdef LOOP_BACK_DEMO
uint8_t loopBackUART2Buffer[UART_RING_BUF_SIZE_RX];
RingBuffer_t loopBackUART2;
#endif
#endif
#ifdef UART_3
UART_STRUCT UART_3_STRUCT;
uint8_t UART_3_RX_BUFFER[UART_RING_BUF_SIZE_RX];
uint8_t UART_3_TX_BUFFER1[UART_RING_BUF_SIZE_TX];
uint8_t UART_3_TX_BUFFER2[UART_RING_BUF_SIZE_TX];
uint8_t ISRBuffer_3[1];
RingBuffer_t UART_3_RX_RING;
DoubleBuffer_t UART_3_TX_DB;
extern UART_HandleTypeDef huart3;
#ifdef LOOP_BACK_DEMO
uint8_t loopBackUART3Buffer[UART_RING_BUF_SIZE_RX];
RingBuffer_t loopBackUART3;
#endif
#endif
#ifdef UART_4
UART_STRUCT UART_4_STRUCT;
uint8_t UART_4_RX_BUFFER[UART_RING_BUF_SIZE_RX];
uint8_t UART_4_TX_BUFFER1[UART_RING_BUF_SIZE_TX];
uint8_t UART_4_TX_BUFFER2[UART_RING_BUF_SIZE_TX];
uint8_t ISRBuffer_4[1];
RingBuffer_t UART_4_RX_RING;
DoubleBuffer_t UART_4_TX_DB;
extern UART_HandleTypeDef huart4;
#ifdef LOOP_BACK_DEMO
uint8_t loopBackUART4Buffer[UART_RING_BUF_SIZE_RX];
RingBuffer_t loopBackUART4;
#endif
#endif
#ifdef UART_5
UART_STRUCT UART_5_STRUCT;
uint8_t UART_5_RX_BUFFER[UART_RING_BUF_SIZE_RX];
uint8_t UART_5_TX_BUFFER1[UART_RING_BUF_SIZE_TX];
uint8_t UART_5_TX_BUFFER2[UART_RING_BUF_SIZE_TX];
uint8_t ISRBuffer_5[1];
RingBuffer_t UART_5_RX_RING;
DoubleBuffer_t UART_5_TX_DB;
extern UART_HandleTypeDef huart5;
#ifdef LOOP_BACK_DEMO
uint8_t loopBackUART5Buffer[UART_RING_BUF_SIZE_RX];
RingBuffer_t loopBackUART5;
#endif
#endif
#ifdef UART_6
UART_STRUCT UART_6_STRUCT;
uint8_t UART_6_RX_BUFFER[UART_RING_BUF_SIZE_RX];
uint8_t UART_6_TX_BUFFER1[UART_RING_BUF_SIZE_TX];
uint8_t UART_6_TX_BUFFER2[UART_RING_BUF_SIZE_TX];
uint8_t ISRBuffer_6[1];
RingBuffer_t UART_6_RX_RING;
DoubleBuffer_t UART_6_TX_DB;
extern UART_HandleTypeDef huart6;
#ifdef LOOP_BACK_DEMO
uint8_t loopBackUART6Buffer[UART_RING_BUF_SIZE_RX];
RingBuffer_t loopBackUART6;
#endif
#endif
#ifdef UART_7
UART_STRUCT UART_7_STRUCT;
uint8_t UART_7_RX_BUFFER[UART_RING_BUF_SIZE_RX];
uint8_t UART_7_TX_BUFFER1[UART_RING_BUF_SIZE_TX];
uint8_t UART_7_TX_BUFFER2[UART_RING_BUF_SIZE_TX];
uint8_t ISRBuffer_7[1];
RingBuffer_t UART_7_RX_RING;
DoubleBuffer_t UART_7_TX_DB;
extern UART_HandleTypeDef huart7;
#ifdef LOOP_BACK_DEMO
uint8_t loopBackUART7Buffer[UART_RING_BUF_SIZE_RX];
RingBuffer_t loopBackUART7;
#endif
#endif
#ifdef UART_8
UART_STRUCT UART_8_STRUCT;
uint8_t UART_8_RX_BUFFER[UART_RING_BUF_SIZE_RX];
uint8_t UART_8_TX_BUFFER1[UART_RING_BUF_SIZE_TX];
uint8_t UART_8_TX_BUFFER2[UART_RING_BUF_SIZE_TX];
uint8_t ISRBuffer_8[1];
RingBuffer_t UART_8_RX_RING;
DoubleBuffer_t UART_8_TX_DB;
extern UART_HandleTypeDef huart8;
#ifdef LOOP_BACK_DEMO
uint8_t loopBackUART8Buffer[UART_RING_BUF_SIZE_RX];
RingBuffer_t loopBackUART8;
#endif
#endif



#endif /* UART_H_ */
