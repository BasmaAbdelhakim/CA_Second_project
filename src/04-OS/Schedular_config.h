/*
 * Schedular.h
 *
 *  Created on: 12 Mar 2020
 *      Author: Basma Abdelhakim
 */

#ifndef SCHEDULAR_H_
#define SCHEDULAR_H_

/************************************************************************************************
  Tic_Time_MS:
             It represents the desired TIC time in MS configured by user.
  MAX_NUMBER_OF_TASKS:
             It represents the max number of the running tasks in the system
             configured by the user.
 ***********************************************************************************************/
#define Tic_Time_MS          2
#define MAX_NUMBER_OF_TASKS  1


typedef void (*task_runnable_t)(void);
typedef struct{
	task_runnable_t taskRunnable;
	u32 periodicity_ms;
}user_task_t;

typedef struct{
	user_task_t * task;
	u32 firstDelay;
}basic_task_info;


#endif /* SCHEDULAR_H_ */
