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
	AlarmNotTriggered = 0U, AlarmTriggered,

} AlarmStates;

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
/* Definitions for AlarmTask */
osThreadId_t AlarmTaskHandle;
const osThreadAttr_t AlarmTask_attributes =
{ .name = "AlarmTask", .priority = (osPriority_t) osPriorityNormal,
		.stack_size = 128 * 4 };
/* Definitions for SensorSurveillanceTask */
osThreadId_t SensorSurveillanceTaskHandle;
const osThreadAttr_t SensorSurveillanceTask_attributes =
{ .name = "SensorSurveillanceTask", .priority = (osPriority_t) osPriorityLow,
		.stack_size = 128 * 4 };
/* Definitions for MessagesQueue */
osMessageQueueId_t MessagesQueueHandle;
const osMessageQueueAttr_t MessagesQueue_attributes =
{ .name = "MessagesQueue" };

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartAlarmTask(void *argument);
void StartSensorSurveillanceTask(void *argument);

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
	/* creation of MessagesQueue */
	MessagesQueueHandle = osMessageQueueNew(1, sizeof(uint16_t),
			&MessagesQueue_attributes);

	/* USER CODE BEGIN RTOS_QUEUES */
	/* add queues, ... */
	/* USER CODE END RTOS_QUEUES */
	/* creation of AlarmTask */
	AlarmTaskHandle = osThreadNew(StartAlarmTask, NULL, &AlarmTask_attributes);

	/* creation of SensorSurveillanceTask */
	SensorSurveillanceTaskHandle = osThreadNew(StartSensorSurveillanceTask,
	NULL, &SensorSurveillanceTask_attributes);

	/* USER CODE BEGIN RTOS_THREADS */
	/* add threads, ... */
	/* USER CODE END RTOS_THREADS */

	/* USER CODE BEGIN RTOS_EVENTS */
	/* add events, ... */
	/* USER CODE END RTOS_EVENTS */

}
/* USER CODE BEGIN Header_StartAlarmTask */
/**
 * @brief Function implementing the AlarmTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartAlarmTask */
void StartAlarmTask(void *argument)
{
	/* USER CODE BEGIN AlarmTask */
	/* Infinite loop */

	static AlarmStates alarmState;

	for (;;)
	{
		osStatus_t status = osMessageQueueGet(MessagesQueueHandle, &alarmState,
		NULL, osWaitForever);

		if (osOK == status)
		{
			if (AlarmTriggered == alarmState)
				HAL_GPIO_WritePin(RED_LED_GPIO_Port, RED_LED_Pin, GPIO_PIN_SET);
			else
				HAL_GPIO_WritePin(RED_LED_GPIO_Port, RED_LED_Pin,
						GPIO_PIN_RESET);

		}

		osDelay(500);
	}
	/* USER CODE END AlarmTask */
}

/* USER CODE BEGIN Header_StartSensorSurveillanceTask */
/**
 * @brief Function implementing the SensorSurveillanceTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartSensorSurveillanceTask */
void StartSensorSurveillanceTask(void *argument)
{
	/* USER CODE BEGIN SensorSurveillanceTask */
	/* Infinite loop */

	static GPIO_PinState state;
	static AlarmStates alarmState;

	/*
	 * https://blog.csdn.net/weixin_41114301/article/details/127350538
	 */
	for (;;)
	{
		state = HAL_GPIO_ReadPin(PUSH_BUTTON_GPIO_Port,
		PUSH_BUTTON_Pin);

		if (GPIO_PIN_SET == state)
		{
			if (AlarmNotTriggered == alarmState)
			{
				alarmState = AlarmTriggered;

				HAL_GPIO_WritePin(YELLOW_LED_GPIO_Port, YELLOW_LED_Pin,
						GPIO_PIN_SET);
			}
			else
			{
				alarmState = AlarmNotTriggered;
				HAL_GPIO_WritePin(YELLOW_LED_GPIO_Port, YELLOW_LED_Pin,
						GPIO_PIN_RESET);
			}

			osMessageQueuePut(MessagesQueueHandle, &alarmState, 0UL, 0UL);
		}

		osDelay(500);
	}
	/* USER CODE END SensorSurveillanceTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

void HAL_GPIO_EXTI_Rising_Callback(uint16_t GPIO_Pin)
{
	HAL_GPIO_WritePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin, GPIO_PIN_SET);
}

void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin)
{
	HAL_GPIO_WritePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin, GPIO_PIN_RESET);
}

int _write(int file, char *ptr, int length)
{
	for (int i = 0; i < length; i++)
		ITM_SendChar(*ptr++);

	return length;
}
/* USER CODE END Application */

