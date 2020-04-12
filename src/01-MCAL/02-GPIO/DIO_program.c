/*************************************************************************************************
 * DIO_interface.h
 *      Author: Basma Abdelhakim
 ************************************************************************************************/


#include "../../03-LIB/STD_TYPES.h"
#include "DIO_interface.h"


/************************************Functions prototypes****** *********************************/

/************************************************************************************************/
u8 MGPIO_ConfigurePinsMode(PinConfig_t * GPIO_configuration) {
	
    u32 Local_u32Iterator;
	u32 Local_u32CurrentMode;
	u32 Local_u32TempRegister;
	u32 Local_u32PinPosition;
	u8  Local_u8returnValue=OK;

	Local_u32CurrentMode = ((u32) GPIO_configuration->mode) & ((u32) 0x0F);

	/*Check if configuration is output or input,
	 * And in case of output configuration add speed value*/
	if ((((u32) (GPIO_configuration->mode)) & ((u32) 0x10)) != ((u32) 0x00)) {
		Local_u32CurrentMode |= ((u32) GPIO_configuration->Speed);
	}

	/*Check if the pin in CRL Register*/
	if ((((u32) (GPIO_configuration->pin)) & ((u32) 0x00FF)) != ((u32) 0x00)) {
		Local_u32TempRegister = GPIO_configuration->GPIO_Port->CRL;
		for (Local_u32Iterator = 0x00; Local_u32Iterator < 0x08;
				Local_u32Iterator++) {
			if ((GPIO_configuration->pin) & (1 << Local_u32Iterator)) {

				Local_u32PinPosition = Local_u32Iterator << 2;
				/*clear corresponding pin bits in register*/
				Local_u32TempRegister &= ~(((u32) 0x0F)
						<< Local_u32PinPosition);
				/*Set corresponding pin bits in register with current mode*/
				Local_u32TempRegister |= (Local_u32CurrentMode
						<< Local_u32PinPosition);
            
				/*In case of input pull up configuration
				 * corresponding pin in ODR register is set to 1*/
				if (GPIO_configuration->mode == INPUT_PULLUP) {
					GPIO_configuration->GPIO_Port->BSRR = (((u32) 0x01) << Local_u32Iterator);
				}

				/*In case of input pull Down configuration
				 * corresponding pin in ODR register is set to 0*/
				else if (GPIO_configuration->mode == INPUT_PULLDOWN) {
					GPIO_configuration->GPIO_Port->BRR = (((u32) 0x01) << Local_u32Iterator);
				}
        
			}
		}
		GPIO_configuration->GPIO_Port->CRL = Local_u32TempRegister;

	} if((((u32) (GPIO_configuration->pin)) & ((u32) 0xFF00)) != ((u32) 0x00)) {
		Local_u32TempRegister = GPIO_configuration->GPIO_Port->CRH;
		for (Local_u32Iterator = 0x00; Local_u32Iterator < 0x08;
				Local_u32Iterator++) {
			if ((GPIO_configuration->pin) & (1 << (Local_u32Iterator + 0x08))) {

				Local_u32PinPosition = Local_u32Iterator << 2;
				/*Clear corresponding pin position*/
				Local_u32TempRegister &=
						~(((u32) 0x0F) << Local_u32PinPosition);
				/*set corresponding pin configuration */
				Local_u32TempRegister |= (Local_u32CurrentMode
						<< Local_u32PinPosition);

				/*In case of input pull up configuration
				 * corresponding pin in ODR register is set to 1*/
				if (GPIO_configuration->mode == INPUT_PULLUP) {
					GPIO_configuration->GPIO_Port->BSRR = (((u32) 0x01)
							<< (Local_u32Iterator + 0x08));
				}

				/*In case of input pull Down configuration
				 * corresponding pin in ODR register is set to 0*/
				else if (GPIO_configuration->mode == INPUT_PULLDOWN) {
					GPIO_configuration->GPIO_Port->BRR = (((u32) 0x01)
							<< (Local_u32Iterator + 0x08));
				}

			}
		}
		GPIO_configuration->GPIO_Port->CRH = Local_u32TempRegister;

	}
    return Local_u8returnValue;
}
/************************************************************************************************/

u8 MGPIO_writePin(volatile GPIO_t * GPIO_Port, u16 pin, u8 pinState) {
	u8 Local_u8returnValue = OK;
	if (pinState == PIN_SET) {
		GPIO_Port->ODR |= pin;
	} else if (pinState== PIN_RESET) {
		GPIO_Port->ODR &= ~pin;
	} else {
		Local_u8returnValue = NOT_OK;
	}
	return Local_u8returnValue;
}
/************************************************************************************************/

u8 MGPIO_ReadPin(volatile GPIO_t * GPIO_Port, u16 pin){
	u8 Local_u8returnValue;
	u32 Local_u32tempvalue;
	Local_u32tempvalue = (GPIO_Port->IDR & pin);
	if (Local_u32tempvalue != 0) {
		Local_u8returnValue = PIN_SET;
	} else {
		Local_u8returnValue = PIN_RESET;
	}
	return Local_u8returnValue;
}

/************************************************************************************************/


