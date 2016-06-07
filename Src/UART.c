/*
 * UART.c
 *
 *  Created on: Jun 6, 2016
 *      Author: work
 */

#include <UART.h>

//setup
void UARTSetup(UART_STRUCT* uartS,UART_HandleTypeDef* uartH,volatile RingBuffer_t* rbTX,volatile RingBuffer_t* rbRX){
	uartS->uartHandler = uartH;
	uartS->rxBuffer = rbTX;
	uartS->txBuffer = rbTX;
}
//end setup

//byte and buffer IO
int UARTWriteByte(UART_STRUCT* uartS,uint8_t* buff){
	if (HAL_UART_Transmit_IT(uartS->uartHandler,buff,1)== HAL_BUSY){
		//todo return error based on the ring buffer error returns
		RingBufferWrite(uartS->txBuffer,buff,1);
		return -1;
	}
	return 0;
}
int UARTWriteBuffer(UART_STRUCT* uartS,uint8_t* buff,int n){
	if (HAL_UART_Transmit_IT(uartS->uartHandler,buff,n)== HAL_BUSY){
		RingBufferWrite(uartS->txBuffer,buff,n);
		return -1;
	}
	return 0;
}
int UARTGetByte(UART_STRUCT* uartS,uint8_t* buff){
	if (uartS->rxBuffer->available == 0){
		return -1;
	}
	RingBufferRead(uartS->rxBuffer,buff,1);
	return 0;
}
int UARTGetBuffer(UART_STRUCT* uartS,uint8_t* buff,int n){
	if (uartS->rxBuffer->available == 0 || uartS->rxBuffer->available < n){
		return -1;
	}

	RingBufferRead(uartS->rxBuffer,buff,n);
	return 0;
}
//end byte and buffer IO
//ISR callbacks
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	switch((uint32_t)huart->Instance){
#ifdef USART1
		case (uint32_t)USART1:
			break;
#endif
#ifdef USART2
		case (uint32_t)USART2:
			break;
#endif
#ifdef USART3
		case (uint32_t)USART3:
			break;
#endif
#ifdef UART4
		case (uint32_t)UART4:
			break;
#endif
#ifdef UART5
		case (uint32_t)UART5:
			break;
#endif
#ifdef USART6
		case (uint32_t)USART6:
			break;
#endif
#ifdef UART7
		case (uint32_t)UART7:
			break;
#endif
#ifdef USART8
		case (uint32_t)USART8:
			break;
#endif
		}
	//todo check handler to use multiple uarts
	//todo handler for buffer or stream
	HAL_GPIO_TogglePin(LD6_GPIO_Port, LD6_Pin);
	__HAL_UART_FLUSH_DRREGISTER(&huart);
	//todo status handling for ring buffer
	RingBufferWrite(&Uart2RXBuffer,ISRBuffer,1);
	if (HAL_UART_Receive_IT(&huart2, (uint8_t *) ISRBuffer, 1) != HAL_OK) {
		printf("uart was not enabled\n");
	}
}
/*void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	HAL_GPIO_TogglePin(LD5_GPIO_Port, LD5_Pin);
	if (Uart2TXBuffer.available > 0){
		HAL_UART_Transmit_IT(&huart2,Uart2RXBuffer.buffer,Uart2TXBuffer.available);
		Uart2TXBuffer.available = 0;
	}
}
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart) {

	printf("uart error: %lu\n", huart->ErrorCode);
}
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
