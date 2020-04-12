/*************************************************************************************************
 * DIO_interface.h
 *      Author: Basma Abdelhakim
 ************************************************************************************************/

#define PORTA_BASE_ADDRESS    0x40010800
#define PORTB_BASE_ADDRESS    0x40010C00
#define PORTC_BASE_ADDRESS    0x40011000

#define PORTA  ((volatile GPIO_t*) PORTA_BASE_ADDRESS )
#define PORTB  ((volatile GPIO_t*) PORTB_BASE_ADDRESS )
#define PORTC  ((volatile GPIO_t*) PORTC_BASE_ADDRESS )

typedef struct {
	u32 CRL;
	u32 CRH;
	u32 IDR;
	u32 ODR;
	u32 BSRR;
	u32 BRR;
	u32 LCKR;
} GPIO_t;

typedef struct {
	volatile GPIO_t * GPIO_Port;
	u16 pin;
	u8 mode;
	u8 Speed;
	u8 state;
} PinConfig_t;

/***********************************GPIO pins options********************************************/
#define GPIO_Pin0     ((u16)0x0001)
#define GPIO_Pin1     ((u16)0x0002)
#define GPIO_Pin2     ((u16)0x0004)
#define GPIO_Pin3     ((u16)0x0008)
#define GPIO_Pin4     ((u16)0x0010)
#define GPIO_Pin5     ((u16)0x0020)
#define GPIO_Pin6     ((u16)0x0040)
#define GPIO_Pin7     ((u16)0x0080)
#define GPIO_Pin8     ((u16)0x0100)
#define GPIO_Pin9     ((u16)0x0200)
#define GPIO_Pin10    ((u16)0x0400)
#define GPIO_Pin11    ((u16)0x0800)
#define GPIO_Pin12    ((u16)0x1000)
#define GPIO_Pin13    ((u16)0x2000)
#define GPIO_Pin14    ((u16)0x4000)
#define GPIO_Pin15    ((u16)0x8000)
#define GPIO_PinAll   ((u16)0xFFFF)
/************************************************************************************************/

/********************************Output configuration options************************************/
#define  OUTPUT_OPEN_DRAIN    0x14
#define  OUTPUT_PUSHPULL      0x10
#define  OUTPUT_AF_PUSHPULL   0x18
#define  OUTPUT_AF_OpenDrain  0x1C
/************************************************************************************************/

/*********************************Input configuration options************************************/
#define INPUT_ANALOG     0x00
#define INPUT_FLOATING   0x04
#define INPUT_PULLDOWN   0x28
#define INPUT_PULLUP     0x48
/************************************************************************************************/

/******************************Output speed configuration options********************************/
#define SPEED_2MHZ   0x2
#define SPEED_10MHZ  0x1
#define SPEED_50MHZ  0x3
/************************************************************************************************/

/***********************************Pins status options********* ********************************/
#define PIN_SET      1U
#define PIN_RESET    0U
/************************************************************************************************/


/************************************Functions prototypes****** *********************************/

/***********************************************************************************************
 * Description:
 *        This function is used to configure one or multiples pins in the same port with
 *              the same configuration.
 *        To configure pins in different ports or with different configuration,the function is
 *            called more than one time.
 *Inputs:
 *      GPIO_configuration field : It is of type PinConfig_t which is previously defined
 *              It takes the following fields as parameters:
 *
 *                 1.GPIO_configuration->GPIO_Port
 *                       It can take the following options:
 *                            1.PORTA
 *                            2.PORTB
 *                            3.PORTC
 *
 *                 2.GPIO_configuration->pin
 *                        It can take any of the GPIO pins options previously defined.
 *
 *                 3.GPIO_configuration->mode
 *                        It can take any of the output or input mode options previously defined.
 *
 *                 4.GPIO_configuration->speed
 *                       In case of output configuration it can take any of the speed
 *                       options previously defined.
 * Outputs:
 *       It returns in case of correct execution   OK
 *       It returns in case of incorrect execution NOT_OK
 ***********************************************************************************************/
u8 MGPIO_ConfigurePinsMode(PinConfig_t * GPIO_configuration);


/***********************************************************************************************
 * Description:
 *         This function is used to write value to the selected pin.
 * Inputs:
 *   GPIO_Port filed : It is of type GPIO_t which is previously defined .
 *                     It can take the following options:
 *                       1.PORTA
 *                       2.PORTB
 *                       3.PORTC
 *  pin filed:It can take any of the GPIO pins options previously defined.
 *  pinstate field:It can take the following options:
 *                     1.PIN_SET
 *                     2.PIN_RESET
 *  Outputs:
 *       It returns in case of correct execution   OK
 *       It returns in case of incorrect execution NOT_OK
 * *********************************************************************************************/

u8 MGPIO_writePin(volatile GPIO_t * GPIO_Port,u16 pin ,u8 pinstate);



/***********************************************************************************************
 * Description:
 *         This function is used to read the  value of  the selected pin.
 * Inputs:
 *   GPIO_Port filed : It is of type GPIO_t which is previously defined .
 *                     It can take the following options:
 *                       1.PORTA
 *                       2.PORTB
 *                       3.PORTC
 *  pin filed:It can take any of the GPIO pins options previously defined.
 *
 *  Outputs:
 *       It returns the read pin value as:
 *          1.PIN_SET
 *          2.PIN_RESET
 * *********************************************************************************************/
u8 MGPIO_ReadPin(volatile GPIO_t * GPIO_Port,u16 pin);



