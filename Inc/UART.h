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

//#define UART_STREAMING

#ifdef UART_STREAMING
#define UART_STREAM_HAND huart2
#endif

typedef struct{
	UART_HandleTypeDef *uartHandler;
	volatile RingBuffer_t *rxBuffer;
	volatile RingBuffer_t *txBuffer;
}UART_STRUCT;
void UARTSetup(UART_STRUCT* ,UART_HandleTypeDef* ,volatile RingBuffer_t* ,volatile RingBuffer_t*) ;

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
