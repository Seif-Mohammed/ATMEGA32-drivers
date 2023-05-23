/*LIP Layer*/
#include "STDTYPE.h"
#define  F_CPU 8000000UL
#include <avr/delay.h>
/* MCAL */
#include "MDIO_Interface.h"
/*HAL*/
#include "HKPD_Config.h"
#include "HKPD_Interface.h"
#include "HKPD_Private.h"

u8 HKPD_Au8RowPins[4] = {HKPD_U8_R0_PIN , HKPD_U8_R1_PIN , HKPD_U8_R2_PIN , HKPD_U8_R3_PIN};
u8 HKPD_Au8RowPorts[4] = {HKPD_U8_R0_PORT , HKPD_U8_R1_PORT , HKPD_U8_R2_PORT , HKPD_U8_R3_PORT};
u8 HKPD_Au8ColPins[4] = {HKPD_U8_C0_PIN , HKPD_U8_C1_PIN , HKPD_U8_C2_PIN , HKPD_U8_C3_PIN};
u8 HKPD_Au8ColPorts[4] = {HKPD_U8_C0_PORT , HKPD_U8_C1_PORT , HKPD_U8_C2_PORT , HKPD_U8_C3_PORT};
u8 HKPD_Au8Keys[4][4] = HKPD_Au8Key;
u8 HKPD_U8GetKey(u8 * Copy_pu8ReturnedKey){
	u8 Local_u8ErrorState = STD_TYPES_OK;
	u8 Local_u8RowCounter;
	u8 Local_u8RColCounter;
	u8 Local_u8PinValue;
	u8 Local_u8Flag =0;
	if(Copy_pu8ReturnedKey != STD_TYPE_NULL){
		*Copy_pu8ReturnedKey = HKPD_u8_NoKeyPressed;
		for(Local_u8RowCounter=0 ; Local_u8RowCounter <=3 ; Local_u8RowCounter++){
			MDIO_u8SetPinValue(HKPD_Au8RowPorts[Local_u8RowCounter] , HKPD_Au8ColPins[Local_u8RowCounter] , MDIO_U8_LOW);
			for(Local_u8RColCounter = 0 ; Local_u8RColCounter <=3 ; Local_u8RColCounter++){
				MDIO_u8GetPinValue(HKPD_Au8ColPorts[Local_u8RColCounter] , HKPD_Au8ColPins[Local_u8RColCounter] , &Local_u8PinValue);
				if(Local_u8PinValue == MDIO_U8_LOW){
					_delay_ms(20);
					while(Local_u8PinValue == MDIO_U8_LOW){
						MDIO_u8GetPinValue(HKPD_Au8ColPorts[Local_u8RColCounter] , HKPD_Au8ColPins[Local_u8RColCounter] , &Local_u8PinValue);
					}
					* Copy_pu8ReturnedKey = HKPD_Au8Keys[Local_u8RowCounter][Local_u8RColCounter];
					Local_u8Flag =1;
					break;
				}
			}
			MDIO_u8SetPinValue(HKPD_Au8RowPorts[Local_u8RowCounter] , HKPD_Au8ColPins[Local_u8RowCounter] , MDIO_U8_HIGH);
			if(Local_u8Flag ==1)
				break;
		}
	}else{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}
