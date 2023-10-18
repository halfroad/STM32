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

typedef enum ResourceOccupationFlags
{
	RESOURCE_FLAG_IDLE,
	RESOURCE_FLAG_OCCUPIED,

} OccupationFlags;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

OccupationFlags occupationFlag = RESOURCE_FLAG_IDLE;

/* USER CODE END Variables */
/* Definitions for FlashGreenLedTask */
osThreadId_t FlashGreenLedTaskHandle;
const osThreadAttr_t FlashGreenLedTask_attributes = {
  .name = "FlashGreenLedTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};
/* Definitions for FlashRedLedTask */
osThreadId_t FlashRedLedTaskHandle;
const osThreadAttr_t FlashRedLedTask_attributes = {
  .name = "FlashRedLedTask",
  .priority = (osPriority_t) osPriorityAboveNormal,
  .stack_size = 128 * 4
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

void access_shared_object();

/* USER CODE END FunctionPrototypes */

void StartFlashGreenLedTask(void *argument);
void StartFlashRedLedTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
	/* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
	/* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
	/* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
	/* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
  /* creation of FlashGreenLedTask */
  FlashGreenLedTaskHandle = osThreadNew(StartFlashGreenLedTask, NULL, &FlashGreenLedTask_attributes);

  /* creation of FlashRedLedTask */
  FlashRedLedTaskHandle = osThreadNew(StartFlashRedLedTask, NULL, &FlashRedLedTask_attributes);

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
		TickType_t ticks = xTaskGetTickCount();

		printf("%d at %s now ticks = %ld\n",__LINE__, __func__, (uint32_t) ticks);

		HAL_GPIO_WritePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin, GPIO_PIN_SET);

		access_shared_object();

		ticks = xTaskGetTickCount();

		printf("%d at %s now ticks = %ld\n",__LINE__, __func__, (uint32_t) ticks);

		HAL_GPIO_WritePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin, GPIO_PIN_RESET);

		osDelay(500);

		ticks = xTaskGetTickCount();

		printf("%d at %s now ticks = %ld\n\n",__LINE__, __func__, (uint32_t) ticks);

	}
  /* USER CODE END FlashGreenLedTask */
}

/* USER CODE BEGIN Header_StartFlashRedLedTask */
/**
 * @brief Function implementing the FlashRedLedTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartFlashRedLedTask */
void StartFlashRedLedTask(void *argument)
{
  /* USER CODE BEGIN FlashRedLedTask */
	/* Infinite loop */
	for (;;)
	{
		TickType_t ticks = xTaskGetTickCount();

		printf("%d at %s now ticks = %ld\n",__LINE__, __func__, (uint32_t) ticks);

		HAL_GPIO_WritePin(RED_LED_GPIO_Port, RED_LED_Pin, GPIO_PIN_SET);

		access_shared_object();

		ticks = xTaskGetTickCount();

		printf("%d at %s now ticks = %ld\n",__LINE__, __func__, (uint32_t) ticks);

		HAL_GPIO_WritePin(RED_LED_GPIO_Port, RED_LED_Pin, GPIO_PIN_RESET);

		osDelay(100);

		ticks = xTaskGetTickCount();

		printf("%d at %s now ticks = %ld\n\n",__LINE__, __func__, (uint32_t) ticks);
	}
  /* USER CODE END FlashRedLedTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

void access_shared_object()
{
	TickType_t ticks = xTaskGetTickCount();

	printf("%d at %s now ticks = %ld\n",__LINE__, __func__, (uint32_t) ticks);

	/* No occupied. */
	if (occupationFlag == RESOURCE_FLAG_IDLE)
		occupationFlag = RESOURCE_FLAG_OCCUPIED;
	else	/* Occupied. */
	{
		HAL_GPIO_WritePin(YELLOW_LED_GPIO_Port, YELLOW_LED_Pin, GPIO_PIN_SET);

		osDelay(100);

		ticks = xTaskGetTickCount();

		printf("%d at %s now ticks = %ld\n\n",__LINE__, __func__, (uint32_t) ticks);

		HAL_GPIO_WritePin(YELLOW_LED_GPIO_Port, YELLOW_LED_Pin, GPIO_PIN_RESET);
	}

	/* Simulate long duration for the resource read/write operation. */
	osDelay(500);

	/* Release the occupation of Write/Read. */
	occupationFlag = RESOURCE_FLAG_IDLE;

	ticks = xTaskGetTickCount();

	printf("%d at %s now ticks = %ld\n\n",__LINE__, __func__, (uint32_t) ticks);
}

int _write(int *file, char *ptr, int length)
{
	for (int i = 0; i < length; i ++)
		ITM_SendChar(*ptr ++);

	return length;
}
/* USER CODE END Application */

