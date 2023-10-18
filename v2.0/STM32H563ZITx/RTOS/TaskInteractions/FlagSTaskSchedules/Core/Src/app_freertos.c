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

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

typedef enum TASK_COLLABORATIVE_FLAGS
{
	TASK_FLAG_NOT_SET,
	TASK_FLAG_SET,
	TASK_FLAG_RESET,

} TaskCollaborativeFlags;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

static TaskCollaborativeFlags TaskFlag1;
static TaskCollaborativeFlags TaskFlag2;

/* USER CODE END Variables */
/* Definitions for FlashGreenLedTask */
osThreadId_t FlashGreenLedTaskHandle;
const osThreadAttr_t FlashGreenLedTask_attributes = {
  .name = "FlashGreenLedTask",
  .priority = (osPriority_t) osPriorityAboveNormal,
  .stack_size = 128 * 4
};
/* Definitions for FlashRedLedTask */
osThreadId_t FlashRedLedTaskHandle;
const osThreadAttr_t FlashRedLedTask_attributes = {
  .name = "FlashRedLedTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};
/* Definitions for FlashYellowLedTask */
osThreadId_t FlashYellowLedTaskHandle;
const osThreadAttr_t FlashYellowLedTask_attributes = {
  .name = "FlashYellowLedTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartFlashGreenLedTask(void *argument);
void StartFlashRedLedTask(void *argument);
void StartFlashYellowLedTask(void *argument);

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

  /* creation of FlashYellowLedTask */
  FlashYellowLedTaskHandle = osThreadNew(StartFlashYellowLedTask, NULL, &FlashYellowLedTask_attributes);

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

	TaskFlag1 = TASK_FLAG_NOT_SET;

	for (uint8_t i = 0; i < 100; i++)
	{
		HAL_GPIO_TogglePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin);

		osDelay(100);
	}

	TaskFlag1 = TASK_FLAG_SET;

	for (uint8_t i = 0; i < 10; i++)
	{
		HAL_GPIO_TogglePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin);

		osDelay(1000);
	}

	TaskFlag1 = TASK_FLAG_RESET;

	for (uint8_t i = 0; i < 100; i++)
	{
		HAL_GPIO_TogglePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin);

		osDelay(100);
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

	TaskFlag2 = TASK_FLAG_NOT_SET;

	/* Infinite loop */
	for (uint8_t i = 0; i < 15; i ++)
	{
		HAL_GPIO_TogglePin(RED_LED_GPIO_Port, RED_LED_Pin);

		osDelay(100);
	}

	TaskFlag2 = TASK_FLAG_SET;

	for (uint8_t i = 0; i < 10; i ++)
	{
		HAL_GPIO_TogglePin(RED_LED_GPIO_Port, RED_LED_Pin);

		osDelay(1000);
	}

	TaskFlag2 = TASK_FLAG_RESET;

	for (uint8_t i = 0; i < 50; i ++)
	{
		HAL_GPIO_TogglePin(RED_LED_GPIO_Port, RED_LED_Pin);

		osDelay(100);
	}

  /* USER CODE END FlashRedLedTask */
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
		HAL_GPIO_TogglePin(YELLOW_LED_GPIO_Port, YELLOW_LED_Pin);

		if (TaskFlag1 == TASK_FLAG_SET &&
				TaskFlag2 == TASK_FLAG_SET)
			osDelay(1000);
		else
			osDelay(100);
	}
  /* USER CODE END FlashYellowLedTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

