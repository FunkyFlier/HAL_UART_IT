/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  *
  * COPYRIGHT(c) 2016 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"
#include "stm32f4xx_it.h"

/* USER CODE BEGIN 0 */
extern uint32_t msCount,uartTimeOutDebugCounter,outByteCount;
#include "UART.h"
/*#include "RingBuffer.h"
extern uint8_t ISRBuffer[1];
extern RingBuffer_t Uart2RXBuffer;
extern RingBuffer_t Uart2TXBuffer;*/
/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern UART_HandleTypeDef huart2;

/******************************************************************************/
/*            Cortex-M4 Processor Interruption and Exception Handlers         */ 
/******************************************************************************/

/**
* @brief This function handles System tick timer.
*/
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  HAL_SYSTICK_IRQHandler();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

/**
* @brief This function handles USART2 global interrupt.
*/
void USART2_IRQHandler(void)
{
  /* USER CODE BEGIN USART2_IRQn 0 */

  /* USER CODE END USART2_IRQn 0 */
  HAL_UART_IRQHandler(&huart2);
  /* USER CODE BEGIN USART2_IRQn 1 */


/*	if (UART_2_STRUCT.fixTxISR == true){

		if (HAL_UART_Receive_IT(UART_2_STRUCT.uartHandler, UART_2_STRUCT.ISRBuf, 1) != HAL_OK) {
	#ifdef DEBUG_TO_CONSOLE
			HAL_GPIO_WritePin(LD5_GPIO_Port, LD5_Pin, 1);
			failedITStartCount++;
			//printf("failed CB %i %i %i\n",(int)HAL_UART_GetState(UART_2_STRUCT.uartHandler),(int)UART_2_STRUCT.uartHandler->gState,UART_2_STRUCT.uartHandler->RxState);
	#endif
		}else{
			UART_2_STRUCT.fixTxISR = false;
		}
	}*/

  if (UART_2_STRUCT.transmit == true) {
	  UART_2_STRUCT.transmit = false;

	  UART_2_STRUCT.txBuffer->locked = true;
  		uartTimeOutDebugCounter = 0;
  		if (HAL_UART_Transmit_IT(UART_2_STRUCT.uartHandler, UART_2_STRUCT.txBuffer->buffer,UART_2_STRUCT.txBuffer->available) == HAL_BUSY){
  			UART_2_STRUCT.txBuffer->locked = false;
  			//return -1;
  		}
  		outByteCount += UART_2_STRUCT.txBuffer->available;
  		UART_2_STRUCT.txBuffer->available = 0;
  		UART_2_STRUCT.txBuffer->readIdx = 0;
  		UART_2_STRUCT.txBuffer->writeIdx = 0;
  		UART_2_STRUCT.txBuffer->locked = false;
  	}
  /* USER CODE END USART2_IRQn 1 */
}

/* USER CODE BEGIN 1 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if (GPIO_Pin == B1_Pin) {
		HAL_GPIO_TogglePin(LD4_GPIO_Port, LD4_Pin);
	}
}
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	HAL_GPIO_TogglePin(LD5_GPIO_Port, LD5_Pin);

}
void HAL_SYSTICK_Callback(void)
{
	msCount++;
	uartTimeOutDebugCounter++;
}


/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
