/*
 * HCLCD_program.c
 *
 *  Created on: 25 Mar 2020
 *      Author: Basma Abdelhakim
 */

#include "../../03-LIB/STD_TYPES.h"
#include "../../04-OS/Schedular_interface.h"

#include "HCLCD_interface.h"
#include "HCLCD_config.h"

#include  "../../01-MCAL/02-GPIO/DIO_interface.h"

/***********************************************************************************************
        Definition  of the required GPIO structure to configure GPIO pins of LCD */

const PinConfig_t CLCD_PINS[] = { {CLCD_RS_PORT,CLCD_RS, OUTPUT_PUSHPULL,SPEED_10MHZ,PIN_RESET},
		                          {CLCD_RW_PORT,CLCD_RW, OUTPUT_PUSHPULL,SPEED_10MHZ,PIN_RESET},
					              {CLCD_E_PORT ,CLCD_E , OUTPUT_PUSHPULL,SPEED_10MHZ,PIN_RESET},
					              {CLCD_D0_PORT,CLCD_D0, OUTPUT_PUSHPULL,SPEED_10MHZ,PIN_RESET} ,
					              {CLCD_D1_PORT,CLCD_D1, OUTPUT_PUSHPULL,SPEED_10MHZ,PIN_RESET} ,
					              {CLCD_D2_PORT,CLCD_D2, OUTPUT_PUSHPULL,SPEED_10MHZ,PIN_RESET} ,
					              {CLCD_D3_PORT,CLCD_D3, OUTPUT_PUSHPULL,SPEED_10MHZ,PIN_RESET} ,
					              {CLCD_D4_PORT,CLCD_D4, OUTPUT_PUSHPULL,SPEED_10MHZ,PIN_RESET} ,
					              {CLCD_D5_PORT,CLCD_D5, OUTPUT_PUSHPULL,SPEED_10MHZ,PIN_RESET} ,
					              {CLCD_D6_PORT,CLCD_D6, OUTPUT_PUSHPULL,SPEED_10MHZ,PIN_RESET} ,
					              {CLCD_D7_PORT,CLCD_D7, OUTPUT_PUSHPULL,SPEED_10MHZ,PIN_RESET} ,
                             };


/***********************************************************************************************/

/*******************************************(Macros)********************************************/
#define LCD_PINS                 11U
#define IDEL_PROCESS             0U
#define WRITE_STRING_PROCESS     1U
#define CLEAR_PROCESS            2U
#define MOVE_CURSOR_PROCESS      3U

#define INITIALIZATION_DELAY     0U
#define FUNCTION_SET_COMMAND     1U
#define DISPLAY_ON_OFF_COMMAND   2U
#define DISPLAY_CLEAR_COMMAND    3U
#define ENTRY_MODE_SET           4U

#define DEFAULt_FS_CONFIGURATION       0x30
#define FUNCTION_SET_CONFIGURATION     (DEFAULt_FS_CONFIGURATION | \
                                            CLCD_CHARACTER_FONT  | \
                                            CLCD_LINES_DISPLAYED)

#define DEFAULt_DISPLAY_CONFIGURATION       0x08
#define DISPLAY_ON_OFF_CONFIGURATION       (DEFAULt_DISPLAY_CONFIGURATION| \
		                                    CLCLD_DIAPLY_MODE | \
											CLCD_CURSOR_MODE  | \
											CLCD_BLINK_MODE)

#define DISPLAY_CLEAR                    0x01

 /**********************************************************************************************/


/***************************************Prototypes*********************************************/
static u8 HCLCD_initProcess(void);
static void HCLCD_writeStringProcess(void);
static void HCLCD_clearProcess(void);
static void HCLCD_moveCursorProcess(void);

/***********************************************************************************************/


/***************************************Global variables****************************************/
const user_task_t LCD_TASK ={&HCLCD_task,2};

static  const u32 CLCD_DATA_PINS[8] = { CLCD_D0, CLCD_D1, CLCD_D2, CLCD_D3, CLCD_D4,
		CLCD_D5, CLCD_D6, CLCD_D7 };

