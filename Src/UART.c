/*
 * UART.c
 *
 *  Created on: Jun 6, 2016
 *      Author: Michael Baker
 *      Works up to 230400 for loop back
 */

#include <UART.h>

extern int inByteCount, outByteCount, lostByteCount,fixISRCount;
extern volatile int infiniteLoopCounter;

void UARTSetup(UART_STRUCT*, UART_HandleTypeDef*, volatile RingBuffer_t*,
		volatile RingBuffer_t*, uint8_t*);

void UARTTXCallBackHandler(UART_STRUCT*);
void UARTRXCallBackHandler(UART_STRUCT*);

void UARTInit() {
#ifdef UART_1
	RingBufferCreate(&UART_1_RX_RING, UART_1_RX_BUFFER,(int) sizeof(UART_1_RX_BUFFER));
	RingBufferCreate(&UART_1_TX_RING, UART_1_TX_BUFFER,(int) sizeof(UART_1_TX_BUFFER));
	UARTSetup(&UART_1_STRUCT, &huart1, &UART_1_RX_RING, &UART_1_TX_RING,ISRBuffer_1);
	if (HAL_UART_Receive_IT(UART_1_STRUCT.uartHandler, (uint8_t *) ISRBuffer_1, 1) != HAL_OK) {
#ifdef DEBUG_TO_CONSOLE
		printf("uart1 was not enabled\n");
#endif//DEBUG_TO_CONSOLE
	}
#endif//UART_1
#ifdef UART_2
	RingBufferCreate(&UART_2_RX_RING, UART_2_RX_BUFFER,(int) sizeof(UART_2_RX_BUFFER));
	RingBufferCreate(&UART_2_TX_RING, UART_2_TX_BUFFER,(int) sizeof(UART_2_TX_BUFFER));
	UARTSetup(&UART_2_STRUCT, &huart2, &UART_2_RX_RING, &UART_2_TX_RING,ISRBuffer_2);
	if (HAL_UART_Receive_IT(UART_2_STRUCT.uartHandler, UART_2_STRUCT.ISRBuf, 1)!= HAL_OK) {
#ifdef DEBUG_TO_CONSOLE
		printf("uart2 was not enabled\n");
#endif//DEBUG_TO_CONSOLE
	}
#endif//UART_2
#ifdef UART_3
	RingBufferCreate(&UART_3_RX_RING, UART_3_RX_BUFFER,(int) sizeof(UART_3_RX_BUFFER));
	RingBufferCreate(&UART_3_TX_RING, UART_3_TX_BUFFER,(int) sizeof(UART_3_TX_BUFFER));
	UARTSetup(&UART_3_STRUCT, &huart3, &UART_3_RX_RING, &UART_3_TX_RING,ISRBuffer_3);
	if (HAL_UART_Receive_IT(UART_3_STRUCT.uartHandler, (uint8_t *) ISRBuffer_3,1) != HAL_OK) {
#ifdef DEBUG_TO_CONSOLE
		printf("uart3 was not enabled\n");
#endif//DEBUG_TO_CONSOLE
	}
#endif//UART_3
#ifdef UART_4
	RingBufferCreate(&UART_4_RX_RING, UART_4_RX_BUFFER,(int) sizeof(UART_4_RX_BUFFER));
	RingBufferCreate(&UART_4_TX_RING, UART_4_TX_BUFFER,(int) sizeof(UART_4_TX_BUFFER));
	UARTSetup(&UART_4_STRUCT, &huart4, &UART_4_RX_RING, &UART_4_TX_RING,ISRBuffer_4);
	if (HAL_UART_Receive_IT(UART_4_STRUCT.uartHandler, (uint8_t *) ISRBuffer_4,1) != HAL_OK) {
#ifdef DEBUG_TO_CONSOLE
		printf("uart4 was not enabled\n");
#endif//DEBUG_TO_CONSOLE
	}
#endif//UART_4
#ifdef UART_5
	RingBufferCreate(&UART_5_RX_RING, UART_5_RX_BUFFER,(int) sizeof(UART_5_RX_BUFFER));
	RingBufferCreate(&UART_5_TX_RING, UART_5_TX_BUFFER,(int) sizeof(UART_5_TX_BUFFER));
	UARTSetup(&UART_5_STRUCT, &huart5, &UART_5_RX_RING, &UART_5_TX_RING,ISRBuffer_5);
	if (HAL_UART_Receive_IT(UART_5_STRUCT.uartHandler, (uint8_t *) ISRBuffer_5,1) != HAL_OK) {
#ifdef DEBUG_TO_CONSOLE
		printf("uart5 was not enabled\n");
#endif//DEBUG_TO_CONSOLE
	}
#endif//UART_5
#ifdef UART_6
	RingBufferCreate(&UART_6_RX_RING, UART_6_RX_BUFFER,(int) sizeof(UART_6_RX_BUFFER));
	RingBufferCreate(&UART_6_TX_RING, UART_6_TX_BUFFER,(int) sizeof(UART_6_TX_BUFFER));
	UARTSetup(&UART_6_STRUCT, &huart6, &UART_6_RX_RING, &UART_6_TX_RING,ISRBuffer_6);
	if (HAL_UART_Receive_IT(UART_6_STRUCT.uartHandler, (uint8_t *) ISRBuffer_6,1) != HAL_OK) {
#ifdef DEBUG_TO_CONSOLE
		printf("uart6 was not enabled\n");
#endif//DEBUG_TO_CONSOLE
	}
#endif//UART_6
#ifdef UART_7
	RingBufferCreate(&UART_7_RX_RING, UART_7_RX_BUFFER,(int) sizeof(UART_7_RX_BUFFER));
	RingBufferCreate(&UART_7_TX_RING, UART_7_TX_BUFFER,(int) sizeof(UART_7_TX_BUFFER));
	UARTSetup(&UART_7_STRUCT, &huart7, &UART_7_RX_RING, &UART_7_TX_RING,ISRBuffer_7);
	if (HAL_UART_Receive_IT(UART_7_STRUCT.uartHandler, (uint8_t *) ISRBuffer_7,1) != HAL_OK) {
#ifdef DEBUG_TO_CONSOLE
		printf("uart7 was not enabled\n");
#endif//DEBUG_TO_CONSOLE
	}
#endif//UART_7
#ifdef UART_8
	RingBufferCreate(&UART_8_RX_RING, UART_8_RX_BUFFER,(int) sizeof(UART_8_RX_BUFFER));
	RingBufferCreate(&UART_8_TX_RING, UART_8_TX_BUFFER,(int) sizeof(UART_8_TX_BUFFER));
	UARTSetup(&UART_8_STRUCT, &huart8, &UART_8_RX_RING, &UART_8_TX_RING,ISRBuffer_8);
	if (HAL_UART_Receive_IT(UART_8_STRUCT.uartHandler, (uint8_t *) ISRBuffer_8,1) != HAL_OK) {
#ifdef DEBUG_TO_CONSOLE
		printf("uart8 was not enabled\n");
#endif//DEBUG_TO_CONSOLE
	}
#endif//UART_8
}

