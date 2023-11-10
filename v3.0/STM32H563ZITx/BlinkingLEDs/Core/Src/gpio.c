/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    gpio.c
 * @brief   This file provides code for the configuration
 *          of all used GPIO pins.
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
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
 * Analog
 * Input
 * Output
 * EVENT_OUT
 * EXTI
 PC1   ------> ETH_MDC
 PA1   ------> ETH_REF_CLK
 PA2   ------> ETH_MDIO
 PA4   ------> ADCx_INP18
 PA7   ------> ETH_CRS_DV
 PC4   ------> ETH_RXD0
 PC5   ------> ETH_RXD1
 PB13   ------> UCPD1_CC1
 PB14   ------> UCPD1_CC2
 PB15   ------> ETH_TXD1
 PD8   ------> USART3_TX
 PD9   ------> USART3_RX
 PA11   ------> USB_DM
 PA12   ------> USB_DP
 PG11   ------> ETH_TX_EN
 PG13   ------> ETH_TXD0
 PB6   ------> LPUART1_TX
 PB7   ------> LPUART1_RX
 */
void MX_GPIO_Init(void)
{

	LL_EXTI_InitTypeDef EXTI_InitStruct =
	{ 0 };
	LL_GPIO_InitTypeDef GPIO_InitStruct =
	{ 0 };

	/* GPIO Ports Clock Enable */
	LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOE);
	LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOC);
	LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOF);
	LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOH);
	LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);
	LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB);
	LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOD);
	LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOG);

	/**/
	LL_GPIO_ResetOutputPin(LED2_YELLOW_GPIO_Port, LED2_YELLOW_Pin);

	/**/
	LL_GPIO_ResetOutputPin(LED1_GREEN_GPIO_Port, LED1_GREEN_Pin);

	/**/
	LL_GPIO_ResetOutputPin(LED3_RED_GPIO_Port, LED3_RED_Pin);

	/**/
	LL_EXTI_SetEXTISource(LL_EXTI_EXTI_PORTC, LL_EXTI_EXTI_LINE13);

	/**/
	LL_EXTI_SetEXTISource(LL_EXTI_EXTI_PORTG, LL_EXTI_EXTI_LINE7);

	/**/
	EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_13;
	EXTI_InitStruct.Line_32_63 = LL_EXTI_LINE_NONE;
	EXTI_InitStruct.LineCommand = ENABLE;
	EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
	EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_RISING;
	LL_EXTI_Init(&EXTI_InitStruct);

	/**/
	EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_7;
	EXTI_InitStruct.Line_32_63 = LL_EXTI_LINE_NONE;
	EXTI_InitStruct.LineCommand = ENABLE;
	EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
	EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_RISING;
	LL_EXTI_Init(&EXTI_InitStruct);

	/**/
	LL_GPIO_SetPinPull(USER_BUTTON_GPIO_Port, USER_BUTTON_Pin, LL_GPIO_PULL_NO);

	/**/
	LL_GPIO_SetPinPull(UCPD_FLT_GPIO_Port, UCPD_FLT_Pin, LL_GPIO_PULL_NO);

	/**/
	LL_GPIO_SetPinMode(USER_BUTTON_GPIO_Port, USER_BUTTON_Pin,
			LL_GPIO_MODE_INPUT);

	/**/
	LL_GPIO_SetPinMode(UCPD_FLT_GPIO_Port, UCPD_FLT_Pin, LL_GPIO_MODE_INPUT);

	/**/
	GPIO_InitStruct.Pin = LED2_YELLOW_Pin;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	LL_GPIO_Init(LED2_YELLOW_GPIO_Port, &GPIO_InitStruct);

	/**/
	GPIO_InitStruct.Pin = RMII_MDC_Pin | RMII_RXD0_Pin | RMII_RXD1_Pin;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	GPIO_InitStruct.Alternate = LL_GPIO_AF_11;
	LL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	/**/
	GPIO_InitStruct.Pin = RMII_REF_CLK_Pin | RMII_MDIO_Pin | RMII_CRS_DV_Pin;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	GPIO_InitStruct.Alternate = LL_GPIO_AF_11;
	LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/**/
	GPIO_InitStruct.Pin = VBUS_SENSE_Pin;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	LL_GPIO_Init(VBUS_SENSE_GPIO_Port, &GPIO_InitStruct);

	/**/
	GPIO_InitStruct.Pin = LED1_GREEN_Pin;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	LL_GPIO_Init(LED1_GREEN_GPIO_Port, &GPIO_InitStruct);

	/**/
	GPIO_InitStruct.Pin = UCPD_CC1_Pin | UCPD_CC2_Pin;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/**/
	GPIO_InitStruct.Pin = RMII_TXD1_Pin;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	GPIO_InitStruct.Alternate = LL_GPIO_AF_11;
	LL_GPIO_Init(RMII_TXD1_GPIO_Port, &GPIO_InitStruct);

	/**/
	GPIO_InitStruct.Pin = T_VCP_TX_Pin | T_VCP_RX_Pin;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	GPIO_InitStruct.Alternate = LL_GPIO_AF_7;
	LL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	/**/
	GPIO_InitStruct.Pin = LED3_RED_Pin;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	LL_GPIO_Init(LED3_RED_GPIO_Port, &GPIO_InitStruct);

	/**/
	GPIO_InitStruct.Pin = USB_FS_N_Pin | USB_FS_P_Pin;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	GPIO_InitStruct.Alternate = LL_GPIO_AF_10;
	LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/**/
	GPIO_InitStruct.Pin = RMII_TXT_EN_Pin | RMI_TXD0_Pin;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	GPIO_InitStruct.Alternate = LL_GPIO_AF_11;
	LL_GPIO_Init(GPIOG, &GPIO_InitStruct);

	/**/
	GPIO_InitStruct.Pin = ARD_D1_TX_Pin | ARD_D0_RX_Pin;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	GPIO_InitStruct.Alternate = LL_GPIO_AF_8;
	LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
