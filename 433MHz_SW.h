/*
 * 433MHz_SW.h
 *
 * Created: 02.07.2016
 *  Author: Adrian Gerber
 */ 


#ifndef _433MHZ_SW_H_
#define _433MHZ_SW_H_

#define F_CPU 8000000
#include <util/delay.h>
#include <avr/io.h>

#define SW_GPIO_PORT PORTD
#define SW_GPIO_DDR  DDRD
#define SW_GPIO_PIN  PIND
#define SW_GPIO_BIT  PD6

#define SW_GPIO_LOW   (SW_GPIO_PORT) &= ~(1<<(SW_GPIO_BIT))
#define SW_GPIO_HIGH  (SW_GPIO_PORT) |=  (1<<(SW_GPIO_BIT))

#define SW_TRI_0 0x00
#define SW_TRI_1 0x01

#define SW_PULSE_LENGTH_US 350

#define SW_SWITCHSTRING "0FFF0FFFFFFFS"

void SW_Setup(void);

/*Generates signal:*/
/* ___ 1  */
/*| 3 |_ */
void SW_SendBit1(void);

/*Generates signal:*/
/* _  3  */
/*|1|___ */
void SW_SendBit0(void);

/*Generates signal:					*/
/* _				31  			*/
/*|1|_______________________________*/
void SW_SendSync(void);

/*Generates signal:*/
/* _  3  _  3 */
/*|1|___|1|___*/
void SW_Send0(void);

/*Generates signal:*/
/* ___ 1 ___ 1*/
/*| 3 |_| 3 |_*/
void SW_Send1(void);

/*Generates signal:*/
/* _  3  ___ 1 */
/*|1|___| 3 |_ */
void SW_SendF(void);

/*Send a string of "TRI"- Characters*/
void SW_SendTRI(char *str);

/*Send a string of "TRI"- Characters*/
void SW_SendTRIRepeat(char *str, uint8_t repeadCnt);

/*Set the state of a remote switch*/
void SW_SetSwitch(uint8_t addr, uint8_t channel, uint8_t repeatCnt, uint8_t state);

#endif /* 433MHZ_SW_H_ */