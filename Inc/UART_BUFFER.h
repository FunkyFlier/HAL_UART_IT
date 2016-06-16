/*
 * UART_BUFFER.h
 *
 *  Created on: Jun 15, 2016
 *      Author: work
 */

#ifndef UART_BUFFER_H_
#define UART_BUFFER_H_
#include <stdbool.h>
#include "string.h"
#include "stdint.h"
#include <stdio.h>
//macros
#define DoubleBufferFree(T) ((T)->size - (T)->writeIdx)
#define DoubleBufferAvailable(T) ((T)->writeIdx)
#define DoubleBufferCommitWrite(T,A) ((T)->writeIdx += A)

#define RingBufferFree(B) ((B)->size - RingBufferAvailable(B))
#define RingWriteIdxToEnd(B) ((B)->size - (B)->writeIdx)//todo rename these
#define RingReadIdxToEnd(B) ((B)->size - (B)->readIdx)
#define RingBufferCommitRead(B, A) ((B)->readIdx = ((B)->readIdx + (A)) % (B)->size)
#define RingBufferCommitWrite(B, A) ((B)->writeIdx = ((B)->writeIdx + (A)) % (B)->size)



typedef struct{
	uint8_t* buffer;
	uint16_t size;
	volatile uint16_t writeIdx;
	volatile uint16_t readIdx;

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

void DoubleBufferCreate(DoubleBuffer_t *, uint8_t *, uint8_t *,int );
int DoubleBufferWrite(DoubleBuffer_t *, uint8_t *, int );
void DoubleBufferSwap(DoubleBuffer_t *);
void RingBufferCreate(RingBuffer_t *, uint8_t *, int );
int RingBufferWriteByte(RingBuffer_t *, uint8_t *);
int RingBufferWrite(RingBuffer_t *, uint8_t *, int );
int RingBufferRead(RingBuffer_t *, uint8_t *, int );
int RingBufferReadByte(RingBuffer_t *, uint8_t *);
int RingBufferAvailable(RingBuffer_t *);

#endif /* UART_BUFFER_H_ */
