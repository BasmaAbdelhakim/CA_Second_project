/*
 * SYSTIC_program.c
 *
 *  Created on: 12 Mar 2020
 *      Author: Basma Abdelhakim
 */


#include "../../03-LIB/STD_TYPES.h"

#include "SYSTIC_config.h"
#include "SYSTIC_interface.h"

#define SYS_TIC_BASE_ADRESS   0xE000E010
#define SysTic ((volatile SysTic_t *)SYS_TIC_BASE_ADRESS)
typedef struct {
	u32 STK_CTRL;
	u32 STK_LOAD;
	u32 STK_VAL;
	u32 STK_CALIB;
} SysTic_t;
static sysTic_CB_t   APPLICATION_CALLBACK_FUN;

/**************************************Global Variables******************************************/
#define AHB_8_PRESCALER   8U
#define AHB_PRESCALER     1U
#define SYS_TIC_BITS      24U
/***********************************************************************************************/

/********************************************Functions******************************************/
u8 SysTic_init(void) {
	u8 returnStatus = OK;
	/*Disable the SysTic timer */
	SysTic->STK_CTRL |= SYS_TIC_STOP;

	/*Configure preScaller as AHP or AHP/8
	 * For STM the only available option from clockTree is AHB/8 */
	SysTic->STK_CTRL |= SYS_TIC_CLKSRC;
	if ((SysTic->STK_CTRL & SYS_TIC_CLKSRC) != SYS_TIC_CLKSRC) {
		returnStatus = NOK;
	}
	/*Enable or disable SysTic interrupt*/
	SysTic->STK_CTRL |= SYS_TIC_INT_STATUS;
	if ((SysTic->STK_CTRL & SYS_TIC_INT_STATUS) != SYS_TIC_INT_STATUS) {
		returnStatus = NOK;
	}
	return returnStatus;
}
/***********************************************************************************************/

u8 SysTic_start(void) {
	u8 returnStatus = OK;
	SysTic->STK_CTRL |= SYS_TIC_START;
	if ((SysTic->STK_CTRL & SYS_TIC_START) != SYS_TIC_START) {
		returnStatus = NOK;
	}
	return returnStatus;
}
/***********************************************************************************************/

u8 SysTic_stop(void) {
	u8 returnStatus = OK;
	SysTic->STK_CTRL |= SYS_TIC_STOP;
	if ((SysTic->STK_CTRL & SYS_TIC_STOP) != SYS_TIC_STOP) {
		returnStatus = NOK;
	}
	return returnStatus;
}
/***********************************************************************************************/

u8 SysTic_SetTime(u32 Time_us, const u8 inputClock) {
	u8 returnStatus = OK;
	u8 SysTicClock;
	u32 preScaler;
	f32 preloadValue;

    #if SYS_TIC_CLKSRC == CLKSRC_AHB_8
		preScaler=AHB_8_PRESCALER;

    #elif SYS_TIC_CLKSRC == CLKSRC_AHB
		preScaler=AHB_PRESCALER;
    #else
		returnStatus = NOK;
    #endif

	SysTicClock=inputClock/preScaler;
	preloadValue=Time_us/(1.0/SysTicClock);
	SysTic->STK_LOAD=(u32)preloadValue;
	return returnStatus;
}
/***********************************************************************************************/

u8 SysTic_SetCallBackFun(sysTic_CB_t CallbackFun) {
	u8 returnStatus = OK;
	if(CallbackFun){
		APPLICATION_CALLBACK_FUN=CallbackFun;
	}
	else{
		returnStatus = NOK;
	}
	return returnStatus;
}
/***********************************************************************************************/

void SysTick_Handler(void){
	if(APPLICATION_CALLBACK_FUN){
		APPLICATION_CALLBACK_FUN();
	}

}
/***********************************************************************************************/
