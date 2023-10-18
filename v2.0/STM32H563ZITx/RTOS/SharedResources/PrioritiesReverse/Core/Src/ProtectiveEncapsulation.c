#include <stdio.h>

#include "cmsis_os2.h"

#include "gpio.h"
#include "ProtectiveEncapsulation.h"


typedef enum RESOURCE_OCCUPATION_FLAGS
{
	OCCUPATION_FLAG_IDLE,
	OCCUPATION_FLAG_OCCUPIED,

} OccupationFlags;

void AccessProtectiveData(TaskCategories task)
{
	/* Acquired after the semaphore creation. */

	const osSemaphoreAttr_t ControlSemaphore_attributes =
	{ .name = "ControlSemaphore" };
	static osSemaphoreId_t ControlSemaphoreHandle;
	static OccupationFlags occupationFlag = OCCUPATION_FLAG_IDLE;

	if (occupationFlag == OCCUPATION_FLAG_IDLE)
	{
		//ControlSemaphoreHandle = osSemaphoreNew(1, 1, &ControlSemaphore_attributes);

		//osSemaphoreRelease(ControlSemaphoreHandle);

		occupationFlag = OCCUPATION_FLAG_OCCUPIED;
	}

	//osSemaphoreAcquire(ControlSemaphoreHandle, osWaitForever);

	uint8_t i;
	uint32_t j;

	for (i = 0; i < 20; i ++)
	{
		if (task == TASK_FLASH_GREEN)
			HAL_GPIO_WritePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin, GPIO_PIN_SET);
		else if (task == TASK_FLASH_RED)
			HAL_GPIO_WritePin(RED_LED_GPIO_Port, RED_LED_Pin, GPIO_PIN_SET);

		for (j = 0; j < ITERATIONS; j ++)
			;

		if (task == TASK_FLASH_GREEN)
			HAL_GPIO_WritePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin, GPIO_PIN_RESET);
		else if (task == TASK_FLASH_RED)
			HAL_GPIO_WritePin(RED_LED_GPIO_Port, RED_LED_Pin, GPIO_PIN_RESET);

		/* 50 milliseconds loop. Change the value accordingly. */
		for (j = 0; j < ITERATIONS; j ++)
		{
			;
		}
	}

	occupationFlag = OCCUPATION_FLAG_IDLE;

	//osSemaphoreRelease(ControlSemaphoreHandle);
}

int _write (int *file, char *ptr, int length)
{
	for (int i = 0; i < length; i ++)
		ITM_SendChar(* ptr ++);

	return length;
}
