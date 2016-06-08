/*
 * UART.c
 *
 *  Created on: Jun 6, 2016
 *      Author: work
 */

#include <UART.h>

void UARTSetup(UART_STRUCT*, UART_HandleTypeDef*, volatile RingBuffer_t*,
		volatile RingBuffer_t*);

void UARTInit() {

#ifdef UART_1
	RingBufferCreate(&UART_1_RX_RING,UART_1_RX_BUFFER,(int)sizeof(UART_1_RX_BUFFER));
	RingBufferCreate(&UART_1_TX_RING,UART_1_TX_BUFFER,(int)sizeof(UART_1_TX_BUFFER));
	UARTSetup(&UART_1_STRUCT,&huart1,&UART_1_RX_RING,&UART_1_TX_RING);
	if (HAL_UART_Receive_IT(UART_1_STRUCT.uartHandler, (uint8_t *) ISRBuffer_1,
					1) != HAL_OK) {
#ifdef DEBUG_TO_CONSOLE
		printf("uart1 was not enabled\n");
#endif//DEBUG_TO_CONSOLE
	}
#endif//UART_1
#ifdef UART_2
	RingBufferCreate(&UART_2_RX_RING, UART_2_RX_BUFFER,(int) sizeof(UART_2_RX_BUFFER));
	RingBufferCreate(&UART_2_TX_RING, UART_2_TX_BUFFER,(int) sizeof(UART_2_TX_BUFFER));
	UARTSetup(&UART_2_STRUCT, &huart2, &UART_2_RX_RING, &UART_2_TX_RING);
	if (HAL_UART_Receive_IT(UART_2_STRUCT.uartHandler, (uint8_t *) ISRBuffer_2,
			1) != HAL_OK) {
#ifdef DEBUG_TO_CONSOLE
		printf("uart2 was not enabled\n");
#endif//DEBUG_TO_CONSOLE
	}
#endif//UART_2
#ifdef UART_3
	RingBufferCreate(&UART_3_RX_RING,UART_3_RX_BUFFER,(int)sizeof(UART_3_RX_BUFFER));
	RingBufferCreate(&UART_3_TX_RING,UART_3_TX_BUFFER,(int)sizeof(UART_3_TX_BUFFER));
	UARTSetup(&UART_3_STRUCT,&huart3,&UART_3_RX_RING,&UART_3_TX_RING);
	if (HAL_UART_Receive_IT(UART_3_STRUCT.uartHandler, (uint8_t *) ISRBuffer_3,
					1) != HAL_OK) {
#ifdef DEBUG_TO_CONSOLE
		printf("uart3 was not enabled\n");
#endif//DEBUG_TO_CONSOLE
	}
#endif//UART_3
#ifdef UART_4
	RingBufferCreate(&UART_4_RX_RING,UART_4_RX_BUFFER,(int)sizeof(UART_4_RX_BUFFER));
	RingBufferCreate(&UART_4_TX_RING,UART_4_TX_BUFFER,(int)sizeof(UART_4_TX_BUFFER));
	UARTSetup(&UART_4_STRUCT,&huart4,&UART_4_RX_RING,&UART_4_TX_RING);
	if (HAL_UART_Receive_IT(UART_4_STRUCT.uartHandler, (uint8_t *) ISRBuffer_4,
					1) != HAL_OK) {
#ifdef DEBUG_TO_CONSOLE
		printf("uart4 was not enabled\n");
#endif//DEBUG_TO_CONSOLE
	}
#endif//UART_4
#ifdef UART_5
	RingBufferCreate(&UART_5_RX_RING,UART_5_RX_BUFFER,(int)sizeof(UART_5_RX_BUFFER));
	RingBufferCreate(&UART_5_TX_RING,UART_5_TX_BUFFER,(int)sizeof(UART_5_TX_BUFFER));
	UARTSetup(&UART_5_STRUCT,&huart5,&UART_5_RX_RING,&UART_5_TX_RING);
	if (HAL_UART_Receive_IT(UART_5_STRUCT.uartHandler, (uint8_t *) ISRBuffer_5,
					1) != HAL_OK) {
#ifdef DEBUG_TO_CONSOLE
		printf("uart5 was not enabled\n");
#endif//DEBUG_TO_CONSOLE
	}
#endif//UART_5
#ifdef UART_6
	RingBufferCreate(&UART_6_RX_RING,UART_6_RX_BUFFER,(int)sizeof(UART_6_RX_BUFFER));
	RingBufferCreate(&UART_6_TX_RING,UART_6_TX_BUFFER,(int)sizeof(UART_6_TX_BUFFER));
	UARTSetup(&UART_6_STRUCT,&huart6,&UART_6_RX_RING,&UART_6_TX_RING);
	if (HAL_UART_Receive_IT(UART_6_STRUCT.uartHandler, (uint8_t *) ISRBuffer_6,
					1) != HAL_OK) {
#ifdef DEBUG_TO_CONSOLE
		printf("uart6 was not enabled\n");
#endif//DEBUG_TO_CONSOLE
	}
#endif//UART_6
#ifdef UART_7
	RingBufferCreate(&UART_7_RX_RING,UART_7_RX_BUFFER,(int)sizeof(UART_7_RX_BUFFER));
	RingBufferCreate(&UART_7_TX_RING,UART_7_TX_BUFFER,(int)sizeof(UART_7_TX_BUFFER));
	UARTSetup(&UART_7_STRUCT,&huart7,&UART_7_RX_RING,&UART_7_TX_RING);
	if (HAL_UART_Receive_IT(UART_7_STRUCT.uartHandler, (uint8_t *) ISRBuffer_7,
					1) != HAL_OK) {
#ifdef DEBUG_TO_CONSOLE
		printf("uart7 was not enabled\n");
#endif//DEBUG_TO_CONSOLE
	}
#endif//UART_7
#ifdef UART_8
	RingBufferCreate(&UART_8_RX_RING,UART_8_RX_BUFFER,(int)sizeof(UART_8_RX_BUFFER));
	RingBufferCreate(&UART_8_TX_RING,UART_8_TX_BUFFER,(int)sizeof(UART_8_TX_BUFFER));
	UARTSetup(&UART_8_STRUCT,&huart8,&UART_8_RX_RING,&UART_8_TX_RING);
	if (HAL_UART_Receive_IT(UART_8_STRUCT.uartHandler, (uint8_t *) ISRBuffer_8,
					1) != HAL_OK) {
#ifdef DEBUG_TO_CONSOLE
		printf("uart8 was not enabled\n");
#endif//DEBUG_TO_CONSOLE
	}
#endif//UART_8
}
//setup
void UARTSetup(UART_STRUCT* uartS, UART_HandleTypeDef* uartH,
		volatile RingBuffer_t* rbRX, volatile RingBuffer_t* rbTX) {
	uartS->uartHandler = uartH;
	uartS->rxBuffer = rbRX;
	uartS->txBuffer = rbTX;
}
//end setup

