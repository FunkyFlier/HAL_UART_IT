/*
 * RingBuffer.h
 *
 *  Created on: Jun 3, 2016
 *      Author: work
 */

#ifndef RINGBUFFER_H_
#define RINGBUFFER_H_

#include <stdint.h>//uint*_t
#include <stddef.h>//size_t
#include <string.h> // memcpy
#include <stdlib.h> //realloc
#include <stdbool.h>

typedef struct {
	uint32_t readIdx;
	uint32_t writeIdx;
	uint8_t* buffer;
	uint32_t size;
	uint32_t available;


} RingBuffer_t;

void RingBufferCreate(RingBuffer_t*,uint8_t*,int);

int RingBufferWrite(RingBuffer_t*,uint8_t*,int );

int RingBufferRead(RingBuffer_t*,uint8_t*,int );


#endif /* RINGBUFFER_H_ */