static  const GPIO_t * CLCD_DATA_PORTS[8]={CLCD_D0_PORT,CLCD_D1_PORT,CLCD_D2_PORT,CLCD_D3_PORT,CLCD_D4_PORT,
		CLCD_D5_PORT,CLCD_D6_PORT,CLCD_D7_PORT};

static const u8 MAX_DATA_BITS=8;

static u8 INIT_COMPLETED_FLAG;
static u8 CURRENT_PROCESS;
static u8 lenght;
static u8 word[255];
static u8 REQUESTED_ROW;
static u8 REQUESTED_COLUMN;

static notify_t WRITE_DONE_NOTIFICATION;
static notify_t CLEAR_DONE_NOTIFICATION;
static notify_t MOVE_CURSOR_DONE_NOTIFICATION;
/***********************************************************************************************/


/******************************************Functions********************************************/

/***********************************************************************************************/
ERROR_STATUS HCLCD_init(void) {
	ERROR_STATUS returnValue;
	u8 iterator;
		for(iterator=0;iterator<LCD_PINS;iterator++){
			returnValue |=MGPIO_ConfigurePinsMode(&CLCD_PINS[iterator]);
		}

	return returnValue;
}

/***********************************************************************************************/
ERROR_STATUS HCLCD_writeString(const u8 * userWord, u8 userLenght) {

	ERROR_STATUS returnValue;
	u8 wordIndex;

	if (userWord != NULL) {
		if (CURRENT_PROCESS == IDEL_PROCESS) {
			CURRENT_PROCESS = WRITE_STRING_PROCESS;

			for (wordIndex = 0; wordIndex < userLenght; wordIndex++) {
				word[wordIndex] = userWord[wordIndex];
			}
			lenght = userLenght;
			returnValue = OK;
		} else {
			returnValue = NOK;
		}
	}
	else{
		returnValue = NOK;
	}
	return returnValue;
}


/***********************************************************************************************/
ERROR_STATUS HCLCD_writeDoneApp(notify_t appFunction){

	ERROR_STATUS returnValue;

	if(appFunction != NULL){
		WRITE_DONE_NOTIFICATION=appFunction;
		returnValue=OK;
	}
	else{
		returnValue=NOK;
	}
	return returnValue;
}

/***********************************************************************************************/
ERROR_STATUS HCLCD_clear(void) {

	ERROR_STATUS returnValue;

	if (CURRENT_PROCESS == IDEL_PROCESS) {
		CURRENT_PROCESS = CLEAR_PROCESS;
		returnValue = OK;
	} else {
		returnValue = NOK;
	}
	return returnValue;
}

/***********************************************************************************************/
ERROR_STATUS HCLCD_clearDoneApp(notify_t appFunction){

	ERROR_STATUS returnValue;
	if(appFunction != NULL){
		CLEAR_DONE_NOTIFICATION=appFunction;
		returnValue=OK;
	}
	else{
		returnValue=NOK;
	}
	return returnValue;
}

/***********************************************************************************************/
ERROR_STATUS HCLCD_moveCursorLocation(u8 row , u8 column){

	ERROR_STATUS returnValue;

	if (CURRENT_PROCESS == IDEL_PROCESS) {
			CURRENT_PROCESS = MOVE_CURSOR_PROCESS;
			REQUESTED_ROW=row;
			REQUESTED_COLUMN=column;
			returnValue = OK;
		} else {
			returnValue = NOK;
		}
		return returnValue;

}
/***********************************************************************************************/
ERROR_STATUS HCLCD_moveCursorDoneApp(notify_t appFunction){

	ERROR_STATUS returnValue;

	if(appFunction != NULL){
			MOVE_CURSOR_DONE_NOTIFICATION=appFunction;
			returnValue=OK;
		}
		else{
			returnValue=NOK;
		}
		return returnValue;
}
/***********************************************************************************************/

/****************************************Static functions **************************************/

