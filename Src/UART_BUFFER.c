/*
 * UART_BUFFER.c
 *
 *  Created on: Jun 15, 2016
 *      Author: work
 */


#include "UART_BUFFER.h"
#include <stdbool.h>
//macros
#define RingBufferAvailable(B) (((B)->writeIdx + 1) % (B)->size - (B)->readIdx - 1)
#define RingBufferFree(B) ((B)->size - RingBufferAvailable(B))
#define RingSpaceToEnd(B) ((B)->size - (B)->writeIdx)
#define RingReadsToEnd(B) ((B)->size - (B)->readIdx)
#define RingBufferCommitRead(B, A) ((B)->readIdx = ((B)->readIdx + (A)) % (B)->size)
#define RingBufferCommitWrite(B, A) ((B)->writeIdx = ((B)->writeIdx + (A)) % (B)->size)

#define TrasmitBufferFree(T) ((T)->size - (T)->writeIdx)
#define TransmitBufferAvailable(T) ((T)->writeIdx)
//#define TrasnmitCommitRead(T,A)
#define TrasnmitCommitWrite(T,A) ((T)->writeIdx += A)
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
	volatile bool reading;
	uint16_t size;
	volatile uint16_t writeIdx;
}TransmitBuffer_t;

void TransmitBufferCreate(TransmitBuffer_t *tb, uint8_t *buffer0, uint8_t *buffer1,int sizeOfBuffer){
	tb->buffer0 = buffer0;
	tb->buffer1 = buffer1;
	tb->buffer = buffer0;
	tb->size = sizeOfBuffer;
	tb->writeIdx = 0;
	tb->useBuffer0 = true;
	tb->writing = false;
	tb->reading = false;
}

//called from UART when TX is busy
int TrasnmitBufferWrite(TransmitBuffer_t *tb, uint8_t *in, int count){
	if (TrasmitBufferFree(tb) == 0){
		return -1;
	}
	if (TrasmitBufferFree(tb) < count){
		count = TrasmitBufferFree(tb);
	}
	tb->writing = true;
	memcpy(&tb->buffer[tb->writeIdx], in, count);
	TrasnmitCommitWrite(tb,count);
	tb->writing = false;
	return 0;
}
//call after HAL_UART_Transmit_IT using the ring buffer
void TrasnmitBufferSwap(TransmitBuffer_t *tb){
	tb->useBuffer0 ^= true;
	if (tb->useBuffer0 == true){
		tb->buffer = tb->buffer0;
	}else{
		tb->buffer = tb->buffer1;
	}
	tb->writeIdx = 0;
}

void RingBufferCreate(RingBuffer_t *rb, uint8_t *buffer, int sizeOfBuffer) {
	rb->buffer = buffer;
	rb->size = sizeOfBuffer;
	rb->readIdx = 0;
	rb->writeIdx = 0;
}

//the write functions should be used in the RX ISR call back
int RingBufferWriteByte(RingBuffer_t *rb, uint8_t *in) {
	if (RingBufferAvailable(rb) >= rb->size){
		return -1;
	}
	if(RingBufferAvailable(rb) == 0){
		rb->writeIdx = rb->readIdx = 0;
	}
	rb->buffer[rb->writeIdx] = *in;
	RingBufferCommitWrite(rb, 1);
	return 0;
}
int RingBufferWrite(RingBuffer_t *rb, uint8_t *in, int count) {
	if (RingBufferAvailable(rb) >= rb->size){
		return -1;
	}
	if(RingBufferAvailable(rb) == 0){
		rb->writeIdx = rb->readIdx = 0;
	}
	if (RingBufferFree(rb) < count){
		count = RingBufferFree(rb);
	}
	if (RingSpaceToEnd(rb) <= count){
		memcpy(&rb->buffer[rb->writeIdx], in, count);
	}else{
		memcpy(&rb->buffer[rb->writeIdx], in, RingSpaceToEnd(rb));
		memcpy(rb->buffer, in + RingSpaceToEnd(rb), count - RingSpaceToEnd(rb));
	}
	RingBufferCommitWrite(rb, count);
	return count;
}
int RingBufferRead(RingBuffer_t *rb, uint8_t *out, int count){
	if (RingBufferAvailable(rb) <= 0){
		return -1;
	}
	if (RingBufferAvailable(rb) < count){
		count = RingBufferAvailable(rb);
	}
	if (rb->writeIdx > rb->readIdx){
		memcpy(out, rb->buffer + rb->readIdx, count);
		RingBufferCommitRead(rb,count);
		return count;
	}
	if (RingReadsToEnd(rb) <= count){
		memcpy(out, rb->buffer + rb->readIdx, count);
		RingBufferCommitRead(rb,count);
		return count;
	}else{
		memcpy(out, rb->buffer + rb->readIdx, RingReadsToEnd(rb));
		memcpy(out, rb->buffer , count - RingReadsToEnd(rb));
	}
	RingBufferCommitRead(rb,count);
	return count;
}



















