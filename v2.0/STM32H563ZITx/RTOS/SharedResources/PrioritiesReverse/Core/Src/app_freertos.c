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

#include "ProtectiveEncapsulation.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

typedef enum RESOURCE_OCCUPATION_FLAGS
{
	RESOURCE_FLAG_IDLE, RESOURCE_FLAG_OCCUPIED,

} OccupationFlags;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define DELAY_TIME_MILLISECONDS	550

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
{ .name = "FlashYellowLedTask", .priority = (osPriority_t) osPriorityNormal1,
		.stack_size = 128 * 4 };
/* Definitions for FlashRedLedTask */
osThreadId_t FlashRedLedTaskHandle;
const osThreadAttr_t FlashRedLedTask_attributes =
{ .name = "FlashRedLedTask", .priority = (osPriority_t) osPriorityNormal2,
		.stack_size = 128 * 4 };

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

extern void AccessProtectiveData(TaskCategories task);

/* USER CODE END FunctionPrototypes */

void StartFlashGreenLedTask(void *argument);
void StartFlashYellowLedTask(void *argument);
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

	/* creation of FlashYellowLedTask */
	FlashYellowLedTaskHandle = osThreadNew(StartFlashYellowLedTask, NULL,
			&FlashYellowLedTask_attributes);

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
	for (;;)
	{
		AccessProtectiveData(TASK_FLASH_GREEN);

		vTaskSuspend(NULL);
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

	uint8_t i;
	uint32_t j;

	for (;;)
	{
		HAL_GPIO_WritePin(YELLOW_LED_GPIO_Port, YELLOW_LED_Pin,
							GPIO_PIN_SET);

		for (j = 0; j < ITERATIONS; j++)
			;

		HAL_GPIO_WritePin(YELLOW_LED_GPIO_Port, YELLOW_LED_Pin,
				GPIO_PIN_RESET);

		for (j = 0; j < ITERATIONS; j++)
			;

		vTaskSuspend(NULL);
	}
	/* USER CODE END FlashYellowLedTask */
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
		AccessProtectiveData(TASK_FLASH_RED);

		vTaskSuspend(NULL);
	}
	/* USER CODE END FlashRedLedTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
