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

#include "CriticalObject.h"

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
/* Definitions for FlashRateUpdateTask */
osThreadId_t FlashRateUpdateTaskHandle;
const osThreadAttr_t FlashRateUpdateTask_attributes =
{ .name = "FlashRateUpdateTask", .priority = (osPriority_t) osPriorityNormal,
		.stack_size = 128 * 4 };
/* Definitions for FlashRedLedTask */
osThreadId_t FlashRedLedTaskHandle;
const osThreadAttr_t FlashRedLedTask_attributes =
{ .name = "FlashRedLedTask", .priority = (osPriority_t) osPriorityNormal,
		.stack_size = 128 * 4 };
/* Definitions for BinarySemaphore */
osSemaphoreId_t BinarySemaphoreHandle;
const osSemaphoreAttr_t BinarySemaphore_attributes =
{ .name = "BinarySemaphore" };

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartFlashGreenLedTask(void *argument);
void StartFlashRateUpdateTask(void *argument);
void StartFlashRedLedTask(void *argument);

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
	/* creation of BinarySemaphore */
	BinarySemaphoreHandle = osSemaphoreNew(1, 1, &BinarySemaphore_attributes);

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
	FlashGreenLedTaskHandle = osThreadNew(StartFlashGreenLedTask, NULL,
			&FlashGreenLedTask_attributes);

	/* creation of FlashRateUpdateTask */
	FlashRateUpdateTaskHandle = osThreadNew(StartFlashRateUpdateTask, NULL,
			&FlashRateUpdateTask_attributes);

	/* creation of FlashRedLedTask */
	FlashRedLedTaskHandle = osThreadNew(StartFlashRedLedTask, NULL,
			&FlashRedLedTask_attributes);

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
	uint8_t greenLedFlashingRate = GetGreenLedFlashingRate();

	for (;;)
	{
		greenLedFlashingRate = GetGreenLedFlashingRate();

		HAL_GPIO_TogglePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin);

		osDelay(1000 / greenLedFlashingRate);
	}
	/* USER CODE END FlashGreenLedTask */
}

/* USER CODE BEGIN Header_StartFlashRateUpdateTask */
/**
 * @brief Function implementing the FlashRateUpdateTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartFlashRateUpdateTask */
void StartFlashRateUpdateTask(void *argument)
{
	/* USER CODE BEGIN FlashRateUpdateTask */
	/* Infinite loop */
	for (;;)
	{
		osDelay(8000);

		SetGreenLedFlashingRate(1);
		SetRedLedFlashingRate(10);

		osDelay(8000);

		SetGreenLedFlashingRate(10);
		SetRedLedFlashingRate(1);
	}
	/* USER CODE END FlashRateUpdateTask */
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
	uint8_t redLedFlashingRate = GetRedLedFlashingRate();

	for (;;)
	{
		redLedFlashingRate = GetRedLedFlashingRate();

		HAL_GPIO_TogglePin(RED_LED_GPIO_Port, RED_LED_Pin);

		osDelay(1000 / redLedFlashingRate);
	}
	/* USER CODE END FlashRedLedTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

