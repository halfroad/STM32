/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    dcache.c
  * @brief   This file provides code for the configuration
  *          of the DCACHE instances.
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
#include "dcache.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* DCACHE1 init function */
void MX_DCACHE1_Init(void)
{

  /* USER CODE BEGIN DCACHE1_Init 0 */

  /* USER CODE END DCACHE1_Init 0 */

  /* Peripheral clock enable */
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DCACHE1);

  /* USER CODE BEGIN DCACHE1_Init 1 */

  /* USER CODE END DCACHE1_Init 1 */
  LL_DCACHE_SetReadBurstType(DCACHE1, LL_DCACHE_READ_BURST_WRAP);
  LL_DCACHE_Enable(DCACHE1);
  /* USER CODE BEGIN DCACHE1_Init 2 */

  /* USER CODE END DCACHE1_Init 2 */

}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