//byte and buffer IO
int UARTWriteByte(UART_STRUCT* uartS, uint8_t* buff) {
	if (HAL_UART_Transmit_IT(uartS->uartHandler, buff, 1) == HAL_BUSY) {
		//todo return error based on the ring buffer error returns
		RingBufferWrite(uartS->txBuffer, buff, 1);
		return -1;
	}
	return 0;
}
int UARTWriteBuffer(UART_STRUCT* uartS, uint8_t* buff, int n) {
	if (HAL_UART_Transmit_IT(uartS->uartHandler, buff, n) == HAL_BUSY) {
		RingBufferWrite(uartS->txBuffer, buff, n);
		return -1;
	}
	return 0;
}
int UARTGetByte(UART_STRUCT* uartS, uint8_t* buff) {
	if (uartS->rxBuffer->available == 0) {
		return -1;
	}
	RingBufferRead(uartS->rxBuffer, buff, 1);
	return 0;
}
int UARTGetBuffer(UART_STRUCT* uartS, uint8_t* buff, int n) {
	if (uartS->rxBuffer->available == 0 || uartS->rxBuffer->available < n) {
		return -1;
	}

	RingBufferRead(uartS->rxBuffer, buff, n);
	return 0;
}
//end byte and buffer IO
//ISR callbacks
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	//this function puts the recieved byte into the correct ring buffer
	switch ((uint32_t) huart->Instance) {
#ifdef USART1
	case (uint32_t) USART1:
#ifdef UART_1
#endif//UART_1
		break;
#endif//USART1
#ifdef USART2
	case (uint32_t) USART2:
#ifdef UART_2
		HAL_GPIO_TogglePin(LD6_GPIO_Port, LD6_Pin);
		RingBufferWrite(UART_2_STRUCT.rxBuffer, ISRBuffer_2, 1);
		__HAL_UART_FLUSH_DRREGISTER(huart);
		if (HAL_UART_Receive_IT(UART_2_STRUCT.uartHandler,
				(uint8_t *) ISRBuffer_2, 1) != HAL_OK) {
			printf("uart2 failed in call back\n");
		}
#endif//UART_2
		break;
#endif//USART2
#ifdef USART3
		case (uint32_t)USART3:
#ifdef UART_3
#endif//UART_3
		break;
#endif//USART3
#ifdef UART3
		case (uint32_t)UART4:
#ifdef UART_4
#endif//UART_4
		break;
#endif//USART4
#ifdef UART5
		case (uint32_t)UART5:
#ifdef UART_5
#endif//UART_5
		break;
#endif//USART5
#ifdef USART6
	case (uint32_t) USART6:
#ifdef UART_6
#endif//UART_6
		break;
#endif//USART6
#ifdef UART7
		case (uint32_t)UART7:
#ifdef UART_7
#endif//UART_7
		break;
#endif//USART7
#ifdef USART8
		case (uint32_t)USART8:
#ifdef UART_8
#endif//UART_8
		break;
#endif//USART8
	}

}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
	//will be implimented similiarly to the RX call back
	//this will check to see if the output ring buffer has any data in it
	//and if so transmit the data which was written to the buffer while the previous data was transmitting
	switch ((uint32_t) huart->Instance) {
#ifdef USART1
	case (uint32_t) USART1:
#ifdef UART_1
#endif//UART_1
		break;
#endif//USART1
#ifdef USART2
	case (uint32_t) USART2:
#ifdef UART_2
		HAL_GPIO_TogglePin(LD5_GPIO_Port, LD5_Pin);
		if (UART_2_STRUCT.txBuffer->available > 0) {
			HAL_UART_Transmit_IT(UART_2_STRUCT.uartHandler,
					UART_2_STRUCT.txBuffer->buffer,
					UART_2_STRUCT.txBuffer->available);
			UART_2_STRUCT.txBuffer->available = 0;
		}
#endif//UART_2
		break;
#endif//USART2
#ifdef USART3
		case (uint32_t)USART3:
#ifdef UART_3
#endif//UART_3
		break;
#endif//USART3
#ifdef UART3
		case (uint32_t)UART4:
#ifdef UART_4
#endif//UART_4
		break;
#endif//USART4
#ifdef UART5
		case (uint32_t)UART5:
#ifdef UART_5
#endif//UART_5
		break;
#endif//USART5
#ifdef USART6
	case (uint32_t) USART6:
#ifdef UART_6
#endif//UART_6
		break;
#endif//USART6
#ifdef UART7
		case (uint32_t)UART7:
#ifdef UART_7
#endif//UART_7
		break;
#endif//USART7
#ifdef USART8
		case (uint32_t)USART8:
#ifdef UART_8
#endif//UART_8
		break;
#endif//USART8
	}
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart) {
#ifdef DEBUG_TO_CONSOLE
	printf("uart error: %lu\n", huart->ErrorCode);
#endif
}
/*
 //end ISR callbacks
 //streaming
 #ifdef UART_STREAMING
 FILE* UART_STREAM_CONFIG(){
 const cookie_io_functions_t* cookiePointer;
 FILE* uart_Stream = funopen(cookiePointer,UART_PUTC,UART_GETC,NULL,NULL);
 return uart_Stream;
 }
 int UART_PUTC(void *cookie, char *buf,int n){
 return 0;
 }
 int UART_GETC(void *cookie,const char *buf ,int n){
 return 0;
 }
 #endif
 //end streaming*/
