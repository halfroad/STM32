/*
 * eeprom.c
 *
 *  Created on: Sep 10, 2023
 *      Author: jinhui
 */

#include <string.h>

#include "eeprom.h"

#define EEPROM_WRITE_ADDRESS	0xA0
#define EEPROM_READ_ADDRESS		0xA1

#define BUFFER_SIZE				256

uint8_t WriteBuffer[BUFFER_SIZE], ReadBuffer[BUFFER_SIZE];


void write()
{
	for (uint8_t i = 0; i < BUFFER_SIZE; i ++)
		WriteBuffer[i] = 'A';

	printf("\r\n EEPROM 24C02 Write Test OK \r\n");

	for (uint8_t i = 0; i < BUFFER_SIZE; i ++)
	{
		HAL_StatusTypeDef status = HAL_I2C_Mem_Write(&hi2c1, EEPROM_WRITE_ADDRESS, i, I2C_MEMADD_SIZE_8BIT, &WriteBuffer[i], 1, 0xff);
		HAL_Delay(5);
	}

	printf("Write bytes into AT24C02 EEPROM id done...\r\n");
}

void read()
{
	HAL_I2C_Mem_Read(&hi2c1, EEPROM_READ_ADDRESS, 0, I2C_MEMADD_SIZE_8BIT, ReadBuffer, BUFFER_SIZE, 0xff);

	for (uint8_t i = 0; i < BUFFER_SIZE; i ++)
		printf("0x%02X ", ReadBuffer[i]);
}
