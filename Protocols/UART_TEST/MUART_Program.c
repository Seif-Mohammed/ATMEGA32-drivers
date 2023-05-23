#include "BIT_MATH.h"
#include "STDTYPE.h"
#include "MDIO_Interface.h"
#include "MUART_Config.h"
#include "MUART_Interface.h"
#include "MUART_Private.h"

static void (*MUART_PF_Notification)(void) = STD_TYPE_NULL;
static void *MUART_Pu8TxString = STD_TYPE_NULL;
u8 MUART_voidInit(void){
	u8 Copy_UCSRC = 0b10000000;
	u16 Copy_UBRR = 51;
	/*Normal speed divisor =16 not 8*/
	CLEAR_BIT(MUART__U8_UCSRA_REG , 1);
	/*Enable Tx,Rx*/
	SET_BIT(MUART__U8_UCSRB_REG , 3);
	SET_BIT(MUART__U8_UCSRB_REG , 4);
	/*Set data bit size ==>8bits*/
	CLEAR_BIT(MUART__U8_UCSRB_REG , 2);
	SET_BIT(Copy_UCSRC , 2);
	SET_BIT(Copy_UCSRC , 1);
	/*Stop bits ==> 2-bits*/
	SET_BIT(Copy_UCSRC , 3);
	/*Set UCSRC register value*/
	MUART__U8_UCSRC_REG = Copy_UCSRC;
	/*Set baud rate*/
	MUART__U8_UBRRL_REG = ( u8)Copy_UBRR;
	MUART__U8_UBRRH_REG = ( u8)(Copy_UBRR>>8);
}

u8 MUART_voidRecieveByte(void){
	while(!GET_BIT(MUART__U8_UCSRA_REG , 7));
	/*Write datat to Tx buffer*/
	return MUART__U8_UDR_REG;
}

u8 MUART_voidSendByte(u8 Copy_u8TxByte){
	while(!GET_BIT(MUART__U8_UCSRA_REG , 5));
	/*Write datat to Tx buffer*/
	MUART__U8_UDR_REG = Copy_u8TxByte;
}
u8 MUART_u8SendString_synch(u8 *Copy_Pu8TxString){
	u8 Local_errprState=STD_TYPES_OK;
	if(Copy_Pu8TxString != STD_TYPE_NULL){
		while(*Copy_Pu8TxString){
			MUART_voidSendByte(*Copy_Pu8TxString);
			Copy_Pu8TxString++;
		}
	}else{
		Local_errprState = STD_TYPES_NOK;
	}
	return Local_errprState;
}

u8 MUART_u8SendString_Asynch(u8 *Copy_Pu8TxString , void(*Copy_pNotification)(void)){
	u8 Local_errprState=STD_TYPES_OK;
	if(Copy_Pu8TxString != STD_TYPE_NULL && Copy_pNotification !=STD_TYPE_NULL){
		/*update global pointer*/
		MUART_PF_Notification = Copy_pNotification;
		MUART_Pu8TxString = Copy_Pu8TxString;
		/*Enable Data Register Empty Interrupt */
		SET_BIT(MUART__U8_UCSRB_REG , 5);
	}else{
		Local_errprState = STD_TYPES_NOK;
	}
	return Local_errprState;
}

void __vector_14(void)__attribute__((signal));
void __vector_14(void){
	static Local_u8Counter =0;
	MUART_voidSendByte(MUART_Pu8TxString[Local_u8Counter]);
	Local_u8Counter++;
	if(MUART_Pu8TxString[Local_u8Counter] =='\0'){
		/*Disable interrupt*/
		CLEAR_BIT(MUART__U8_UCSRB_REG , 5);
		Local_u8Counter =0;
		MUART_PF_Notification();
	}
}