/***********************************************************************************************/
static u8 HCLCD_initProcess(void) {

	static u8 currentInitState = FUNCTION_SET_COMMAND;
	static u8 counter = 0;
	u8 iterator;
	u8 pinValue;
	u8 returnValue = NOK;

	if (counter >= 20) {
		switch (currentInitState) {
		case FUNCTION_SET_COMMAND:
			if (MGPIO_ReadPin(CLCD_E_PORT, CLCD_E)) {
				/*CLCD_E =0*/
				MGPIO_writePin(CLCD_E_PORT, CLCD_E, PIN_RESET);
				currentInitState = DISPLAY_ON_OFF_COMMAND;
			} else {
				/*FUNCTION_SET_COMMAND actions
				 1. Set RS and RW to zero
				 2. Write Function Set configuration*/

				MGPIO_writePin(CLCD_RS_PORT, CLCD_RS, PIN_RESET);
				MGPIO_writePin(CLCD_RW_PORT, CLCD_RW, PIN_RESET);


				for (iterator = 0; iterator < MAX_DATA_BITS; iterator++) {
					pinValue=(FUNCTION_SET_CONFIGURATION >>iterator) & 0x01;
					MGPIO_writePin(CLCD_DATA_PORTS[iterator], CLCD_DATA_PINS[iterator],pinValue);
				}

				/*Let CLCD_E = 1*/
				MGPIO_writePin(CLCD_E_PORT, CLCD_E, PIN_SET);
			}
			break;
		case DISPLAY_ON_OFF_COMMAND:
			/*If CLCD_E == 1*/
			if (MGPIO_ReadPin(CLCD_E_PORT, CLCD_E)) {
				/*CLCD_E =0*/
				MGPIO_writePin(CLCD_E_PORT, CLCD_E, PIN_RESET);
				currentInitState = DISPLAY_CLEAR_COMMAND;
			} else {
				/*Display On/Off COMMAND actions
				 1. Set RS and RW to zero
				 2. Write ON/OFF configuration*/

				MGPIO_writePin(CLCD_RS_PORT, CLCD_RS, PIN_RESET);
				MGPIO_writePin(CLCD_RS_PORT, CLCD_RW, PIN_RESET);

				/*ON/OFF configuration*/
				for (iterator = 0; iterator < MAX_DATA_BITS; iterator++) {
					pinValue= (DISPLAY_ON_OFF_CONFIGURATION >> iterator) &0x01;
					MGPIO_writePin(CLCD_DATA_PORTS[iterator], CLCD_DATA_PINS[iterator],	pinValue);
				}

				//MGPIO_writePort(CLCD_PORT,CLCD_DATA_PINS,DISPLAY_ON_OFF_CONFIGURATION);
				/*Let CLCD_E = 1*/
				MGPIO_writePin(CLCD_E_PORT, CLCD_E, PIN_SET);
			}
			break;
		case DISPLAY_CLEAR_COMMAND:
			/*If CLCD_E == 1*/
			if (MGPIO_ReadPin(CLCD_E_PORT, CLCD_E)) {
				/*CLCD_E =0*/
				MGPIO_writePin(CLCD_E_PORT, CLCD_E, PIN_RESET);
				INIT_COMPLETED_FLAG = 1;
			} else {
				/*DISPLAY_CLEAR_COMMAND actions
				 1. Set RS and RW to zero
				 2. Write Clear configuration*/

				MGPIO_writePin(CLCD_RS_PORT, CLCD_RS, PIN_RESET);
				MGPIO_writePin(CLCD_RW_PORT, CLCD_RW, PIN_RESET);

				for (iterator = 0; iterator < MAX_DATA_BITS; iterator++) {
					pinValue = (DISPLAY_CLEAR >> iterator)
							& 0x01;
					MGPIO_writePin(CLCD_DATA_PORTS[iterator], CLCD_DATA_PINS[iterator],
							pinValue);
				}

				/*Let CLCD_E = 1*/
				MGPIO_writePin(CLCD_E_PORT, CLCD_E, PIN_SET);
			}
			break;
		}
	} else {
		counter++;
	}

	return returnValue;
}
/***********************************************************************************************/
static void HCLCD_writeStringProcess(void) {

	/*******************************************************************************************
	 * Write process steps:
	 *                  1.Set RS to 1.
	 *                  2.Set RW to 0.
	 *                  3.write data.
	 *                  4. EnablePulse.
	 * *****************************************************************************************/
	static u8 currentChar = 0;
	u8 index;
	u8 pinValue;

	/*If CLCD_E == 1*/
	if (MGPIO_ReadPin(CLCD_E_PORT, CLCD_E)) {
		/*CLCD_E =0*/
		MGPIO_writePin(CLCD_E_PORT, CLCD_E, PIN_RESET);
	} else {
		if (lenght == currentChar) {
			CURRENT_PROCESS = IDEL_PROCESS;
			currentChar = 0;
			WRITE_DONE_NOTIFICATION();
		} else {
			MGPIO_writePin(CLCD_RS_PORT, CLCD_RS, PIN_SET);
			MGPIO_writePin(CLCD_RS_PORT, CLCD_RW, PIN_RESET);


			for (index = 0; index < 8; index++) {
				pinValue = (word[currentChar] >> index) & 0x01;
				MGPIO_writePin(CLCD_DATA_PORTS[index], CLCD_DATA_PINS[index],
						pinValue);
			}
			/*Let CLCD_E = 1*/
			MGPIO_writePin(CLCD_E_PORT, CLCD_E, PIN_SET);
			currentChar++;
		}

	}
}


