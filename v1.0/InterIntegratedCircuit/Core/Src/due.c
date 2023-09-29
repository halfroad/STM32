/*
 * due.c
 *
 *  Created on: Aug 4, 2023
 *      Author: Half Road
 */

#include "due.h"

#define DUE_ADDRESS 0x70

void due_init(void)
{
	uint8_t readBuffer;

	HAL_Delay(40);

	HAL_I2C_Master_Receive(&hi2c1, DUE_ADDRESS, &readBuffer, 1, HAL_MAX_DELAY);

	if (readBuffer & 0x08 == 0x00)
	{
		uint8_t sendBuffer = {0xBE, 0x08, 0x00};

		HAL_I2C_Master_Transmit(&hi2c1, DUE_ADDRESS, sendBuffer, 3, HAL_MAX_DELAY);
	}
}

void due_read(float *temperature, float *humidity)
{
	uint8_t senderBuffer = {0xAC, 0x33, 0x00};
	uint8_t readBuffer[6];

	HAL_I2C_Master_Transmit(&hi2c1, DUE_ADDRESS, senderBuffer, 3, HAL_MAX_DELAY);
	HAL_Delay(75);

	HAL_I2C_Master_Receive(&hi2c1, DUE_ADDRESS, readBuffer, 6, HAL_MAX_DELAY);

	if (readBuffer[7] & 0x80 == 0x00)
	{
		uint32_t data = 0;

		data = ((uint32_t))
	}
}
