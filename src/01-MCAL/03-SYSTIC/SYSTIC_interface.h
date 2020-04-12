/*
 * SYSTIC_interface.h
 *
 *  Created on: 12 Mar 2020
 *      Author: Basma Abdelhakim
 */

#ifndef SYSTIC_INTERFACE_H_
#define SYSTIC_INTERFACE_H_

typedef void (*sysTic_CB_t)(void);

/************************************STK_CTRL register bits**************************************/
#define CLKSRC_AHB_8    0x00000000
#define CLKSRC_AHB      0x00000004

#define TIC_ENABLE_INT  0x00000002
#define TIC_DISABLE_INT 0x00000000

#define SYS_TIC_START   0x00000001
#define SYS_TIC_STOP    0x00000000
/************************************************************************************************/


/************************************Functions prototypes****** *********************************/

/************************************************************************************************
 Description:
          This function is used to initialize  the SysTic timer according to the configuration
                   in the SYSTIC_config.h file
           It is used to configure the following configurations:
              1.Configure preScaller as AHP or AHP/8,
                For STM the only available option from clockTree is AHB/8.
              2.Enable or disable SysTic interrupt
 Outputs:
       It returns in case of correct execution   OK
       It returns in case of incorrect execution NOK
 ***********************************************************************************************/
u8 SysTic_init(void);

/************************************************************************************************
 Description:
          This function is used to start  the SysTic timer.
          It must be called after setting the following:
              1.systic timer callback function.
              2.The desired  user time in us.
 Outputs:
       It returns in case of correct execution   OK
       It returns in case of incorrect execution NOK
 ***********************************************************************************************/
u8 SysTic_start(void);

/************************************************************************************************
 Description:
          This function is used to stop  the systic timer.
 Outputs:
       It returns in case of correct execution   OK
       It returns in case of incorrect execution NOK
 ***********************************************************************************************/
u8 SysTic_stop(void);

/************************************************************************************************
 Description:
          This function is used to set the desired  user time in us according to input system
          clock.This information can be determined after calling the RCC_GetSystemClock from
          the RCC module.
 Outputs:
       It returns in case of correct execution   OK
       It returns in case of incorrect execution NOK
 ***********************************************************************************************/
u8 SysTic_SetTime(u32 Time_us,const u8 inputClock);

/************************************************************************************************
 Description:
          This function is used to set the SysTic call back function which will be called when
           the SysTic timer reaches zero and if the SysTic interrupt is enabled.
 Outputs:
       It returns in case of correct execution   OK
       It returns in case of incorrect execution NOK
 ***********************************************************************************************/
u8 SysTic_SetCallBackFun(sysTic_CB_t  CallbackFun);


#endif /* SYSTIC_INTERFACE_H_ */
