/*LIB LAYER*/
#include "STDTYPE.h"
#include "BIT_MATH.h"
/* MCAL */
#include "MDIO_Interface.h"
#include "MDIO_Private.h"
#include "MDIO_Config.h"
/*Function implementation*/
u8 MDIO_u8SetPinDirection(u8 Copy_u8PortID , u8 Copy_u8PinID , u8 Copy_u8PinDirection){
	u8 Local_u8ErrorState =0;
	if((Copy_u8PinID <= MDIO_U8_PIN_7) && (Copy_u8PortID <= MDIO_U8_PORTD)){
		Local_u8ErrorState =1;
		switch (Copy_u8PinDirection){
		case(MDIO_U8_OUTPUT):
			switch(Copy_u8PortID){
			case(MDIO_U8_PORTA):SET_BIT(MDIO_U8_DDRA,Copy_u8PinID);break;
			case(MDIO_U8_PORTB):SET_BIT(MDIO_U8_DDRB,Copy_u8PinID);break;
			case(MDIO_U8_PORTC):SET_BIT(MDIO_U8_DDRC,Copy_u8PinID);break;
			case(MDIO_U8_PORTD):SET_BIT(MDIO_U8_DDRD,Copy_u8PinID);break;
			}break;
		case(MDIO_U8_INPUT_PULLED_UP):
			switch(Copy_u8PortID){
			case(MDIO_U8_PORTA):CLEAR_BIT(MDIO_U8_DDRA,Copy_u8PinID);SET_BIT(MDIO_U8_PORTA_REG,Copy_u8PinID);break;
			case(MDIO_U8_PORTB):CLEAR_BIT(MDIO_U8_DDRB,Copy_u8PinID);SET_BIT(MDIO_U8_PORTB_REG,Copy_u8PinID);break;
			case(MDIO_U8_PORTC):CLEAR_BIT(MDIO_U8_DDRC,Copy_u8PinID);SET_BIT(MDIO_U8_PORTC_REG,Copy_u8PinID);break;
			case(MDIO_U8_PORTD):CLEAR_BIT(MDIO_U8_DDRD,Copy_u8PinID);SET_BIT(MDIO_U8_PORTD_REG,Copy_u8PinID);break;
			}break;
		case(MDIO_U8_INPUT_FLOATING):
			switch(Copy_u8PortID){
			case(MDIO_U8_PORTA):CLEAR_BIT(MDIO_U8_DDRA,Copy_u8PinID);break;
			case(MDIO_U8_PORTB):CLEAR_BIT(MDIO_U8_DDRB,Copy_u8PinID);break;
			case(MDIO_U8_PORTC):CLEAR_BIT(MDIO_U8_DDRC,Copy_u8PinID);break;
			case(MDIO_U8_PORTD):CLEAR_BIT(MDIO_U8_DDRD,Copy_u8PinID);break;
			}break;
		default:Local_u8ErrorState=STD_TYPES_NOK;
		}

	}
	return Local_u8ErrorState;
}
u8 MDIO_u8SetPinValue(u8 Copy_u8PortID , u8 Copy_u8PinID , u8 Copy_u8PinValue){
	u8 Local_u8ErrorState;
	if((Copy_u8PinID <= MDIO_U8_PIN_7) && (Copy_u8PortID <= MDIO_U8_PORTD)){
		Local_u8ErrorState = 1;
		switch (Copy_u8PinValue){
		case(MDIO_U8_HIGH):
			switch(Copy_u8PortID){
			case(MDIO_U8_PORTA):SET_BIT(MDIO_U8_PORTA_REG,Copy_u8PinID);break;
			case(MDIO_U8_PORTB):SET_BIT(MDIO_U8_PORTB_REG,Copy_u8PinID);break;
			case(MDIO_U8_PORTC):SET_BIT(MDIO_U8_PORTC_REG,Copy_u8PinID);break;
			case(MDIO_U8_PORTD):SET_BIT(MDIO_U8_PORTD_REG,Copy_u8PinID);break;
			}
			break;
		case(MDIO_U8_LOW):
			switch(Copy_u8PortID){
			case(MDIO_U8_PORTA):CLEAR_BIT(MDIO_U8_PORTA_REG,Copy_u8PinID);break;
			case(MDIO_U8_PORTB):CLEAR_BIT(MDIO_U8_PORTB_REG,Copy_u8PinID);break;
			case(MDIO_U8_PORTC):CLEAR_BIT(MDIO_U8_PORTC_REG,Copy_u8PinID);break;
			case(MDIO_U8_PORTD):CLEAR_BIT(MDIO_U8_PORTD_REG,Copy_u8PinID);break;
			}
			break;
		default:Local_u8ErrorState=STD_TYPES_NOK;
		}
	}
	return Local_u8ErrorState;
}
u8 MDIO_u8GetPinValue(u8 Copy_u8PortID , u8 Copy_u8PinID , u8 * Copy_Pu8PinValue){
	u8 Local_u8ErrorState;
	if((Copy_u8PinID <= MDIO_U8_PIN_7) && (Copy_u8PortID <= MDIO_U8_PORTD) && (Copy_Pu8PinValue != STD_TYPE_NULL)){
		Local_u8ErrorState = 1;
		switch(Copy_u8PortID){
		case(MDIO_U8_PORTA):(* Copy_Pu8PinValue )= GET_BIT(MDIO_U8_PINA,Copy_u8PinID);break;
		case(MDIO_U8_PORTB):(* Copy_Pu8PinValue )= GET_BIT(MDIO_U8_PINB,Copy_u8PinID);break;
		case(MDIO_U8_PORTC):(* Copy_Pu8PinValue )= GET_BIT(MDIO_U8_PINC,Copy_u8PinID);break;
		case(MDIO_U8_PORTD):(* Copy_Pu8PinValue )= GET_BIT(MDIO_U8_PIND,Copy_u8PinID);break;
		}
	}
	return Local_u8ErrorState;
}
u8 MDIO_u8GetPortDirection(u8 Copy_u8PortID ,  u8 Copy_u8PortDirection){
	u8 Local_u8ErrorState = STD_TYPES_NOK;
	if(Copy_u8PortID <= MDIO_U8_PORTD){
		Local_u8ErrorState = STD_TYPES_OK;
		switch(Copy_u8PortDirection){
		case(MDIO_U8_OUTPUT):
			switch(Copy_u8PortID){
			case(MDIO_U8_PORTA):MDIO_U8_DDRA = 0xFF;break;
			case(MDIO_U8_PORTB):MDIO_U8_DDRB = 0xFF;break;
			case(MDIO_U8_PORTC):MDIO_U8_DDRC = 0xFF;break;
			case(MDIO_U8_PORTD):MDIO_U8_DDRD = 0xFF;break;
			}
			break;
		case(MDIO_U8_INPUT_FLOATING):
			switch(Copy_u8PortID){
			case(MDIO_U8_PORTA):MDIO_U8_DDRA = 0x00;break;
			case(MDIO_U8_PORTB):MDIO_U8_DDRB = 0x00;break;
			case(MDIO_U8_PORTC):MDIO_U8_DDRC = 0x00;break;
			case(MDIO_U8_PORTD):MDIO_U8_DDRD = 0x00;break;
			}
		break;
		case(MDIO_U8_INPUT_PULLED_UP):
			switch(Copy_u8PortID){
			case(MDIO_U8_PORTA):MDIO_U8_DDRA = 0x00;MDIO_U8_PORTA_REG = 0xFF;break;
			case(MDIO_U8_PORTB):MDIO_U8_DDRB = 0x00;MDIO_U8_PORTB_REG = 0xFF;break;
			case(MDIO_U8_PORTC):MDIO_U8_DDRC = 0x00;MDIO_U8_PORTC_REG = 0xFF;break;
			case(MDIO_U8_PORTD):MDIO_U8_DDRD = 0x00;MDIO_U8_PORTD_REG = 0xFF;break;
			}
		break;
		default:Local_u8ErrorState= STD_TYPES_NOK;
		}
	}
	return Local_u8ErrorState;
}
u8 MDIO_u8SetPortValue(u8 Copy_u8PortID  , u8 Copy_u8PortValue){
	u8 Local_u8ErrorState= STD_TYPES_NOK;
	if(Copy_u8PortID <= MDIO_U8_PORTD){
		Local_u8ErrorState = STD_TYPES_OK;
		switch(Copy_u8PortID){
		case(MDIO_U8_PORTA):MDIO_U8_PORTA_REG = Copy_u8PortValue;break;
		case(MDIO_U8_PORTB):MDIO_U8_PORTB_REG = Copy_u8PortValue;break;
		case(MDIO_U8_PORTC):MDIO_U8_PORTC_REG = Copy_u8PortValue;break;
		case(MDIO_U8_PORTD):MDIO_U8_PORTD_REG = Copy_u8PortValue;break;
		}
	}
	return Local_u8ErrorState;
}
u8 MDIO_u8GetPortValue(u8 Copy_u8PortID , u8 * Copy_u8PortValue){
	u8 Local_u8ErrorState= STD_TYPES_NOK;
	if((Copy_u8PortID <= MDIO_U8_PORTD) && (Copy_u8PortValue != STD_TYPE_NULL)){
		Local_u8ErrorState = STD_TYPES_OK;
		switch(Copy_u8PortID){
		case(MDIO_U8_PORTA): * Copy_u8PortValue = MDIO_U8_PINA;break;
		case(MDIO_U8_PORTB): * Copy_u8PortValue = MDIO_U8_PINB;break;
		case(MDIO_U8_PORTC): * Copy_u8PortValue = MDIO_U8_PINC;break;
		case(MDIO_U8_PORTD): * Copy_u8PortValue = MDIO_U8_PIND;break;
		}
	}
	return Local_u8ErrorState;
}
u8 MDIO_U8INIT(void){
	/*PORT DIRECTIONS*/
	MDIO_U8_DDRA = PRIVATE_U8_CONC(MDIO_u8_PA7_DIRECTION , MDIO_u8_PA6_DIRECTION , MDIO_u8_PA5_DIRECTION , MDIO_u8_PA4_DIRECTION , MDIO_u8_PA3_DIRECTION, MDIO_u8_PA2_DIRECTION, MDIO_u8_PA1_DIRECTION ,MDIO_u8_PA0_DIRECTION);
	MDIO_U8_DDRB = PRIVATE_U8_CONC(MDIO_u8_PB7_DIRECTION , MDIO_u8_PB6_DIRECTION , MDIO_u8_PB5_DIRECTION , MDIO_u8_PB4_DIRECTION , MDIO_u8_PB3_DIRECTION, MDIO_u8_PB2_DIRECTION, MDIO_u8_PB1_DIRECTION ,MDIO_u8_PB0_DIRECTION);
	MDIO_U8_DDRC = PRIVATE_U8_CONC(MDIO_u8_PC7_DIRECTION , MDIO_u8_PC6_DIRECTION , MDIO_u8_PC5_DIRECTION , MDIO_u8_PC4_DIRECTION , MDIO_u8_PC3_DIRECTION, MDIO_u8_PC2_DIRECTION, MDIO_u8_PC1_DIRECTION ,MDIO_u8_PC0_DIRECTION);
	MDIO_U8_DDRD = PRIVATE_U8_CONC(MDIO_u8_PD7_DIRECTION , MDIO_u8_PD6_DIRECTION , MDIO_u8_PD5_DIRECTION , MDIO_u8_PD4_DIRECTION , MDIO_u8_PD3_DIRECTION, MDIO_u8_PD2_DIRECTION, MDIO_u8_PD1_DIRECTION ,MDIO_u8_PD0_DIRECTION);
	/*PORT VALUES*/
	MDIO_U8_PORTA_REG = PRIVATE_U8_CONC(MDIO_u8_PA7_VALUE , MDIO_u8_PA6_VALUE , MDIO_u8_PA5_VALUE , MDIO_u8_PA4_VALUE , MDIO_u8_PA3_VALUE , MDIO_u8_PA2_VALUE , MDIO_u8_PA1_VALUE , MDIO_u8_PA0_VALUE);
	MDIO_U8_PORTB_REG = PRIVATE_U8_CONC(MDIO_u8_PB7_VALUE , MDIO_u8_PB6_VALUE , MDIO_u8_PB5_VALUE , MDIO_u8_PB4_VALUE , MDIO_u8_PB3_VALUE , MDIO_u8_PB2_VALUE , MDIO_u8_PB1_VALUE , MDIO_u8_PB0_VALUE);
	MDIO_U8_PORTC_REG = PRIVATE_U8_CONC(MDIO_u8_PC7_VALUE , MDIO_u8_PC6_VALUE , MDIO_u8_PC5_VALUE , MDIO_u8_PC4_VALUE , MDIO_u8_PC3_VALUE , MDIO_u8_PC2_VALUE , MDIO_u8_PC1_VALUE , MDIO_u8_PC0_VALUE);
	MDIO_U8_PORTD_REG = PRIVATE_U8_CONC(MDIO_u8_PD7_VALUE , MDIO_u8_PD6_VALUE , MDIO_u8_PD5_VALUE , MDIO_u8_PD4_VALUE , MDIO_u8_PD3_VALUE , MDIO_u8_PD2_VALUE , MDIO_u8_PD1_VALUE , MDIO_u8_PD0_VALUE);
}

