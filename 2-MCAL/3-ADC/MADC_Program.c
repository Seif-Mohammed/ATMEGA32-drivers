#include "BIT_MATH.h"
#include "STDTYPE.h"
#include "MDIO_Interface.h"
#include "MADC_Interace.h"
#include "MADC_Private.h"
#include "MADC_Config.h"
static void (*MADC_PF_Notification)(u16) = STD_TYPE_NULL;
static u8 busy_flag=MADC_NOTbusy;

void MADC_voidINIT(void){
	/*Select Vref =>AVCC*/
	MADC_U8_ADMUX_REG |= MADC_U8ADC_Vref;
	/*Leftadj OR Rightadj*/
	CLEAR_BIT(MADC_U8_ADMUX_REG , 5);
	/*Single conversion mode or Others*/
	CLEAR_BIT(MADC_U8_ADCSRA_REG , 5);
	/*Prescalar optio for CLK=> 8MHz/64=(125KHz) */
	SET_BIT(MADC_U8_ADCSRA_REG , 2);
	SET_BIT(MADC_U8_ADCSRA_REG , 1);
	CLEAR_BIT(MADC_U8_ADCSRA_REG , 0);
	/*Enable ADC*/
	SET_BIT(MADC_U8_ADCSRA_REG , 7);
}
u8 MADC_U8GetDigitalValueSynch(u8 Copy_u8ChannedNumber , u16 * Copy_pu16_DigitalValue){
	u8 Local_u8ErrorState = STD_TYPES_OK;
	u32 Local_u32TimeoutCounter =0;
	if((busy_flag == MADC_NOTbusy) && (Copy_u8ChannedNumber < 32) && Copy_pu16_DigitalValue !=STD_TYPE_NULL){
		/*Select Channel Number*/
		MADC_U8_ADMUX_REG &= 0B11100000;
		MADC_U8_ADMUX_REG |= Copy_u8ChannedNumber;
		/*Start Conversion*/
		SET_BIT(MADC_U8_ADCSRA_REG , 6);
		/*Wait for the flag to be set*/
		while((GET_BIT(MADC_U8_ADCSRA_REG , 4) == 0) && (Local_u32TimeoutCounter < MADC_U8_MAXTimeOut) ){
			Local_u32TimeoutCounter++;
		}
		if(GET_BIT(MADC_U8_ADCSRA_REG , 4)){
			/*Clear flag*/
			SET_BIT(MADC_U8_ADCSRA_REG,4);
			/*Return result*/
			*Copy_pu16_DigitalValue = MADC_U8_ADC_REG;
		}else{
			Local_u8ErrorState = STD_TYPES_NOK;
		}
	}
	else{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}

u8 MADC_U8GetDigitalValueAsynch(u8 Copy_u8ChannedNumber , void(*Copy_pNotification)(u16)){
	u8 Local_u8ErrorState = STD_TYPES_OK;
	if((busy_flag == MADC_NOTbusy) && (Copy_u8ChannedNumber < 32) && Copy_pNotification !=STD_TYPE_NULL){
		busy_flag = MADC_busy;
		/*Update global pointer to function*/
		MADC_PF_Notification = Copy_pNotification;
		/*Select Channel Number*/
		MADC_U8_ADMUX_REG &= 0B11100000;
		MADC_U8_ADMUX_REG |= Copy_u8ChannedNumber;
		/*Enable Interrup*/
		SET_BIT(MADC_U8_ADCSRA_REG , 3);
		/*Start Conversion*/
		SET_BIT(MADC_U8_ADCSRA_REG , 6);

	}
	else{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}

void __vector_16(void)__attribute__((signal));
void __vector_16(void){
	busy_flag = MADC_NOTbusy;
	MDIO_u8SetPinValue(MDIO_U8_PORTD , MDIO_U8_PIN_7 , MDIO_U8_HIGH);
	/*Return result*/
	MADC_PF_Notification( MADC_U8_ADC_REG);
}
