/*
 * HCLCD_config.h
 *
 *  Created on: 25 Mar 2020
 *      Author: Basma Abdelhakim
 */

#ifndef HCLCD_CONFIG_H_
#define HCLCD_CONFIG_H_

#define CLCD_RS_PORT     PORTA
#define CLCD_RS         GPIO_Pin0

#define CLCD_RW_PORT     PORTA
#define CLCD_RW          GPIO_Pin1

#define CLCD_E_PORT     PORTA
#define CLCD_E           GPIO_Pin2

#define CLCD_D0_PORT     PORTA
#define CLCD_D0          GPIO_Pin3

#define CLCD_D1_PORT     PORTA
#define CLCD_D1          GPIO_Pin4

#define CLCD_D2_PORT     PORTA
#define CLCD_D2          GPIO_Pin5

#define CLCD_D3_PORT     PORTA
#define CLCD_D3          GPIO_Pin6

#define CLCD_D4_PORT     PORTA
#define CLCD_D4          GPIO_Pin7

#define CLCD_D5_PORT      PORTA
#define CLCD_D5          GPIO_Pin8

#define CLCD_D6_PORT     PORTA
#define CLCD_D6          GPIO_Pin9

#define CLCD_D7_PORT     PORTA
#define CLCD_D7          GPIO_Pin10


#define CLCD_BITS_MODE         CLCD_8_BITS_MODE
#define CLCD_LINES_DISPLAYED   CLCD_2_LINES_DISPLAY
#define CLCD_CHARACTER_FONT    DOT_CHARACTER_FONT_5_x_7


#define CLCLD_DIAPLY_MODE   DISPLAY_ON
#define CLCD_CURSOR_MODE    CURSOR_OFF
#define CLCD_BLINK_MODE     BLINK_OFF
#endif /* HCLCD_CONFIG_H_ */
