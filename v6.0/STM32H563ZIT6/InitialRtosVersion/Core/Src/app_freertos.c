/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : app_freertos.c
 * Description        : Code for freertos applications
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
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
/* Definitions for FlashGreenLEDTask */
osThreadId_t FlashGreenLEDTaskHandle;
const osThreadAttr_t FlashGreenLEDTask_attributes = {
  .name = "FlashGreenLEDTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};
/* Definitions for FlashYellowLEDTask */
osThreadId_t FlashYellowLEDTaskHandle;
const osThreadAttr_t FlashYellowLEDTask_attributes = {
  .name = "FlashYellowLEDTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};
/* Definitions for FlashRedLEDTask */
osThreadId_t FlashRedLEDTaskHandle;
const osThreadAttr_t FlashRedLEDTask_attributes = {
  .name = "FlashRedLEDTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartFlashGreenLEDTask(void *argument);
void StartFlashYellowLEDTask(void *argument);
void StartFlashRedLEDTask(void *argument);

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
  /* creation of FlashGreenLEDTask */
  FlashGreenLEDTaskHandle = osThreadNew(StartFlashGreenLEDTask, NULL, &FlashGreenLEDTask_attributes);

  /* creation of FlashYellowLEDTask */
  FlashYellowLEDTaskHandle = osThreadNew(StartFlashYellowLEDTask, NULL, &FlashYellowLEDTask_attributes);

  /* creation of FlashRedLEDTask */
  FlashRedLEDTaskHandle = osThreadNew(StartFlashRedLEDTask, NULL, &FlashRedLEDTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
	/* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
	/* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}
/* USER CODE BEGIN Header_StartFlashGreenLEDTask */
/**
 * @brief Function implementing the FlashGreenLEDTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartFlashGreenLEDTask */
void StartFlashGreenLEDTask(void *argument)
{
  /* USER CODE BEGIN FlashGreenLEDTask */
	/* Infinite loop */
	for (;;)
	{
		HAL_GPIO_TogglePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin);

		osDelay(500);
	}
  /* USER CODE END FlashGreenLEDTask */
}

/* USER CODE BEGIN Header_StartFlashYellowLEDTask */
/**
 * @brief Function implementing the FlashYellowLEDTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartFlashYellowLEDTask */
void StartFlashYellowLEDTask(void *argument)
{
  /* USER CODE BEGIN FlashYellowLEDTask */
	/* Infinite loop */
	for (;;)
	{
		HAL_GPIO_TogglePin(YELLOW_LED_GPIO_Port, YELLOW_LED_Pin);

		osDelay(500);
	}
  /* USER CODE END FlashYellowLEDTask */
}

/* USER CODE BEGIN Header_StartFlashRedLEDTask */
/**
 * @brief Function implementing the FlashRedLEDTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartFlashRedLEDTask */
void StartFlashRedLEDTask(void *argument)
{
  /* USER CODE BEGIN FlashRedLEDTask */
	/* Infinite loop */
	for (;;)
	{
		HAL_GPIO_TogglePin(RED_LED_GPIO_Port, RED_LED_Pin);

		osDelay(500);
	}
  /* USER CODE END FlashRedLEDTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

