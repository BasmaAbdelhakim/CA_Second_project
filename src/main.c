#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

#include "03-LIB/STD_TYPES.h"

#include "01-MCAL/01-RCC/RCC_interface.h"
#include "01-MCAL/02-GPIO/DIO_interface.h"

#include "01-MCAL/03-SYSTIC/SYSTIC_interface.h"
#include "04-OS/Schedular_interface.h"

#include "02-HAL/02-LCD/HCLCD_interface.h"


PinConfig_t led = {PORTA, GPIO_Pin13, SPEED_2MHZ, OUTPUT_PUSHPULL, PIN_SET };
void fun3 (void);
int main(int argc, char* argv[]) {
	RCC_CLK_Select(SW_HSE);
	RCC_EnablePrephiralClock(APB2ENR_BUS, PORTA_Enable);
	RCC_EnablePrephiralClock(APB2ENR_BUS, PORTC_Enable);

	//MGPIO_ConfigurePinsMode(PORTC, &led);
	//MGPIO_writePinValue(PORTC, &led);

	HCLCD_init();

	HCLCD_moveCursorDoneApp(&fun3);
	HCLCD_moveCursorLocation(LINE_2,COLUMN_1);



	schedular_init();
	schedular_start();
	start_OS();
}

void fun3 (void){
	u8 arr [4]={5+48,3+48,4+48,5+48};
	HCLCD_writeString((const u8  *)arr,4);
}
#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
