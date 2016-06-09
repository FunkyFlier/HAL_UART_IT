/*
 * RingBuffer.c
 *
 *  Created on: Jun 3, 2016
 *      Author: work
 */
#include "RingBuffer.h"
//to do status codes to defines
void RingBufferCreate(RingBuffer_t *rb, uint8_t *buffer, int sizeOfBuffer) {
	rb->buffer = buffer;
	rb->size = sizeOfBuffer;
	rb->readIdx = 0;
	rb->writeIdx = 0;
	rb->available = 0;
}

int RingBufferWrite(RingBuffer_t *rb, uint8_t *in, int count) {

	if (count > rb->size) {
		return RB_WRITE_ERR;
	}
	if (rb->available == 0) {
		rb->readIdx = 0;
		rb->writeIdx = 0;
		memcpy(&rb->buffer[rb->writeIdx], in, count);
		rb->writeIdx = count - 1;
		rb->available = count;
	} else {
		//add data to buffer
		if (rb->writeIdx + count < rb->size) {
			//copy
			memcpy(&rb->buffer[rb->writeIdx + 1], in, count);
			rb->writeIdx += count;
		} else {
			//wrap copy
			size_t part = rb->size - rb->writeIdx - 1;
			memcpy(&rb->buffer[rb->writeIdx + 1], in, part);
			memcpy(rb->buffer, in + part, count - part);
			rb->writeIdx = count - part - 1;
		}
		if (count + rb->available > rb->size) {
			rb->readIdx = rb->writeIdx + 1;
			if (rb->readIdx == rb->size) {
				rb->readIdx = 0;
			}
			rb->available = rb->size;
			return RB_WRITE_OVERRUN;
		} else {
			rb->available += count;
		}
	}

	return RB_WRITE_OK;

}

int RingBufferRead(RingBuffer_t *rb, uint8_t *out, int count) {
	if (count > rb->available || rb->available == 0) {
		return RB_READ_ERR;
	}

	if ((rb->readIdx < rb->writeIdx)
			|| ((rb->readIdx > rb->writeIdx) && ((rb->size - rb->readIdx) >= count))) {
		//no wrap
		memcpy(out, &rb->buffer[rb->readIdx], count);
		rb->readIdx += count;
		rb->available -= count;
	} else {
		//wrap required
		size_t part = rb->size - rb->readIdx;
		memcpy(out, &rb->buffer[rb->readIdx], part);
		memcpy(out + part, rb->buffer, count - part);
		rb->readIdx = count - part - 1;
		rb->available -= count;
	}
	if (rb->available == 0) {
		rb->readIdx = 0;
		rb->writeIdx = 0;
	}

	return RB_READ_OK;
}

