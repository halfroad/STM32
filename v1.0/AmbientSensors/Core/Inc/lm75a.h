/*
 * lm75a.h
 *
 *  Created on: Aug 15, 2023
 *      Author: Half Road
 */

#ifndef INC_LM75A_H_
#define INC_LM75A_H_

#include "lm75a.h"

#define LM75A_SLAVE_ADDRESS 		(0x48 << 1)
#define LM75A_TEMPERATURE_REGISTER	0x00
#define LM75A_CONFIGURE_REGISTER	0x01


void lm75a_init();
float lm75a_acquire_temperature(void);

#endif /* INC_LM75A_H_ */
