#include "STDTYPE.h"
#include "MDIO_Interface.h"
#include "HLCD_Interface.h"
#include "HLCD_Private.h"
#include "HLCD_Config.h"
#include <avr/delay.h>
#include <stdio.h>
u8 HLCD_U8Init(void){
	u8 Local_u8ErrorState = STD_TYPES_OK;
	_delay_ms(31);
	/*send function set command*/
	HLCD_U8WriteCommand(0b00111000);
	_delay_us(40);
	/*send display on\off command*/
	HLCD_U8WriteCommand(0b00001111);
	_delay_us(40);
	/*send display CLEAR command*/
	HLCD_U8WriteCommand(0b00000001);
	_delay_ms(2);
	/*send ENTERY MODE SET command*/
	HLCD_U8WriteCommand(0b00000110);
	return Local_u8ErrorState;
}
u8 HLCD_U8WriteChar(u8 Copy_u8Char){
	u8 Local_u8ErrorState = STD_TYPES_OK;
	/*1- set RS high(Data)
	 *2- set RW low to write
	 *3- send command on data pins
	 *4- send pulse to enable(E) pin to let LCD read the data */
	MDIO_u8SetPinValue(HLCD_U8_RS_PORT,HLCD_U8_RS_PIN,MDIO_U8_HIGH);
	MDIO_u8SetPinValue(HLCD_U8_RW_PORT,HLCD_U8_RW_PIN,MDIO_U8_LOW);
	MDIO_u8SetPortValue(HLCD_U8_DATA_PORT,Copy_u8Char);
	MDIO_u8SetPinValue(HLCD_U8_E_PORT,HLCD_U8_E_PIN,MDIO_U8_HIGH);
	_delay_us(1);
	MDIO_u8SetPinValue(HLCD_U8_E_PORT,HLCD_U8_E_PIN,MDIO_U8_LOW);
	return Local_u8ErrorState;
}
u8 HLCD_U8WriteCommand(u8 Copy_u8Cmnd){
	u8 Local_u8ErrorState = STD_TYPES_OK;
	/*1- set RS low(Command)
	 *2- set RW low to write
	 *3- send command on data pins
	 *4- send pulse to enable(E) pin to let LCD read the data */
	MDIO_u8SetPinValue(HLCD_U8_RS_PORT,HLCD_U8_RS_PIN,MDIO_U8_LOW);
	MDIO_u8SetPinValue(HLCD_U8_RW_PORT,HLCD_U8_RW_PIN,MDIO_U8_LOW);
	MDIO_u8SetPortValue(HLCD_U8_DATA_PORT,Copy_u8Cmnd);
	MDIO_u8SetPinValue(HLCD_U8_E_PORT,HLCD_U8_E_PIN,MDIO_U8_HIGH);
	_delay_us(1);
	MDIO_u8SetPinValue(HLCD_U8_E_PORT,HLCD_U8_E_PIN,MDIO_U8_LOW);
	return Local_u8ErrorState;

}
u8 HLCD_U8SetCursor(u8 Copy_u8LineNumber , u8 Copy_u8CharacterNumber){
	u8 Local_u8ErrorState = STD_TYPES_OK;
	HLCD_U8WriteCommand((0x80|(Copy_u8LineNumber<<6))+Copy_u8CharacterNumber);
	return Local_u8ErrorState;
}
void HLCD_U8ClearLCD(void){
	HLCD_U8WriteCommand(0b00000001);
}

void HLCD_U8DrawChar(u8 Copy_u8LineNumber , u8 Copy_u8CharacterNumber , u8 Copy_CharIndex , u8 * Copy_CustomChar){
	HLCD_U8WriteCommand( 0b01000000 + (Copy_CharIndex*8));
	for(u8 i=0 ; i<8 ; i++){
		HLCD_U8WriteChar(Copy_CustomChar[i]);
	}
	/*PUT AC back to DDRAM*/
	HLCD_U8SetCursor(Copy_u8LineNumber,Copy_u8CharacterNumber);
	/*Display drawn chs on LCD*/
	HLCD_U8WriteChar(Copy_CharIndex);
}

u8 HLCD_U8WriteString(u8 * Copy_u8String){

	while(*Copy_u8String){
		HLCD_U8WriteChar(*Copy_u8String);
		Copy_u8String++;
	}
}

u8 HLCD_U8WriteNumber(u8  Copy_u8Number){
	int Local_u8ErrorState = 1;
	int j = Copy_u8Number;
	int i=0;
	do {
		j /= 10;
		++i;
	}

	while (j != 0);
	int arr[i];
	for(j=i-1 ; j>=0 ; j--){
		arr[j] = ((Copy_u8Number) % 10)+48;
		(Copy_u8Number)= (Copy_u8Number)/10;
	}
	for(j=0 ; j<i ; j++){
		HLCD_U8WriteChar(arr[j]);
	}
	return Local_u8ErrorState;
}
