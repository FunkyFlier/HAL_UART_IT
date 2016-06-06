/*
 * RingBuffer.c
 *
 *  Created on: Jun 3, 2016
 *      Author: work
 */
#include "RingBuffer.h"
//to do status codes to defines
void RingBufferCreate(RingBuffer_t *rb,uint8_t *buffer ,int sizeOfBuffer){
	rb->buffer = buffer;
	rb->size = sizeOfBuffer;
	rb->readIdx = 0;
	rb->writeIdx = 0;
	rb->available = 0;
}

int RingBufferWrite(RingBuffer_t *rb,uint8_t *in,int count){
	//check if the count is over the buffer size
	if (count > rb->size){
			return 1;
	}
	if (rb->available == 0){
		rb->readIdx = 0;
		rb->writeIdx = 0;
		memcpy(&rb->buffer[rb->writeIdx],in,count);
		rb->writeIdx = count - 1;
		rb->available = count;
	}else{
		//add data to buffer
		if (rb->writeIdx + count < rb->size){
			//copy
			memcpy(&rb->buffer[rb->writeIdx + 1],in,count);
			rb->writeIdx += count;
		}else{
			//wrap copy
			size_t part = rb->size - rb->writeIdx - 1;
			memcpy(&rb->buffer[rb->writeIdx + 1], in, part);
			memcpy(rb->buffer, in + part, count - part);
			rb->writeIdx = count - part - 1;
		}
		if (count + rb->available > rb->size ){
			rb->readIdx = rb->writeIdx + 1;
			if (rb->readIdx == rb->size){
				rb->readIdx = 0;
			}
			rb->available = rb->size;
			return 2;
		}else{
			rb->available += count;
		}
	}

	return 0;

}
//error returns negative
//no error returns zero or number bytes out
int RingBufferRead(RingBuffer_t *rb,uint8_t *out,int count){

	if (count > rb->available){
		return 1;
	}
	if (rb->available == 0){
		return 2;
	}
	if (rb->readIdx < rb->writeIdx){
		memcpy(out,&rb->buffer[rb->readIdx],count);
		rb->readIdx += count;
		rb->available -= count;
	}else{
		size_t part = rb->size - rb->readIdx ;
		memcpy(out,&rb->buffer[rb->readIdx],  part);
		memcpy(out + part, rb->buffer, count - part);
		rb->readIdx = count - part - 1;
		rb->available -= count;
	}
	if (rb->available == 0){
		rb->readIdx = 0;
		rb->writeIdx = 0;
	}


	return 0;
}












