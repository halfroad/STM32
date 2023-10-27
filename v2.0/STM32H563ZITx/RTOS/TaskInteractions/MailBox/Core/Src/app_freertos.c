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

typedef enum
{
	MESSAGE_QUEUE_SYNC_1, MESSAGE_QUEUE_SYNC_2,

} MessagesQueueSync;

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
/* Definitions for DirectiveTask */
osThreadId_t DirectiveTaskHandle;
const osThreadAttr_t DirectiveTask_attributes =
{ .name = "DirectiveTask", .priority = (osPriority_t) osPriorityNormal,
		.stack_size = 128 * 4 };
/* Definitions for FlashTask */
osThreadId_t FlashTaskHandle;
const osThreadAttr_t FlashTask_attributes =
{ .name = "FlashTask", .priority = (osPriority_t) osPriorityNormal,
		.stack_size = 128 * 4 };
/* Definitions for MailBoxMutex */
osMutexId_t MailBoxMutexHandle;
const osMutexAttr_t MailBoxMutex_attributes =
{ .name = "MailBoxMutex" };
/* Definitions for MessagesQueue */
osMessageQueueId_t MessagesQueueHandle;
const osMessageQueueAttr_t MessagesQueue_attributes =
{ .name = "MessagesQueue" };
/* Definitions for MailBoxBinarySemaphore1 */
osSemaphoreId_t MailBoxBinarySemaphore1Handle;
const osSemaphoreAttr_t MailBoxBinarySemaphore1_attributes =
{ .name = "MailBoxBinarySemaphore1" };
/* Definitions for MailBoxBinarySemaphore2 */
osSemaphoreId_t MailBoxBinarySemaphore2Handle;
const osSemaphoreAttr_t MailBoxBinarySemaphore2_attributes =
{ .name = "MailBoxBinarySemaphore2" };

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDirectiveTask(void *argument);
void StartFlashTask(void *argument);

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
	/* creation of MailBoxMutex */
	MailBoxMutexHandle = osMutexNew(&MailBoxMutex_attributes);

	/* USER CODE BEGIN RTOS_MUTEX */
	/* add mutexes, ... */
	/* USER CODE END RTOS_MUTEX */
	/* creation of MailBoxBinarySemaphore1 */
	MailBoxBinarySemaphore1Handle = osSemaphoreNew(1, 1,
			&MailBoxBinarySemaphore1_attributes);

	/* creation of MailBoxBinarySemaphore2 */
	MailBoxBinarySemaphore2Handle = osSemaphoreNew(1, 1,
			&MailBoxBinarySemaphore2_attributes);

	/* USER CODE BEGIN RTOS_SEMAPHORES */
	/* add semaphores, ... */
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
	/* creation of DirectiveTask */
	DirectiveTaskHandle = osThreadNew(StartDirectiveTask, NULL,
			&DirectiveTask_attributes);

	/* creation of FlashTask */
	FlashTaskHandle = osThreadNew(StartFlashTask, NULL, &FlashTask_attributes);

	/* USER CODE BEGIN RTOS_THREADS */
	/* add threads, ... */
	/* USER CODE END RTOS_THREADS */

	/* USER CODE BEGIN RTOS_EVENTS */
	/* add events, ... */
	/* USER CODE END RTOS_EVENTS */

}
/* USER CODE BEGIN Header_StartDirectiveTask */
/**
 * @brief Function implementing the DirectiveTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartDirectiveTask */
void StartDirectiveTask(void *argument)
{
	/* USER CODE BEGIN DirectiveTask */
	/* Infinite loop */

	static MessagesQueueSync sync;

	for (;;)
	{
		for (uint8_t i = 0; i < 10; i++)
		{
			HAL_GPIO_TogglePin(RED_LED_GPIO_Port, RED_LED_Pin);

			osDelay(1000);
		}

		sync = MESSAGE_QUEUE_SYNC_1;

		osMessageQueuePut(MessagesQueueHandle, &sync, 0UL, 0UL);

		for (uint8_t i = 0; i < 50; i++)
		{
			HAL_GPIO_TogglePin(RED_LED_GPIO_Port, RED_LED_Pin);

			osDelay(100);
		}

		sync = MESSAGE_QUEUE_SYNC_2;

		osMessageQueuePut(MessagesQueueHandle, &sync, 0UL, 0UL);
	}
	/* USER CODE END DirectiveTask */
}

/* USER CODE BEGIN Header_StartFlashTask */
/**
 * @brief Function implementing the FlashTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartFlashTask */
void StartFlashTask(void *argument)
{
	/* USER CODE BEGIN FlashTask */
	/* Infinite loop */

	static MessagesQueueSync sync;
	static osStatus_t status;

	for (;;)
	{
		for (uint8_t i = 0; i < 50; i++)
		{
			HAL_GPIO_TogglePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin);

			osDelay(100);
		}

		status = osMessageQueueGet(MessagesQueueHandle, &sync, NULL, 0UL);

		if (osOK == status)
		{
			if (MESSAGE_QUEUE_SYNC_1 == sync)
			{
				HAL_GPIO_WritePin(YELLOW_LED_GPIO_Port, YELLOW_LED_Pin,
						GPIO_PIN_SET);
				//HAL_GPIO_WritePin(BLUE_LED_GPIO_Port, BLUE_LED_Pin, GPIO_PIN_RESET);
				printf("Turn Blue LED off.\n");
			}
			else
			{
				//HAL_GPIO_WritePin(BLUE_LED_GPIO_Port, BLUE_LED_Pin, GPIO_PIN_SET);
				printf("Turn Blue LED on.\n");
				HAL_GPIO_WritePin(YELLOW_LED_GPIO_Port, YELLOW_LED_Pin,
						GPIO_PIN_RESET);
			}
		}

		for (uint8_t i = 0; i < 10; i++)
		{
			HAL_GPIO_TogglePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin);

			osDelay(1000);
		}

		status = osMessageQueueGet(MessagesQueueHandle, &sync, NULL, 0UL);

		if (osOK == status)
		{
			if (MESSAGE_QUEUE_SYNC_1 == sync)
			{
				HAL_GPIO_WritePin(YELLOW_LED_GPIO_Port, YELLOW_LED_Pin,
						GPIO_PIN_SET);
				//HAL_GPIO_WritePin(BLUE_LED_GPIO_Port, BLUE_LED_Pin, GPIO_PIN_RESET);
				printf("Turn Blue LED off.\n");
			}
			else
			{
				//HAL_GPIO_WritePin(BLUE_LED_GPIO_Port, BLUE_LED_Pin, GPIO_PIN_SET);
				printf("Turn Blue LED on.\n");
				HAL_GPIO_WritePin(YELLOW_LED_GPIO_Port, YELLOW_LED_Pin,
						GPIO_PIN_RESET);
			}
		}

	}
	/* USER CODE END FlashTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

int _write(int file, char *ptr, int length)
{
	for (int i = 0; i < length; i++)
		ITM_SendChar(*ptr++);

	return length;
}

/* USER CODE END Application */

