#ifndef MDIO_Private_h
#define MDIO_Private_h
/*PORTA*/
#define MDIO_U8_PORTA_REG	*((volatile u8*)0x3B)
#define MDIO_U8_DDRA  		*((volatile u8*)0x3A)
#define MDIO_U8_PINA  		*((const volatile u8*)0x39)
/* PORTB*/
#define MDIO_U8_PORTB_REG 	*((volatile u8*)0x38)
#define MDIO_U8_DDRB  		*((volatile u8*)0x37)
#define MDIO_U8_PINB  		*((const volatile u8*)0x36)
/*PORTC*/
#define MDIO_U8_PORTC_REG 	*((volatile u8*)0x35)
#define MDIO_U8_DDRC  		*((volatile u8*)0x34)
#define MDIO_U8_PINC  		*((const volatile u8*)0x33)
/*PORTD*/
#define MDIO_U8_PORTD_REG 	*((volatile u8*)0x32)
#define MDIO_U8_DDRD  		*((volatile u8*)0x31)
#define MDIO_U8_PIND  		*((const volatile u8*)0x30)
/*Macros definitions for intial direction and value */
#define  MDIO_U8_INIT_INPUT    			0
#define  MDIO_U8_INIT_OUTPUT 			1
#define  MDIO_U8_INIT_LOW				0
#define  MDIO_U8_INIT_HIGH				1
#define  MDIO_U8_INIT_INPUT_FLOATING	0
#define  MDIO_U8_INIT_INPUT_PULLED_UP	1
/*Concatenation function*/
#define PRIVATE_U8_CONC(X7,X6,X5,X4,X3,X2,X1,X0)		PRIVATE_U8_CONC_HELP(X7,X6,X5,X4,X3,X2,X1,X0)
#define PRIVATE_U8_CONC_HELP(X7,X6,X5,X4,X3,X2,X1,X0) 	0b##X7##X6##X5##X4##X3##X2##X1##X0

#endif
