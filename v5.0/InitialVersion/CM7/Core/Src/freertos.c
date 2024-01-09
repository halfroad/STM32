/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : freertos.c
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
#include "gpio.h"
#include "cmsis_os.h"

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
const osThreadAttr_t FlashGreenLEDTask_attributes =
{ .name = "FlashGreenLEDTask", .stack_size = 128 * 4, .priority =
		(osPriority_t) osPriorityNormal, };
/* Definitions for FlashRedLEDTask */
osThreadId_t FlashRedLEDTaskHandle;
const osThreadAttr_t FlashRedLEDTask_attributes =
{ .name = "FlashRedLEDTask", .stack_size = 128 * 4, .priority =
		(osPriority_t) osPriorityNormal, };

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartFlashGreenLEDTask(void *argument);
void StartFlashRedLEDTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Hook prototypes */
void vApplicationIdleHook(void);
void vApplicationTickHook(void);

/* USER CODE BEGIN 2 */
void vApplicationIdleHook(void)
{
	/* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
	 to 1 in FreeRTOSConfig.h. It will be called on each iteration of the idle
	 task. It is essential that code added to this hook function never attempts
	 to block in any way (for example, call xQueueReceive() with a block time
	 specified, or call vTaskDelay()). If the application makes use of the
	 vTaskDelete() API function (as this demo application does) then it is also
	 important that vApplicationIdleHook() is permitted to return to its calling
	 function, because it is the responsibility of the idle task to clean up
	 memory allocated by the kernel to any task that has since been deleted. */
}
/* USER CODE END 2 */

/* USER CODE BEGIN 3 */
void vApplicationTickHook(void)
{
	/* This function will be called by each tick interrupt if
	 configUSE_TICK_HOOK is set to 1 in FreeRTOSConfig.h. User code can be
	 added here, but the tick hook is called from an interrupt context, so
	 code must not attempt to block, and only the interrupt safe FreeRTOS API
	 functions can be used (those that end in FromISR()). */
}
/* USER CODE END 3 */

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

	/* Create the thread(s) */
	/* creation of FlashGreenLEDTask */
	FlashGreenLEDTaskHandle = osThreadNew(StartFlashGreenLEDTask, NULL,
			&FlashGreenLEDTask_attributes);

	/* creation of FlashRedLEDTask */
	FlashRedLEDTaskHandle = osThreadNew(StartFlashRedLEDTask, NULL,
			&FlashRedLEDTask_attributes);

	/* USER CODE BEGIN RTOS_THREADS */
	/* add threads, ... */
	/* USER CODE END RTOS_THREADS */

	/* USER CODE BEGIN RTOS_EVENTS */
	/* add events, ... */
	/* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartFlashGreenLEDTask */
/**
 * @brief  Function implementing the FlashGreenLEDTask thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartFlashGreenLEDTask */
void StartFlashGreenLEDTask(void *argument)
{
	/* USER CODE BEGIN StartFlashGreenLEDTask */
	/* Infinite loop */
	for (;;)
	{
		HAL_GPIO_TogglePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin);
		HAL_GPIO_TogglePin(RED_LED_GPIO_Port, RED_LED_Pin);

		osDelay(500);
	}
	/* USER CODE END StartFlashGreenLEDTask */
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
	/* USER CODE BEGIN StartFlashRedLEDTask */
	/* Infinite loop */
	for (;;)
	{
		osDelay(1);
	}
	/* USER CODE END StartFlashRedLEDTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

