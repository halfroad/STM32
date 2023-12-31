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
/* Definitions for task_1 */
osThreadId_t task_1Handle;
const osThreadAttr_t task_1_attributes = { .name = "task_1", .priority =
		(osPriority_t) osPriorityNormal, .stack_size = 128 * 4 };
/* Definitions for task_2 */
osThreadId_t task_2Handle;
const osThreadAttr_t task_2_attributes = { .name = "task_2", .priority =
		(osPriority_t) osPriorityBelowNormal, .stack_size = 128 * 4 };

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void task_1_entry_function(void *argument);
void task_2_entry_function(void *argument);

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
	/* creation of task_1 */
	task_1Handle = osThreadNew(task_1_entry_function, NULL, &task_1_attributes);

	/* creation of task_2 */
	task_2Handle = osThreadNew(task_2_entry_function, NULL, &task_2_attributes);

	/* USER CODE BEGIN RTOS_THREADS */
	/* add threads, ... */
	/* USER CODE END RTOS_THREADS */

	/* USER CODE BEGIN RTOS_EVENTS */
	/* add events, ... */
	/* USER CODE END RTOS_EVENTS */

}
/* USER CODE BEGIN Header_task_1_entry_function */
/**
 * @brief Function implementing the task_1 thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_task_1_entry_function */
void task_1_entry_function(void *argument)
{
	/* USER CODE BEGIN task_1 */
	/* Infinite loop */
	for (;;)
	{
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
		osDelay(500);
	}
	/* USER CODE END task_1 */
}

/* USER CODE BEGIN Header_task_2_entry_function */
/**
 * @brief Function implementing the task_2 thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_task_2_entry_function */
void task_2_entry_function(void *argument)
{
	/* USER CODE BEGIN task_2 */
	/* Infinite loop */
	for (;;)
	{

		HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_4);
		osDelay(250);
	}
	/* USER CODE END task_2 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

