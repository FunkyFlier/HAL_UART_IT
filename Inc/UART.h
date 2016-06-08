/*
 * UART.h
 *
 *  Created on: Jun 6, 2016
 *      Author: work
 */

#ifndef UART_H_
#define UART_H_

#include "stm32f4xx_hal.h"
#include "RingBuffer.h"
#include "stdio.h"
#include "defines.h"

//remove
#include <stdbool.h>
//todo wrapper function for ring buffer so everything is handled via UART.h
//todo function call to zero ring buffers
/*
 * Definitions to configure UART
 */
#define UART_RING_BUF_SIZE_RX 128
#define UART_RING_BUF_SIZE_TX 128

//#define UART_1
//#define UART_2
//#define UART_3
//#define UART_4
//#define UART_5
//#define UART_6
//#define UART_7
//#define UART_8
typedef struct{
	UART_HandleTypeDef *uartHandler;
	volatile RingBuffer_t *rxBuffer;
	volatile RingBuffer_t *txBuffer;
}UART_STRUCT;

#ifdef UART_1
UART_STRUCT UART_1_STRUCT;
uint8_t UART_1_RX_BUFFER[UART_RING_BUF_SIZE_RX];
uint8_t UART_1_TX_BUFFER[UART_RING_BUF_SIZE_TX];
uint8_t ISRBuffer_1[1];
RingBuffer_t UART_1_RX_RING;
RingBuffer_t UART_1_TX_RING;
extern UART_HandleTypeDef huart1;

#endif
#ifdef UART_2
UART_STRUCT UART_2_STRUCT;
uint8_t UART_2_RX_BUFFER[UART_RING_BUF_SIZE_RX];
uint8_t UART_2_TX_BUFFER[UART_RING_BUF_SIZE_TX];
uint8_t ISRBuffer_2[1];
RingBuffer_t UART_2_RX_RING;
RingBuffer_t UART_2_TX_RING;
extern UART_HandleTypeDef huart2;
#endif
#ifdef UART_3
UART_STRUCT UART_3_STRUCT;
uint8_t UART_3_RX_BUFFER[UART_RING_BUF_SIZE_RX];
uint8_t UART_3_TX_BUFFER[UART_RING_BUF_SIZE_TX];
uint8_t ISRBuffer_3[1];
RingBuffer_t UART_3_RX_RING;
RingBuffer_t UART_3_TX_RING;
extern UART_HandleTypeDef huart3;
#endif
#ifdef UART_4
UART_STRUCT UART_4_STRUCT;
uint8_t UART_4_RX_BUFFER[UART_RING_BUF_SIZE_RX];
uint8_t UART_4_TX_BUFFER[UART_RING_BUF_SIZE_TX];
uint8_t ISRBuffer_4[1];
RingBuffer_t UART_4_RX_RING;
RingBuffer_t UART_4_TX_RING;
extern UART_HandleTypeDef huart4;
#endif
#ifdef UART_5
UART_STRUCT UART_5_STRUCT;
uint8_t UART_5_RX_BUFFER[UART_RING_BUF_SIZE_RX];
uint8_t UART_5_TX_BUFFER[UART_RING_BUF_SIZE_TX];
uint8_t ISRBuffer_5[1];
RingBuffer_t UART_5_RX_RING;
RingBuffer_t UART_5_TX_RING;
extern UART_HandleTypeDef huart5;
#endif
#ifdef UART_6
UART_STRUCT UART_6_STRUCT;
uint8_t UART_6_RX_BUFFER[UART_RING_BUF_SIZE_RX];
uint8_t UART_6_TX_BUFFER[UART_RING_BUF_SIZE_TX];
uint8_t ISRBuffer_6[1];
RingBuffer_t UART_6_RX_RING;
RingBuffer_t UART_6_TX_RING;
extern UART_HandleTypeDef huart6;
#endif
#ifdef UART_7
UART_STRUCT UART_7_STRUCT;
uint8_t UART_7_RX_BUFFER[UART_RING_BUF_SIZE_RX];
uint8_t UART_7_TX_BUFFER[UART_RING_BUF_SIZE_TX];
uint8_t ISRBuffer_7[1];
RingBuffer_t UART_7_RX_RING;
RingBuffer_t UART_7_TX_RING;
extern UART_HandleTypeDef huart7;
#endif
#ifdef UART_8
UART_STRUCT UART_8_STRUCT;
uint8_t UART_8_RX_BUFFER[UART_RING_BUF_SIZE_RX];
uint8_t UART_8_TX_BUFFER[UART_RING_BUF_SIZE_TX];
uint8_t ISRBuffer_8[1];
RingBuffer_t UART_8_RX_RING;
RingBuffer_t UART_8_TX_RING;
extern UART_HandleTypeDef huart8;
#endif

//#define UART_STREAMING

#ifdef UART_STREAMING
#define UART_STREAM_HAND huart2
#endif

void UARTInit();

int UARTWriteByte(UART_STRUCT*,uint8_t*);
int UARTWriteBuffer(UART_STRUCT*,uint8_t*,int);
int UARTGetByte(UART_STRUCT*,uint8_t*);
int UARTGetBuffer(UART_STRUCT*,uint8_t*,int);
/*
#ifdef UART_STREAMING
FILE* UART_STREAM_CONFIG();
int UART_PUTC(void*, char*,int);
int UART_GETC(void*,const char* ,int n);
#endif
*/


#endif /* UART_H_ */
