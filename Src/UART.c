/*
 * UART.c
 *
 *  Created on: Jun 6, 2016
 *      Author: Michael Baker
 *      Works up to 230400 for loop back
 */

#include <UART.h>

//extern int inByteCount, outByteCount, lostByteCount,fixISRCount;
//extern volatile int infiniteLoopCounter;

void UARTSetup(UART_STRUCT*, UART_HandleTypeDef*, RingBuffer_t*,
		DoubleBuffer_t*, uint8_t*);

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
	RingBufferCreate(&UART_2_RX_RING, UART_2_RX_BUFFER,(int) UART_RING_BUF_SIZE_RX);
	DoubleBufferCreate(&UART_2_TX_DB, UART_2_TX_BUFFER1,UART_2_TX_BUFFER2,(int) UART_RING_BUF_SIZE_TX);
	UARTSetup(&UART_2_STRUCT, &huart2, &UART_2_RX_RING, &UART_2_TX_DB,ISRBuffer_2);
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
void UARTSetup(UART_STRUCT* uartS, UART_HandleTypeDef* uartH,RingBuffer_t* rbRX, DoubleBuffer_t* dbTX,uint8_t* ISRBuf) {
	uartS->uartHandler = uartH;
	uartS->rxBuffer = rbRX;
	uartS->txBuffer = dbTX;
	uartS->ISRBuf = ISRBuf;
	uartS->RXOverRun = false;
	uartS->TXOverRun = false;
}
//end setup

//byte and buffer IO
int UARTWriteBuffer(UART_STRUCT* uartS, uint8_t* buff, int n) {
	n = DoubleBufferWrite(uartS->txBuffer, buff, n);
	if (n == -1){
		uartS->TXOverRun = true;
	}
	if (DoubleBufferAvailable(uartS->txBuffer) > 0){
		if (HAL_UART_Transmit_IT(uartS->uartHandler, uartS->txBuffer->buffer, DoubleBufferAvailable(uartS->txBuffer)) != HAL_BUSY) {
			DoubleBufferSwap(uartS->txBuffer);
		}
	}
	return n;

}
void UARTTXCallBackHandler(UART_STRUCT* uartS) {
	if (uartS->txBuffer->writing == true) {
		return;
	}
	if (DoubleBufferAvailable(uartS->txBuffer) > 0){
		if (HAL_UART_Transmit_IT(uartS->uartHandler, uartS->txBuffer->buffer, DoubleBufferAvailable(uartS->txBuffer)) != HAL_BUSY) {
			DoubleBufferSwap(uartS->txBuffer);
		}else{
			printf("tx buffer err in ISR\n");
		}
	}

}
int UARTAvailabe(UART_STRUCT* uartS) {
	//return RingBufferAvailable(uartS->rxBuffer);
	return RingBufferAvailable(uartS->rxBuffer);
	//return 0;
}
int UARTGetByte(UART_STRUCT* uartS, uint8_t* buff) {
	//return RingBufferReadByte(uartS->rxBuffer, buff);
	return 0;
}
int UARTGetBuffer(UART_STRUCT* uartS, uint8_t* buff, int n) {
	return RingBufferRead(uartS->rxBuffer,buff,n);
}

void UARTRXCallBackHandler(UART_STRUCT* uartS) {
	if (RingBufferWriteByte(uartS->rxBuffer, uartS->ISRBuf) == -1){
		uartS->TXOverRun = true;
	}
	__HAL_UART_FLUSH_DRREGISTER(uartS->uartHandler);
	if (HAL_UART_Receive_IT(uartS->uartHandler, uartS->ISRBuf, 1) != HAL_OK) {
		if (uartS->uartHandler->RxState == HAL_UART_STATE_READY){
			uartS->uartHandler->RxState = HAL_UART_STATE_BUSY_RX;
			uartS->uartHandler->pRxBuffPtr = uartS->ISRBuf;
			uartS->uartHandler->RxXferSize = 1;
			uartS->uartHandler->RxXferCount = 1;
			uartS->uartHandler->ErrorCode = HAL_UART_ERROR_NONE;
			SET_BIT(uartS->uartHandler->Instance->CR1, USART_CR1_PEIE);
			SET_BIT(uartS->uartHandler->Instance->CR3, USART_CR3_EIE);
			SET_BIT(uartS->uartHandler->Instance->CR1, USART_CR1_RXNEIE);
		  }
	}



}

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