//setup
void UARTSetup(UART_STRUCT* uartS, UART_HandleTypeDef* uartH,volatile RingBuffer_t* rbRX, volatile RingBuffer_t* rbTX,uint8_t* ISRBuf) {
	uartS->uartHandler = uartH;
	uartS->rxBuffer = rbRX;
	uartS->txBuffer = rbTX;
	uartS->ISRBuf = ISRBuf;
	uartS->transmit = false;
	//uartS->fixTxISR = false;
}
//end setup

//byte and buffer IO
int UARTWriteByte(UART_STRUCT* uartS, uint8_t* buff) {
	return UARTWriteBuffer(uartS, buff, 1);
}
int UARTWriteBuffer(UART_STRUCT* uartS, uint8_t* buff, int n) {
	//to do return number of bytes written
	if (HAL_UART_Transmit_IT(uartS->uartHandler, buff, n) == HAL_BUSY) {
		//check if buffer will be overrun
		if (RingBufferAvailable(uartS->txBuffer) + n > UART_RING_BUF_SIZE_TX) {
			RingBufferWrite(uartS->txBuffer, buff,
			UART_RING_BUF_SIZE_TX - RingBufferAvailable(uartS->txBuffer));
			//return UART_RING_BUF_SIZE_TX - RingBufferAvailable(uartS->txBuffer);
		} else {
			RingBufferWrite(uartS->txBuffer, buff, n);
		}
	} else {
		outByteCount += n;
	}
	//handle interrupt firing during RingBufferWrite
	if (uartS->transmit == true) {
		uartS->transmit = false;
		uartS->txBuffer->locked = true;
		if (uartS->txBuffer->available != 0) {
			//todo removed might cause trouble
			HAL_UART_Transmit_IT(uartS->uartHandler, uartS->txBuffer->buffer,uartS->txBuffer->available);
			outByteCount += uartS->txBuffer->available;
			uartS->txBuffer->available = 0;
			uartS->txBuffer->readIdx = 0;
			uartS->txBuffer->writeIdx = 0;
		}
		uartS->txBuffer->locked = false;
	}
	return 0;
}
void UARTTXCallBackHandler(UART_STRUCT* uartS) {
	//check if ring buffer is currently writing
	//if so UARTWriteBuffer becomes blocking
	if (uartS->txBuffer->locked == true) {
		uartS->transmit = true;
		return;
	} else {
		uartS->txBuffer->locked = true;
		if (uartS->txBuffer->available != 0) {
			HAL_UART_Transmit_IT(uartS->uartHandler, uartS->txBuffer->buffer,uartS->txBuffer->available);
			outByteCount += uartS->txBuffer->available;
			uartS->txBuffer->available = 0;
			uartS->txBuffer->readIdx = 0;
			uartS->txBuffer->writeIdx = 0;
		}
		uartS->txBuffer->locked = false;

	}
}
int UARTAvailabe(UART_STRUCT* uartS) {
	return RingBufferAvailable(uartS->rxBuffer);
}
int UARTGetByte(UART_STRUCT* uartS, uint8_t* buff) {
	return UARTGetBuffer(uartS, buff, 1);
}
int UARTGetBuffer(UART_STRUCT* uartS, uint8_t* buff, int n) {
	if (RingBufferAvailable(uartS->rxBuffer) == 0) {
		return -1;
	}
	if (RingBufferAvailable(uartS->rxBuffer) < n) {
		n = RingBufferAvailable(uartS->rxBuffer);
	}

	n = RingBufferRead(uartS->rxBuffer, buff, n);
	//interrupt fired during buffer access
	if (UART_2_STRUCT.readWriteCollision == true) {
		//todo testing if this simplified version works
		RingBufferWriteByte(uartS->rxBuffer, &uartS->collisionByte);
		UART_2_STRUCT.readWriteCollision = false;
	}
	return n;
}

