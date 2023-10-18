/*
 * ProtectiveEncapsulation.h
 *
 *  Created on: Oct 15, 2023
 *      Author: Jinhui
 */

#ifndef INC_PROTECTIVEENCAPSULATION_H_
#define INC_PROTECTIVEENCAPSULATION_H_

typedef enum TASK_CATEGORIES
{
	TASK_FLASH_GREEN,
	TASK_FLASH_RED,

} TaskCategories;

#define ITERATIONS	10000

void AccessProtectiveData(TaskCategories task);

#endif /* INC_PROTECTIVEENCAPSULATION_H_ */