/***********************************************************************************************/
static void HCLCD_clearProcess(void) {
	u8 pinValue;
	u8 iterator;
	/*If CLCD_E == 1*/
	if (MGPIO_ReadPin(CLCD_E_PORT, CLCD_E)) {
		/*CLCD_E =0*/
		MGPIO_writePin(CLCD_E_PORT,CLCD_E,PIN_RESET);
		CURRENT_PROCESS = IDEL_PROCESS;
		CLEAR_DONE_NOTIFICATION();
	} else {
		/*DISPLAY_CLEAR_COMMAND actions
		 1. Set RS and RW to zero
		 2. Write Clear configuration*/
		MGPIO_writePin(CLCD_RS_PORT, CLCD_RS, PIN_RESET);
		MGPIO_writePin(CLCD_RW_PORT, CLCD_RW, PIN_RESET);

		/*Clear configuration*/
		for (iterator = 0; iterator < MAX_DATA_BITS; iterator++) {
			pinValue = (DISPLAY_CLEAR >> iterator) & 0x01;
			MGPIO_writePin(CLCD_DATA_PORTS[iterator], CLCD_DATA_PINS[iterator],
					pinValue);
						}

		/*Let CLCD_E = 1*/
		MGPIO_writePin(CLCD_E_PORT, CLCD_E, PIN_SET);
	}
}

/***********************************************************************************************/
static void HCLCD_moveCursorProcess(void){
	u8 location = REQUESTED_ROW + REQUESTED_COLUMN;
	u8 index;
	u8 pinValue;

	/*If CLCD_E == 1*/
	if (MGPIO_ReadPin(CLCD_E_PORT, CLCD_E)) {
		/*CLCD_E =0*/
		MGPIO_writePin(CLCD_E_PORT, CLCD_E, PIN_RESET);
		CURRENT_PROCESS = IDEL_PROCESS;
		MOVE_CURSOR_DONE_NOTIFICATION();
	} else {
		/*Set RS and RW to 0 */
		MGPIO_writePin(CLCD_RS_PORT, CLCD_RS, PIN_RESET);
		MGPIO_writePin(CLCD_RW_PORT, CLCD_RW, PIN_RESET);

		for (index = 0; index < 8; index++) {
			pinValue = (location >> index) & 0x01;
			MGPIO_writePin(CLCD_DATA_PORTS[index], CLCD_DATA_PINS[index], pinValue);

		}
		/*Let CLCD_E = 1*/
		MGPIO_writePin(CLCD_E_PORT, CLCD_E, PIN_SET);
	}
}
/***********************************************************************************************/



/****************************************LCD Runnable********************************************/
void HCLCD_task(void) {
	if (INIT_COMPLETED_FLAG) {
		switch (CURRENT_PROCESS) {
		case IDEL_PROCESS:
			break;
		case WRITE_STRING_PROCESS:
			HCLCD_writeStringProcess();
			break;
		case CLEAR_PROCESS:
			HCLCD_clearProcess();
			break;
		case MOVE_CURSOR_PROCESS:
			HCLCD_moveCursorProcess();
			break;
		}
	} else {
		HCLCD_initProcess();
	}

}

/***********************************************************************************************/


