void UARTRXCallBackHandler(UART_STRUCT* uartS) {
	HAL_StatusTypeDef debugStatus;
	__HAL_UART_FLUSH_DRREGISTER(uartS->uartHandler);
	if (RingBufferWriteByte(uartS->rxBuffer, uartS->ISRBuf) == -1) {
		if (UART_2_STRUCT.readWriteCollision == true) {
			lostByteCount++;
		}
		UART_2_STRUCT.readWriteCollision = true;
		uartS->collisionByte = uartS->ISRBuf[0];
	}
	inByteCount++;

	//kludge because the RX and TX share the same interrupt and lock the UART
	if (HAL_UART_Receive_IT(uartS->uartHandler, uartS->ISRBuf, 1) != HAL_OK) {
		if (uartS->uartHandler->RxState == HAL_UART_STATE_READY){
			  if(uartS->uartHandler->RxState == HAL_UART_STATE_READY)
			  {
			    uartS->uartHandler->pRxBuffPtr = uartS->ISRBuf;
			    uartS->uartHandler->RxXferSize = 1;
			    uartS->uartHandler->RxXferCount = 1;
			    uartS->uartHandler->ErrorCode = HAL_UART_ERROR_NONE;
			    uartS->uartHandler->RxState = HAL_UART_STATE_BUSY_RX;
			    /* Enable the UART Parity Error Interrupt */
			    SET_BIT(uartS->uartHandler->Instance->CR1, USART_CR1_PEIE);
			    /* Enable the UART Error Interrupt: (Frame error, noise error, overrun error) */
			    SET_BIT(uartS->uartHandler->Instance->CR3, USART_CR3_EIE);
			    /* Enable the UART Data Register not empty Interrupt */
			     SET_BIT(uartS->uartHandler->Instance->CR1, USART_CR1_RXNEIE);
			    //return HAL_OK;
			  }
		}

	}



}
//end byte and buffer IO
//ISR callbacks
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	//this function puts the received byte into the correct ring buffer
	switch ((uint32_t) huart->Instance) {
#ifdef USART1
	case (uint32_t) USART1:
#ifdef UART_1
		UARTRXCallBackHandler(&UART_1_STRUCT);
#endif//UART_1
		break;
#endif//USART1
#ifdef USART2
	case (uint32_t) USART2:
#ifdef UART_2
		UARTRXCallBackHandler(&UART_2_STRUCT);
#endif//UART_2
		break;
#endif//USART2
#ifdef USART3
		case (uint32_t)USART3:
#ifdef UART_3
		UARTRXCallBackHandler(&UART_3_STRUCT);
#endif//UART_3
		break;
#endif//USART3
#ifdef UART3
		case (uint32_t)UART4:
#ifdef UART_4
		UARTRXCallBackHandler(&UART_4_STRUCT);
#endif//UART_4
		break;
#endif//USART4
#ifdef UART5
		case (uint32_t)UART5:
#ifdef UART_5
		UARTRXCallBackHandler(&UART_5_STRUCT);
#endif//UART_5
		break;
#endif//USART5
#ifdef USART6
	case (uint32_t) USART6:
#ifdef UART_6
		UARTRXCallBackHandler(&UART_6_STRUCT);
#endif//UART_6
		break;
#endif//USART6
#ifdef UART7
		case (uint32_t)UART7:
#ifdef UART_7
		UARTRXCallBackHandler(&UART_7_STRUCT);
#endif//UART_7
		break;
#endif//USART7
#ifdef USART8
		case (uint32_t)USART8:
#ifdef UART_8
		UARTRXCallBackHandler(&UART_8_STRUCT);
#endif//UART_8
		break;
#endif//USART8
	}

}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {

	switch ((uint32_t) huart->Instance) {
#ifdef USART1
	case (uint32_t) USART1:
#ifdef UART_1
		UARTTXCallBackHandler(&UART_1_STRUCT);
#endif//UART_1
		break;
#endif//USART1
#ifdef USART2
	case (uint32_t) USART2:
#ifdef UART_2
		UARTTXCallBackHandler(&UART_2_STRUCT);
#endif//UART_2
		break;
#endif//USART2
#ifdef USART3
		case (uint32_t)USART3:
#ifdef UART_3
		UARTTXCallBackHandler(&UART_3_STRUCT);
#endif//UART_3
		break;
#endif//USART3
#ifdef UART3
		case (uint32_t)UART4:
#ifdef UART_4
		UARTTXCallBackHandler(&UART_4_STRUCT);
#endif//UART_4
		break;
#endif//USART4
#ifdef UART5
		case (uint32_t)UART5:
#ifdef UART_5
		UARTTXCallBackHandler(&UART_5_STRUCT);
#endif//UART_5
		break;
#endif//USART5
#ifdef USART6
	case (uint32_t) USART6:
#ifdef UART_6
		UARTTXCallBackHandler(&UART_6_STRUCT);
#endif//UART_6
		break;
#endif//USART6
#ifdef UART7
		case (uint32_t)UART7:
#ifdef UART_7
		UARTTXCallBackHandler(&UART_7_STRUCT);
#endif//UART_7
		break;
#endif//USART7
#ifdef USART8
		case (uint32_t)USART8:
#ifdef UART_8
		UARTTXCallBackHandler(&UART_8_STRUCT);
#endif//UART_8
		break;
#endif//USART8
	}
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart) {
#ifdef DEBUG_TO_CONSOLE
	//printf("uart error: %lu\n", huart->ErrorCode);
	printf("u E: %i\nu S: %i\n", (int) HAL_UART_GetError(huart),
			(int) HAL_UART_GetState(huart));
#endif
}
void RingBufferCreate(RingBuffer_t *rb, uint8_t *buffer, int sizeOfBuffer) {
	rb->buffer = buffer;
	rb->size = sizeOfBuffer;
	rb->readIdx = 0;
	rb->writeIdx = 0;
	rb->available = 0;
	rb->locked = false;
}
/*
 * These functions will return -1 on error or number of bytes written
 * Overrun on write returns the size of the buffer + 1
 */
