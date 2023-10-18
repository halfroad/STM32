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

		printf("Priority Normal: Turn the Blue LED ON, ticks = %lu.\n", (uint32_t)ticks);
		printf("Priority Normal: Simulate task execution, Green LED will flash for 4 seconds (20Hz is recommended). Will switch to next possible highest priority task.\n\n");

		osDelay(4000);

		ticks = xTaskGetTickCount();

		printf("Priority Normal: Stop flashing Green LED, ticks = %lu.\n", (uint32_t)ticks);
		printf("Priority Normal: Turn the Blue LED off.\n");
		printf("Priority Normal: Task is halted for 6 seconds. Will switch to next possible highest priority task.\n\n");

		osDelay(6000);
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

		printf("Priority Above Normal: Turn the Orange LED on, ticks = %lu.\n", (uint32_t)ticks);
		printf("Priority Above Normal: Simulate task execution, Red LED will flash 0.5 second (20Hz is recommended). Will switch to next possible highest priority task.\n\n");

		osDelay(500);

		ticks = xTaskGetTickCount();

		printf("Priority Above Normal: Turn the Red LED off, ticks = %lu.\n", (uint32_t)ticks);
		printf("Priority Above Normal: Turn the Orange LED off.\n");
		printf("Priority Above Normal: Task is halted for 1.5 seconds. Will switch to next possible highest priority task.\n\n");

		osDelay(1500);
	}

	/*
	SWV ITM Data Console - ITM Port: 0

	Priority Above Normal: Turn the Orange LED on, ticks = 0.
	Priority Above Normal: Simulate task execution, Red LED will flash 0.5 second (20Hz is recommended). Will switch to next possible highest priority task.

	Priority Normal: Turn the Blue LED ON, ticks = 0.
	Priority Normal: Simulate task execution, Green LED will flash for 4 seconds (20Hz is recommended). Will switch to next possible highest priority task.

	Priority Above Normal: Turn the Red LED off, ticks = 500.
	Priority Above Normal: Turn the Orange LED off.
	Priority Above Normal: Task is halted for 1.5 seconds. Will switch to next possible highest priority task.

	Priority Above Normal: Turn the Orange LED on, ticks = 2000.
	Priority Above Normal: Simulate task execution, Red LED will flash 0.5 second (20Hz is recommended). Will switch to next possible highest priority task.

	Priority Above Normal: Turn the Red LED off, ticks = 2500.
	Priority Above Normal: Turn the Orange LED off.
	Priority Above Normal: Task is halted for 1.5 seconds. Will switch to next possible highest priority task.

	Priority Above Normal: Turn the Orange LED on, ticks = 4000.
	Priority Above Normal: Simulate task execution, Red LED will flash 0.5 second (20Hz is recommended). Will switch to next possible highest priority task.

	Priority Normal: Stop flashing Green LED, ticks = 4001.
	Priority Normal: Turn the Blue LED off.
	Priority Normal: Task is halted for 6 seconds. Will switch to next possible highest priority task.

	Priority Above Normal: Turn the Red LED off, ticks = 4500.
	Priority Above Normal: Turn the Orange LED off.
	Priority Above Normal: Task is halted for 1.5 seconds. Will switch to next possible highest priority task.

	Priority Above Normal: Turn the Orange LED on, ticks = 6000.
	Priority Above Normal: Simulate task execution, Red LED will flash 0.5 second (20Hz is recommended). Will switch to next possible highest priority task.

	Priority Above Normal: Turn the Red LED off, ticks = 6500.
	Priority Above Normal: Turn the Orange LED off.
	Priority Above Normal: Task is halted for 1.5 seconds. Will switch to next possible highest priority task.

	Priority Above Normal: Turn the Orange LED on, ticks = 8000.
	Priority Above Normal: Simulate task execution, Red LED will flash 0.5 second (20Hz is recommended). Will switch to next possible highest priority task.

	Priority Above Normal: Turn the Red LED off, ticks = 8500.
	Priority Above Normal: Turn the Orange LED off.
	Priority Above Normal: Task is halted for 1.5 seconds. Will switch to next possible highest priority task.

	Priority Above Normal: Turn the Orange LED on, ticks = 10000.
	Priority Above Normal: Simulate task execution, Red LED will flash 0.5 second (20Hz is recommended). Will switch to next possible highest priority task.

	Priority Normal: Turn the Blue LED ON, ticks = 10001.
	Priority Normal: Simulate task execution, Green LED will flash for 4 seconds (20Hz is recommended). Will switch to next possible highest priority task.

	Priority Above Normal: Turn the Red LED off, ticks = 10500.
	Priority Above Normal: Turn the Orange LED off.
	Priority Above Normal: Task is halted for 1.5 seconds. Will switch to next possible highest priority task.

	Priority Above Normal: Turn the Orange LED on, ticks = 12000.
	Priority Above Normal: Simulate task execution, Red LED will flash 0.5 second (20Hz is recommended). Will switch to next possible highest priority task.

	Priority Above Normal: Turn the Red LED off, ticks = 12500.
	Priority Above Normal: Turn the Orange LED off.
	Priority Above Normal: Task is halted for 1.5 seconds. Will switch to next possible highest priority task.

	Priority Above Normal: Turn the Orange LED on, ticks = 14000.
	Priority Above Normal: Simulate task execution, Red LED will flash 0.5 second (20Hz is recommended). Will switch to next possible highest priority task.

	Priority Normal: Stop flashing Green LED, ticks = 14001.
	Priority Normal: Turn the Blue LED off.
	Priority Normal: Task is halted for 6 seconds. Will switch to next possible highest priority task.

	Priority Above Normal: Turn the Red LED off, ticks = 14500.
	Priority Above Normal: Turn the Orange LED off.
	Priority Above Normal: Task is halted for 1.5 seconds. Will switch to next possible highest priority task.

	Priority Above Normal: Turn the Orange LED on, ticks = 16000.
	Priority Above Normal: Simulate task execution, Red LED will flash 0.5 second (20Hz is recommended). Will switch to next possible highest priority task.

	Priority Above Normal: Turn the Red LED off, ticks = 16500.
	Priority Above Normal: Turn the Orange LED off.
	Priority Above Normal: Task is halted for 1.5 seconds. Will switch to next possible highest priority task.

	Priority Above Normal: Turn the Orange LED on, ticks = 18000.
	Priority Above Normal: Simulate task execution, Red LED will flash 0.5 second (20Hz is recommended). Will switch to next possible highest priority task.

	Priority Above Normal: Turn the Red LED off, ticks = 18500.
	Priority Above Normal: Turn the Orange LED off.
	Priority Above Normal: Task is halted for 1.5 seconds. Will switch to next possible highest priority task.

	Priority Above Normal: Turn the Orange LED on, ticks = 20000.
	Priority Above Normal: Simulate task execution, Red LED will flash 0.5 second (20Hz is recommended). Will switch to next possible highest priority task.

	Priority Normal: Turn the Blue LED ON, ticks = 20001.
	Priority Normal: Simulate task execution, Green LED will flash for 4 seconds (20Hz is recommended). Will switch to next possible highest priority task.

	Priority Above Normal: Turn the Red LED off, ticks = 20500.
	Priority Above Normal: Turn the Orange LED off.
	Priority Above Normal: Task is halted for 1.5 seconds. Will switch to next possible highest priority task.

	Priority Above Normal: Turn the Orange LED on, ticks = 22000.
	Priority Above Normal: Simulate task execution, Red LED will flash 0.5 second (20Hz is recommended). Will switch to next possible highest priority task.

	Priority Above Normal: Turn the Red LED off, ticks = 22500.
	Priority Above Normal: Turn the Orange LED off.
	Priority Above Normal: Task is halted for 1.5 seconds. Will switch to next possible highest priority task.

	Priority Above Normal: Turn the Orange LED on, ticks = 24000.
	Priority Above Normal: Simulate task execution, Red LED will flash 0.5 second (20Hz is recommended). Will switch to next possible highest priority task.

	Priority Normal: Stop flashing Green LED, ticks = 24001.
	Priority Normal: Turn the Blue LED off.
	Priority Normal: Task is halted for 6 seconds. Will switch to next possible highest priority task.

	Priority Above Normal: Turn the Red LED off, ticks = 24500.
	Priority Above Normal: Turn the Orange LED off.
	Priority Above Normal: Task is halted for 1.5 seconds. Will switch to next possible highest priority task.

	Priority Above Normal: Turn the Orange LED on, ticks = 26000.
	Priority Above Normal: Simulate task execution, Red LED will flash 0.5 second (20Hz is recommended). Will switch to next possible highest priority task.

	Priority Above Normal: Turn the Red LED off, ticks = 26500.
	Priority Above Normal: Turn the Orange LED off.
	Priority Above Normal: Task is halted for 1.5 seconds. Will switch to next possible highest priority task.

	Priority Above Normal: Turn the Orange LED on, ticks = 28000.
	Priority Above Normal: Simulate task execution, Red LED will flash 0.5 second (20Hz is recommended). Will switch to next possible highest priority task.

	Priority Above Normal: Turn the Red LED off, ticks = 28500.
	Priority Above Normal: Turn the Orange LED off.
	Priority Above Normal: Task is halted for 1.5 seconds. Will switch to next possible highest priority task.

	Priority Above Normal: Turn the Orange LED on, ticks = 30000.
	Priority Above Normal: Simulate task execution, Red LED will flash 0.5 second (20Hz is recommended). Will switch to next possible highest priority task.

	Priority Normal: Turn the Blue LED ON, ticks = 30001.
	Priority Normal: Simulate task execution, Green LED will flash for 4 seconds (20Hz is recommended). Will switch to next possible highest priority task.

	Priority Above Normal: Turn the Red LED off, ticks = 30500.
	Priority Above Normal: Turn the Orange LED off.
	Priority Above Normal: Task is halted for 1.5 seconds. Will switch to next possible highest priority task.

	Priority Above Normal: Turn the Orange LED on, ticks = 32000.
	Priority Above Normal: Simulate task execution, Red LED will flash 0.5 second (20Hz is recommended). Will switch to next possible highest priority task.

	Priority Above Normal: Turn the Red LED off, ticks = 32500.
	Priority Above Normal: Turn the Orange LED off.
	Priority Above Normal: Task is halted for 1.5 seconds. Will switch to next possible highest priority task.

	Priority Above Normal: Turn the Orange LED on, ticks = 34000.
	Priority Above Normal: Simulate task execution, Red LED will flash 0.5 second (20Hz is recommended). Will switch to next possible highest priority task.

	Priority Normal: Stop flashing Green LED, ticks = 34001.
	Priority Normal: Turn the Blue LED off.
	Priority Normal: Task is halted for 6 seconds. Will switch to next possible highest priority task.

	Priority Above Normal: Turn the Red LED off, ticks = 34500.
	Priority Above Normal: Turn the Orange LED off.
	Priority Above Normal: Task is halted for 1.5 seconds. Will switch to next possible highest priority task.

	Priority Above Normal: Turn the Orange LED on, ticks = 36000.
	Priority Above Normal: Simulate task execution, Red LED will flash 0.5 second (20Hz is recommended). Will switch to next possible highest priority task.

	Priority Above Normal: Turn the Red LED off, ticks = 36500.
	Priority Above Normal: Turn the Orange LED off.
	Priority Above Normal: Task is halted for 1.5 seconds. Will switch to next possible highest priority task.

	Priority Above Normal: Turn the Orange LED on, ticks = 38000.
	Priority Above Normal: Simulate task execution, Red LED will flash 0.5 second (20Hz is recommended). Will switch to next possible highest priority task.

	Priority Above Normal: Turn the Red LED off, ticks = 38500.
	Priority Above Normal: Turn the Orange LED off.
	Priority Above Normal: Task is halted for 1.5 seconds. Will switch to next possible highest priority task.

	Priority Above Normal: Turn the Orange LED on, ticks = 40000.
	Priority Above Normal: Simulate task execution, Red LED will flash 0.5 second (20Hz is recommended). Will switch to next possible highest priority task.

	Priority Normal: Turn the Blue LED ON, ticks = 40001.
	Priority Normal: Simulate task execution, Green LED will flash for 4 seconds (20Hz is recommended). Will switch to next possible highest priority task.

	Priority Above Normal: Turn the Red LED off, ticks = 40500.
	Priority Above Normal: Turn the Orange LED off.
	Priority Above Normal: Task is halted for 1.5 seconds. Will switch to next possible highest priority task.

	Priority Above Normal: Turn the Orange LED on, ticks = 42000.
	Priority Above Normal: Simulate task execution, Red LED will flash 0.5 second (20Hz is recommended). Will switch to next possible highest priority task.

	Priority Above Normal: Turn the Red LED off, ticks = 42500.
	Priority Above Normal: Turn the Orange LED off.
	Priority Above Normal: Task is halted for 1.5 seconds. Will switch to next possible highest priority task.

	Priority Above Normal: Turn the Orange LED on, ticks = 44000.
	Priority Above Normal: Simulate task execution, Red LED will flash 0.5 second (20Hz is recommended). Will switch to next possible highest priority task.

	Priority Normal: Stop flashing Green LED, ticks = 44001.
	Priority Normal: Turn the Blue LED off.
	Priority Normal: Task is halted for 6 seconds. Will switch to next possible highest priority task.

	Priority Above Normal: Turn the Red LED off, ticks = 44500.
	Priority Above Normal: Turn the Orange LED off.
	Priority Above Normal: Task is halted for 1.5 seconds. Will switch to next possible highest priority task.

	Priority Above Normal: Turn the Orange LED on, ticks = 46000.
	Priority Above Normal: Simulate task execution, Red LED will flash 0.5 second (20Hz is recommended). Will switch to next possible highest priority task.

	Priority Above Normal: Turn the Red LED off, ticks = 46500.
	Priority Above Normal: Turn the Orange LED off.
	Priority Above Normal: Task is halted for 1.5 seconds. Will switch to next possible highest priority task.

	Priority Above Normal: Turn the Orange LED on, ticks = 48000.
	Priority Above Normal: Simulate task execution, Red LED will flash 0.5 second (20Hz is recommended). Will switch to next possible highest priority task.

	Priority Above Normal: Turn the Red LED off, ticks = 48500.
	Priority Above Normal: Turn the Orange LED off.
	Priority Above Normal: Task is halted for 1.5 seconds. Will switch to next possible highest priority task.

	Priority Above Normal: Turn the Orange LED on, ticks = 50000.
	Priority Above Normal: Simulate task execution, Red LED will flash 0.5 second (20Hz is recommended). Will switch to next possible highest priority task.

	Priority Normal: Turn the Blue LED ON, ticks = 50001.
	Priority Normal: Simulate task execution, Green LED will flash for 4 seconds (20Hz is recommended). Will switch to next possible highest priority task.

	Priority Above Normal: Turn the Red LED off, ticks = 50500.
	Priority Above Normal: Turn the Orange LED off.
	Priority Above Normal: Task is halted for 1.5 seconds. Will switch to next possible highest priority task.

	Priority Above Normal: Turn the Orange LED on, ticks = 52000.
	Priority Above Normal: Simulate task execution, Red LED will flash 0.5 second (20Hz is recommended). Will switch to next possible highest priority task.

	Priority Above Normal: Turn the Red LED off, ticks = 52500.
	Priority Above Normal: Turn the Orange LED off.
	Priority Above Normal: Task is halted for 1.5 seconds. Will switch to next possible highest priority task.

	Priority Above Normal: Turn the Orange LED on, ticks = 54000.
	Priority Above Normal: Simulate task execution, Red LED will flash 0.5 second (20Hz is recommended). Will switch to next possible highest priority task.

	Priority Normal: Stop flashing Green LED, ticks = 54001.
	Priority Normal: Turn the Blue LED off.
	Priority Normal: Task is halted for 6 seconds. Will switch to next possible highest priority task.

	Priority Above Normal: Turn the Red LED off, ticks = 54500.
	Priority Above Normal: Turn the Orange LED off.
	Priority Above Normal: Task is halted for 1.5 seconds. Will switch to next possible highest priority task.

	Priority Above Normal: Turn the Orange LED on, ticks = 56000.
	Priority Above Normal: Simulate task execution, Red LED will flash 0.5 second (20Hz is recommended). Will switch to next possible highest priority task.

	Priority Above Normal: Turn the Red LED off, ticks = 56500.
	Priority Above Normal: Turn the Orange LED off.
	Priority Above Normal: Task is halted for 1.5 seconds. Will switch to next possible highest priority task.

	Priority Above Normal: Turn the Orange LED on, ticks = 58000.
	Priority Above Normal: Simulate task execution, Red LED will flash 0.5 second (20Hz is recommended). Will switch to next possible highest priority task.

	Priority Above Normal: Turn the Red LED off, ticks = 58500.
	Priority Above Normal: Turn the Orange LED off.
	Priority Above Normal: Task is halted for 1.5 seconds. Will switch to next possible highest priority task.

	Priority Above Normal: Turn the Orange LED on, ticks = 60000.
	Priority Above Normal: Simulate task execution, Red LED will flash 0.5 second (20Hz is recommended). Will switch to next possible highest priority task.

	Priority Normal: Turn the Blue LED ON, ticks = 60001.
	Priority Normal: Simulate task execution, Green LED will flash for 4 seconds (20Hz is recommended). Will switch to next possible highest priority task.

	Priority Above Normal: Turn the Red LED off, ticks = 60500.
	Priority Above Normal: Turn the Orange LED off.
	Priority Above Normal: Task is halted for 1.5 seconds. Will switch to next possible highest priority task.

	Priority Above Normal: Turn the Orange LED on, ticks = 62000.
	Priority Above Normal: Simulate task execution, Red LED will flash 0.5 second (20Hz is recommended). Will switch to next possible highest priority task.

	Priority Above Normal: Turn the Red LED off, ticks = 62500.
	Priority Above Normal: Turn the Orange LED off.
	Priority Above Normal: Task is halted for 1.5 seconds. Will switch to next possible highest priority task.

	Priority Above Normal: Turn the Orange LED on, ticks = 64000.
	Priority Above Normal: Simulate task execution, Red LED will flash 0.5 second (20Hz is recommended). Will switch to next possible highest priority task.

	Priority Normal: Stop flashing Green LED, ticks = 64001.
	Priority Normal: Turn the Blue LED off.
	Priority Normal: Task is halted for 6 seconds. Will switch to next possible highest priority task.

	*/
  /* USER CODE END FlashRedLedTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

int _write (int file, char *ptr, int length)
{
	for (int i = 0; i < length; i ++)
		ITM_SendChar(*ptr ++);

	return length;
}

/* USER CODE END Application */

