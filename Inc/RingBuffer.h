/*
 * RingBuffer.h
 *
 *  Created on: Jun 3, 2016
 *      Author: work
 */

#ifndef RINGBUFFER_H_
#define RINGBUFFER_H_
#include <stdint.h>
#include <stddef.h>
#include <string.h> // memcpy
#include <stdlib.h> //realloc
typedef struct RingBuffer_s {
	uint32_t readIdx;
	uint32_t writeIdx;
	uint8_t* buffer;
	uint32_t size;
	uint32_t available;


} RingBuffer_t;

void RingBuffer_create(RingBuffer_t*,uint8_t*,int);

int RingBuffer_write(RingBuffer_t*,char*,int );

int RingBuffer_read(RingBuffer_t*,char*,int );
/*
#define RingBuffer_used(B) (((B)->end + 1) % (B)->length - (B)->start - 1)

#define RingBuffer_free(B) ((B)->length - (B)->end - 1)

#define RingBuffer_full(B) (RingBuffer_available_data((B)) - (B)->length == 0)

#define RingBuffer_empty(B) (RingBuffer_available_data((B)) == 0)
*/

#endif /* RINGBUFFER_H_ */