int RingBufferWriteByte(RingBuffer_t *rb, uint8_t *in) {
	if (rb->locked == true) {

		return -1;
	}
	rb->locked = true;
	rb->buffer[rb->writeIdx] = *in;
	rb->writeIdx++;
	rb->available++;
	if (rb->writeIdx == rb->size) {
		rb->writeIdx = 0;
	}
	if (rb->writeIdx == rb->readIdx) {
		rb->readIdx++;
		rb->available = rb->size;
	}

	rb->locked = false;
	return 0;
}
int RingBufferWrite(RingBuffer_t *rb, uint8_t *in, int count) {
	if (count > rb->size) {
		return -1;
	}
	if (rb->locked == true) {
		return -1;
	}
	rb->locked = true;
	if (rb->available == 0) {
		rb->readIdx = 0;
		rb->writeIdx = 0;
		memcpy(&rb->buffer[rb->writeIdx], in, count);
		rb->writeIdx = count - 1;
		rb->available = count;
	} else {
		if (rb->writeIdx + count < rb->size) {
			memcpy(&rb->buffer[rb->writeIdx + 1], in, count);
			rb->writeIdx += count;
		} else {
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
			rb->locked = false;
			return rb->size + 1;
		} else {
			rb->available += count;
		}
	}
	rb->locked = false;
	return count;

}

