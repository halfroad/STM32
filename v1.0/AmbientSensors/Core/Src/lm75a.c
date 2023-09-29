/*
 * lm75a.c
 *
 *  Created on: Aug 14, 2023
 *      Author: Half Road
 */

#include <stdio.h>
#include "i2c.h"
#include "lm75a.h"



static int write_byte(uint8_t ip, uint8_t data)
{
	HAL_StatusTypeDef status = HAL_I2C_Mem_Write(&hi2c1, LM75A_SLAVE_ADDRESS, ip, I2C_MEMADD_SIZE_8BIT, &data, 1,  HAL_MAX_DELAY);

	if (status != HAL_OK)
	{
		printf("%s: failed to write register\n", __func__);

		return -1;
	}

	return 0;
}

static int read_word(uint8_t ip)
{
	uint8_t bytes[2];
	HAL_StatusTypeDef status = HAL_I2C_Mem_Read(&hi2c1, LM75A_SLAVE_ADDRESS, ip, I2C_MEMADD_SIZE_8BIT, bytes, 2, HAL_MAX_DELAY);

	if (status != HAL_OK)
	{
		printf("%s: failed to read register.\n", __func__);
		return -1;
	}

	return (bytes[0] << 8) | bytes[1];
}

void lm75a_init()
{
	write_byte(LM75A_CONFIGURE_REGISTER, 0x00);
}

float lm75a_acquire_temperature(void)
{
	int reading = read_word(LM75A_TEMPERATURE_REGISTER) & 0xffff;

	printf("%s, reading = %x\n", __func__, reading);

	reading >>= 5;

	float temperature = reading * 0.125;

	printf("%s, temperature = %f\n", __func__, temperature);

	return temperature;
}
