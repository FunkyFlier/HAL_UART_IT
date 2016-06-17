/*
 * UART_BUFFER.c
 *
 *  Created on: Jun 15, 2016
 *      Author: work
 */

#include "UART_BUFFER.h"

void DoubleBufferCreate(DoubleBuffer_t *tb, uint8_t *buffer0, uint8_t *buffer1,int sizeOfBuffer){
	tb->buffer0 = buffer0;
	tb->buffer1 = buffer1;
	tb->buffer = tb->buffer0;
	tb->size = sizeOfBuffer;
	tb->writeIdx = 0;
	tb->useBuffer0 = true;
	tb->writing = false;
}

//called from UARTwrite when TX is in progress
int DoubleBufferWrite(DoubleBuffer_t *tb, uint8_t *in, int count){
	if (DoubleBufferFree(tb) == 0){
		return -1;
	}
	if (DoubleBufferFree(tb) < count){
		count = DoubleBufferFree(tb);
	}
	tb->writing = true;
	memcpy(&tb->buffer[tb->writeIdx], in, count);
	DoubleBufferCommitWrite(tb,count);
	tb->writing = false;
	return count;
}

//called after one of the buffers is sent with HAL_UART_Transmit_IT
void DoubleBufferSwap(DoubleBuffer_t *tb){
	tb->useBuffer0 ^= true;
	if (tb->useBuffer0 == true){
		tb->buffer = tb->buffer0;
	}else{
		tb->buffer = tb->buffer1;
	}
	tb->writeIdx = 0;
}

int RingBufferAvailable(RingBuffer_t *rb) {
	int readIndex = rb->readIdx;
	int writeIndex = rb->writeIdx;
	int available =  writeIndex - readIndex;
	if (available < 0){
		available += rb->size;
	 }
	return available;
}

void RingBufferCreate(RingBuffer_t *rb, uint8_t *buffer, int sizeOfBuffer) {
	rb->buffer = buffer;
	rb->size = sizeOfBuffer;
	rb->readIdx = 0;
	rb->writeIdx = 0;
}

//the write functions should be used in the RX ISR call back
int RingBufferWriteByte(RingBuffer_t *rb, uint8_t *in) {
	rb->readIdxTemp = rb->readIdx;
	if (rb->readIdxTemp == ((rb->writeIdx + 1) % rb->size)){
		return -1;
	}
	rb->buffer[rb->writeIdx] = in[0];
	rb->writeIdx = (rb->writeIdx + (1)) % rb->size;
	return 1;
}
int RingBufferWrite(RingBuffer_t *rb, uint8_t *in, int count) {
	rb->readIdxTemp = rb->readIdx;
	rb->availableWrite = rb->writeIdx - rb->readIdxTemp;
	if (rb->availableWrite < 0){
		rb->availableWrite += rb->size;
	}
	if (rb->availableWrite >= rb->size){
		return -1;
	}
	if(rb->availableWrite == 0){
		rb->writeIdx = rb->readIdx = 0;
	}

	if ((rb->size - rb->availableWrite) < count){
		count = (rb->size -rb->availableWrite);
	}
	if (RingWriteIdxToEnd(rb) >= count){
		memcpy(rb->buffer + rb->writeIdx, in, count);
	}else{
		memcpy(rb->buffer + rb->writeIdx, in, RingWriteIdxToEnd(rb));
		memcpy(rb->buffer, in + RingWriteIdxToEnd(rb), count - RingWriteIdxToEnd(rb));
	}
	RingBufferCommitWrite(rb, count);
	return count;
}
int RingBufferRead(RingBuffer_t *rb, uint8_t *out, int count){
	rb->writeIdxTemp = rb->writeIdx;
	rb->availableRead = rb->writeIdxTemp - rb->readIdx;
	if (rb->availableRead < 0){
		rb->availableRead += rb->size;
	}
	if (rb->availableRead == 0){
		return -1;
	}

	if (rb->availableRead < count){
		count = rb->availableRead;
	}
	if (rb->writeIdxTemp > rb->readIdx){
		memcpy(out, rb->buffer + rb->readIdx, count);
		RingBufferCommitRead(rb,count);
		return count;
	}
	if (RingReadIdxToEnd(rb) >= count){
		memcpy(out, rb->buffer + rb->readIdx, count);
		RingBufferCommitRead(rb,count);
		return count;
	}else{
		memcpy(out, rb->buffer + rb->readIdx, RingReadIdxToEnd(rb));
		memcpy(out, rb->buffer , count - RingReadIdxToEnd(rb));
	}
	RingBufferCommitRead(rb,count);
	return count;
}



