int RingBufferRead(RingBuffer_t *rb, uint8_t *out, int count) {
	if (rb->locked == true) {
		return -1;
	}
	if (rb->available == 0) {
		return -1;
	}

	rb->locked = true;
	if (count > rb->available) {
		count = rb->available;
	}
	if ((rb->readIdx < rb->writeIdx)
			|| ((rb->readIdx > rb->writeIdx)
					&& ((rb->size - rb->readIdx) >= count))
			|| rb->readIdx == rb->writeIdx) {
		memcpy(out, &rb->buffer[rb->readIdx], count);
		rb->readIdx += count;
		rb->available -= count;
	} else {
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
	rb->locked = false;
	return count;
}
int RingBufferAvailable(RingBuffer_t *rb) {
	while (rb->locked == true) {
	}
	return rb->available;
}

//end ISR callbacks
//streamings
/*#ifdef UART_STREAMING
 #define UART_STREAM_HANDLER UART_2_STRUCT
 FILE* UART_STREAM_CONFIG() {
 uart_Stream = funopen(cookiePointer, UART_PUTC, UART_GETC,NULL, NULL);
 return uart_Stream;
 }
 int UART_PUTC(void *cookie, char *buf, int n) {
 if (UARTWriteBuffer(&UART_STREAM_HANDLER, (uint8_t*)buf, n) != 0) {
 printf("putc\n");
 return -1;
 }
 return 0;
 }
 int UART_GETC(void *cookie, const char *buf, int n) {
 if (UARTGetBuffer(&UART_STREAM_HANDLER, (uint8_t*)buf, n) != 0) {
 printf("getc\n");
 return -1;
 }
 return 0;
 }
 #endif*/
//end streaming
