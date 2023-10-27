/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : app_freertos.c
 * Description        : Code for freertos applications
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os2.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include <stdio.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for FlashGreenLedTask */
osThreadId_t FlashGreenLedTaskHandle;
const osThreadAttr_t FlashGreenLedTask_attributes =
{ .name = "FlashGreenLedTask", .priority = (osPriority_t) osPriorityNormal,
		.stack_size = 128 * 4 };
/* Definitions for FlashYellowLedTask */
osThreadId_t FlashYellowLedTaskHandle;
const osThreadAttr_t FlashYellowLedTask_attributes =
{ .name = "FlashYellowLedTask", .priority = (osPriority_t) osPriorityNormal,
		.stack_size = 128 * 4 };
/* Definitions for DeferableInterruptServices */
osThreadId_t DeferableInterruptServicesHandle;
const osThreadAttr_t DeferableInterruptServices_attributes =
{ .name = "DeferableInterruptServices",
		.priority = (osPriority_t) osPriorityLow, .stack_size = 128 * 4 };
/* Definitions for MessagesQueue */
osMessageQueueId_t MessagesQueueHandle;
const osMessageQueueAttr_t MessagesQueue_attributes =
{ .name = "MessagesQueue" };
/* Definitions for ControlsSemaphore */
osSemaphoreId_t ControlsSemaphoreHandle;
const osSemaphoreAttr_t ControlsSemaphore_attributes =
{ .name = "ControlsSemaphore" };

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartFlashGreenLedTask(void *argument);
void StartFlashYellowLedTask(void *argument);
void StartDeferableInterruptServices(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
 * @brief  FreeRTOS initialization
 * @param  None
 * @retval None
 */
void MX_FREERTOS_Init(void)
{
	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* USER CODE BEGIN RTOS_MUTEX */
	/* add mutexes, ... */
	/* USER CODE END RTOS_MUTEX */
	/* creation of ControlsSemaphore */
	ControlsSemaphoreHandle = osSemaphoreNew(1, 1,
			&ControlsSemaphore_attributes);

	/* USER CODE BEGIN RTOS_SEMAPHORES */
	/* add semaphores, ... */
	osSemaphoreAcquire(ControlsSemaphoreHandle, osWaitForever);
	/* USER CODE END RTOS_SEMAPHORES */

	/* USER CODE BEGIN RTOS_TIMERS */
	/* start timers, add new ones, ... */
	/* USER CODE END RTOS_TIMERS */
	/* creation of MessagesQueue */
	MessagesQueueHandle = osMessageQueueNew(1, sizeof(uint16_t),
			&MessagesQueue_attributes);

	/* USER CODE BEGIN RTOS_QUEUES */
	/* add queues, ... */
	/* USER CODE END RTOS_QUEUES */
	/* creation of FlashGreenLedTask */
	FlashGreenLedTaskHandle = osThreadNew(StartFlashGreenLedTask, NULL,
			&FlashGreenLedTask_attributes);

	/* creation of FlashYellowLedTask */
	FlashYellowLedTaskHandle = osThreadNew(StartFlashYellowLedTask, NULL,
			&FlashYellowLedTask_attributes);

	/* creation of DeferableInterruptServices */
	DeferableInterruptServicesHandle = osThreadNew(
			StartDeferableInterruptServices, NULL,
			&DeferableInterruptServices_attributes);

	/* USER CODE BEGIN RTOS_THREADS */
	/* add threads, ... */
	/* USER CODE END RTOS_THREADS */

	/* USER CODE BEGIN RTOS_EVENTS */
	/* add events, ... */
	/* USER CODE END RTOS_EVENTS */

}
/* USER CODE BEGIN Header_StartFlashGreenLedTask */
/**
 * @brief Function implementing the FlashGreenLedTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartFlashGreenLedTask */
void StartFlashGreenLedTask(void *argument)
{
	/* USER CODE BEGIN FlashGreenLedTask */
	/* Infinite loop */
	for (;;)
	{
		for (uint8_t i = 0; i < 8; i++)
		{
			HAL_GPIO_TogglePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin);

			osDelay(500);
		}
	}
	/* USER CODE END FlashGreenLedTask */
}

/* USER CODE BEGIN Header_StartFlashYellowLedTask */
/**
 * @brief Function implementing the FlashYellowLedTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartFlashYellowLedTask */
void StartFlashYellowLedTask(void *argument)
{
	/* USER CODE BEGIN FlashYellowLedTask */
	/* Infinite loop */
	for (;;)
	{
		for (uint8_t i = 0; i < 4; i++)
		{
			HAL_GPIO_TogglePin(YELLOW_LED_GPIO_Port, YELLOW_LED_Pin);

			osDelay(500);
		}
	}
	/* USER CODE END FlashYellowLedTask */
}

/* USER CODE BEGIN Header_StartDeferableInterruptServices */
/**
 * @brief Function implementing the DeferableInterruptServices thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartDeferableInterruptServices */
void StartDeferableInterruptServices(void *argument)
{
	/* USER CODE BEGIN DeferableInterruptServices */
	/* Infinite loop */

	for (;;)
	{
		osSemaphoreAcquire(ControlsSemaphoreHandle, osWaitForever);

		HAL_GPIO_WritePin(RED_LED_GPIO_Port, RED_LED_Pin, GPIO_PIN_SET);

		osDelay(1000);

		HAL_GPIO_WritePin(RED_LED_GPIO_Port, RED_LED_Pin, GPIO_PIN_RESET);

		for (uint8_t i = 0; i < 10; i ++)
		{
			//HAL_GPIO_TogglePin(BLUE_LED_GPIO_Port, BLUE_LED_Pin);
			printf("Flash Blue LED %d times.\n", i + 1);

			osDelay(500);
		}
	}
	/* USER CODE END DeferableInterruptServices */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

void HAL_GPIO_EXTI_Rising_Callback(uint16_t GPIO_Pin)
{
	osSemaphoreRelease(ControlsSemaphoreHandle);
}


int _write(int file, char *ptr, int length)
{
	for (int i = 0; i < length; i++)
		ITM_SendChar(*ptr++);

	return length;
}

/* USER CODE END Application */

