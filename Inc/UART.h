/*
 * UART.h
 *
 *  Created on: Jun 6, 2016
 *      Author: work
 */

#ifndef UART_H_
#define UART_H_

#include "stm32f4xx_hal.h"
#include "defines.h"
#include <string.h>
#include <stdbool.h>
#include "stdint.h"
#include <UART_BUFFER.h>
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

#ifdef UART_1
UART_STRUCT UART_1_STRUCT;
uint8_t UART_1_RX_BUFFER[UART_RING_BUF_SIZE_RX];
uint8_t UART_1_TX_BUFFER1[UART_RING_BUF_SIZE_TX];
uint8_t UART_1_TX_BUFFER2[UART_RING_BUF_SIZE_TX];
uint8_t ISRBuffer_1[1];
RingBuffer_t UART_1_RX_RING;
DoubleBuffer_t UART_1_TX_DB;
extern UART_HandleTypeDef huart1;
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
#endif



#endif /* UART_H_ */
