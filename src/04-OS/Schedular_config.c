/*
 * Schedular_config.c
 *
 *  Created on: 12 Mar 2020
 *      Author: Basma Abdelhakim
 */
#include "../03-LIB/STD_TYPES.h"

#include "Schedular_config.h"
#include "Schedular_interface.h"

/************************************************************************************************
  user_task_t field:
             It represents the basic array of tasks defined by the the user.
             Each task is created by its module and it is externed here.
             It has two fields:
                      1. A pointer to  the task runnable.
                      2.The task periodicity in ms.
  sys_tasks_info:
              It represents a modified version of the previous field.
              It has two fields:
                      1. A pointer to the previous  filed.
                      2. first delay of the tasks in ms.
 ************************************************************************************************/
extern user_task_t LCD_TASK;

basic_task_info const sys_tasks_info [MAX_NUMBER_OF_TASKS]={{&LCD_TASK,0}};
