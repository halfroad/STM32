/*
 * CriticalObject.h
 *
 *  Created on: Oct 25, 2023
 *      Author: Li, Hui
 */

#ifndef INC_CRITICALOBJECT_H_
#define INC_CRITICALOBJECT_H_

void SetGreenLedFlashingRate(uint8_t greenLedFlashRate);
void SetRedLedFlashingRate(uint8_t redLedFlashRate);

uint8_t GetGreenLedFlashingRate(void);
uint8_t GetRedLedFlashingRate(void);

#endif /* INC_CRITICALOBJECT_H_ */
