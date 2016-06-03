/*
 * RingBuffer.c
 *
 *  Created on: Jun 3, 2016
 *      Author: work
 */
#include "RingBuffer.h"

void RingBuffer_create(RingBuffer_t *rb,uint8_t *buffer ,int sizeOfBuffer){
	rb->buffer = buffer;
	rb->size = sizeOfBuffer;
	rb->readIdx = 0;
	rb->writeIdx = 0;
	rb->available = 0;
}

int RingBuffer_write(RingBuffer_t *rb,char *in,int count){
	//check if the count is over the buffer size
	if (count > rb->size){
			return 1;
	}
	if (rb->available == 0){
		rb->readIdx = 0;
		rb->writeIdx = count - 1;
		memcpy(&rb->buffer[rb->writeIdx],in,count);
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
			return 2;
		}else{
			//update available
			if (rb->writeIdx > rb->readIdx){
				rb->available = rb->writeIdx - rb->readIdx + 1;
			}else{
				rb->available = rb->size - rb->readIdx + rb->writeIdx + 1;
			}
		}
	}

	return 0;

}

int RingBuffer_read(RingBuffer_t *rb,char *out,int count){
	/*if (count > rb->available){
		return 1;
	}
	if (rb->readIdx + count < rb->size){
		memcpy(out,&rb->buffer[rb->readIdx],count);
		rb->readIdx += count;
	}else{
		size_t part = rb->size - rb->readIdx ;
		memcpy(out,&rb->buffer[rb->readIdx],  part);
		memcpy(out + part, rb->buffer, count - part);
		rb->readIdx = count - part - 1;
	}*/

	return 0;
}











