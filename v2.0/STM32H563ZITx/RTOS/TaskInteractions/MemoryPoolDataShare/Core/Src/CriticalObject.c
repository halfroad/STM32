/*
 * CriticalObject.c
 *
 *  Created on: Oct 25, 2023
 *       Author: Li, Hui
 */

#include "FreeRTOS.h"
#include "cmsis_os2.h"

#include "CriticalObject.h"

typedef struct
{
	uint8_t GreenLedFlashRate;
	uint8_t RedLedFlashRate;

} FlashingRate;

const osSemaphoreAttr_t semaphoreAttributes = {
		.name = "Binary Semaphore"
};

osSemaphoreId_t semaphoreHandle;

void Init()
{
	semaphoreHandle = osSemaphoreNew(1, 0, &semaphoreAttributes);
}

FlashingRate FlashingRatePool = {10, 1};

void SetGreenLedFlashingRate(uint8_t greenLedFlashRate)
{
	osSemaphoreAcquire(semaphoreHandle, osWaitForever);

	FlashingRatePool.GreenLedFlashRate = greenLedFlashRate;

	osSemaphoreRelease(semaphoreHandle);
}

void SetRedLedFlashingRate(uint8_t redLedFlashRate)
{
	osSemaphoreAcquire(semaphoreHandle, osWaitForever);

	FlashingRatePool.RedLedFlashRate = redLedFlashRate;

	osSemaphoreRelease(semaphoreHandle);
}

uint8_t GetGreenLedFlashingRate(void)
{
	return FlashingRatePool.GreenLedFlashRate;
}

uint8_t GetRedLedFlashingRate(void)
{
	return FlashingRatePool.RedLedFlashRate;
}
