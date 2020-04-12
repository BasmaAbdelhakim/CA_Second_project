/************************************************************************************************
 * Schedular_interface.h
 *
 *  Created on: 12 Mar 2020
 *      Author: Basma Abdelhakim
 ************************************************************************************************/

#ifndef SCHEDULAR_INTERFACE_H_
#define SCHEDULAR_INTERFACE_H_

#include "Schedular_config.h"

#define  READY_STATUS     1
#define  SUSPEND_STATUS   0

/************************************Functions prototypes****** *********************************/


/************************************************************************************************
 Description:
           This function is used to set OS flag to one to be used later by schedular_start
           function.
 ************************************************************************************************/
void setOs_Flag(void);

/************************************************************************************************
 Description:
          1.This function is used to initialize the system tasks array with the values obtained
             from Schedular_config.h and Schedular_config.c
           2.It also used to initialize SYSTIC timer and set its time to  TIC time in US .
           3.It sets setOs_Flag as call back function for SYSTIC timer.
 ************************************************************************************************/
void schedular_init(void);

/************************************************************************************************
 Description:
            This function is used in:
              1.start SYSTIC timer.
              2.According to OS flag it starts OS.
 ************************************************************************************************/
void schedular_start(void);


/************************************************************************************************
 Description:
            This function is used to call the tasks runnable according to their periodicity
             configured in the Schedular_config.c file.
 ************************************************************************************************/
void start_OS(void);


#endif /* SCHEDULAR_INTERFACE_H_ */
