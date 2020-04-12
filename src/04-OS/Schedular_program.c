/*
 * Shedular_program.c
 *
 *  Created on: 12 Mar 2020
 *      Author: Basma Abdelhakim
 */

#include "../03-LIB/STD_TYPES.h"

#include "../01-MCAL/01-RCC/RCC_interface.h"
#include "../01-MCAL/03-SYSTIC/SYSTIC_interface.h"

#include "Schedular_interface.h"


typedef struct {
	basic_task_info * task;
	u32 periodicityTicksMs;
	u32 ticsToExec;
    u8  taskStatus;
} SysTasks_t;

/**************************************Global variables*******************************************/
extern basic_task_info sys_tasks_info [MAX_NUMBER_OF_TASKS];
static SysTasks_t sysTasks[MAX_NUMBER_OF_TASKS];
u8 currentTaskRunning=0;
u8 OS_FLAG = 0;
/************************************************************************************************/


/*****************************************Functions**********************************************/

/************************************************************************************************/

void setOs_Flag(void) {
	OS_FLAG = 1;
}

/************************************************************************************************/

void schedular_init(void) {
	u32 inputClock;
	u32 TicTimeUs;
	for(currentTaskRunning=0;currentTaskRunning<MAX_NUMBER_OF_TASKS;currentTaskRunning++){
		sysTasks[currentTaskRunning].task= &sys_tasks_info[currentTaskRunning];
		sysTasks[currentTaskRunning].periodicityTicksMs=(sys_tasks_info[currentTaskRunning].task->periodicity_ms) / Tic_Time_MS;
		sysTasks[currentTaskRunning].ticsToExec= sys_tasks_info[currentTaskRunning].firstDelay / Tic_Time_MS ;
		sysTasks[currentTaskRunning].taskStatus=READY_STATUS;
	}
	SysTic_init();

	RCC_GetSystemClock(&inputClock);

	TicTimeUs=Tic_Time_MS*1000;
	SysTic_SetTime(TicTimeUs, inputClock);
	SysTic_SetCallBackFun(setOs_Flag);
}
/************************************************************************************************/

void schedular_start(void){
	SysTic_start();
	while(1){
		if(OS_FLAG){
			OS_FLAG=0;
            start_OS();
		}
	}
}
/************************************************************************************************/

void start_OS(void){
    u8 i=0;
    for(i=0;i<MAX_NUMBER_OF_TASKS;i++){
    	if(sysTasks[i].ticsToExec==0 && sysTasks[i].taskStatus==READY_STATUS){
    		sysTasks[i].task->task->taskRunnable();
    		sysTasks[i].ticsToExec=sysTasks[i].periodicityTicksMs;
    	}
    	sysTasks[i].ticsToExec--;
    }
}

/************************************************************************************************/
