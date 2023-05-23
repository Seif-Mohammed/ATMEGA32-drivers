#include "STDTYPE.h"
#include "BIT_MATH.h"
#include "MDIO_Interface.h"

#include "MTMR_Config.h"
#include "MTMR_Interface.h"
#include "MTMR_Private.h"

static void(*MTMR_PF[2])(void) = {STD_TYPE_NULL , STD_TYPE_NULL};

u8 MTMR_TIMER0_INIT(void){
	/*Select timer mode*/
	MTMR_U8_TCCR0_REG |= MTMR_U8_TMR0_PhaseCorrectPWM;
	/*Set OC0 PIN => Noninverting mode */
	SET_BIT(MTMR_U8_TCCR0_REG , 5);
	CLEAR_BIT(MTMR_U8_TCCR0_REG , 4);
	/*set preload value*/
	//MTMR_U8_TCNT0_REG = MTMR_U8_TMRO_PreLoadValue;
	/*Set compare match value*/
	MTMR_U8_OCR0_REG = 127;
	/*Enable Interrupt*/
	//SET_BIT(MTMR_U8_TIMSK_REG , 1);
	/*Enable INTERRUPT compare match*/
	//SET_BIT(MTMR_U8_OCR0_REG , 1);
	/*Set preScaler(8.. for now)*/
	MTMR_U8_TCCR0_REG |= 0b00000010;
}

u8 MTMR_TMR0CompareMatchValue(u8 Copy_u8CompareMatchValue){
	MTMR_U8_OCR0_REG = Copy_u8CompareMatchValue;
}

u8 MTMR_U8TMR0_SetCallBack(u8 CopyInterruptNo , void (*Copy_pf)(void)){
	u8 LocalstateError = STD_TYPES_OK;
	if(Copy_pf != STD_TYPE_NULL){
		MTMR_PF[CopyInterruptNo] =Copy_pf;
	}
	return LocalstateError;
}

void __vector_11(void) __attribute__((signal));
void __vector_11(void){
	static  u16 Local_counter =0;
	Local_counter++;
	if(Local_counter ==3907){
		/*Reset PreLoad value*/
		MTMR_U8_TCNT0_REG = MTMR_U8_TMRO_PreLoadValue;
		/*Action*/
		if(MTMR_PF[MTMR_TMR0_OVF] != STD_TYPE_NULL){
			MTMR_PF[MTMR_TMR0_OVF]();
		}
		/*Clear Counter*/
		Local_counter = 0;
	}
}

void __vector_10(void) __attribute__((signal));
void __vector_10(void){
	static  u16 Local_counter =0;
	Local_counter++;
	if(Local_counter ==10000){
		/*Action*/
		if(MTMR_PF[MTMR_TMR0_CTC] != STD_TYPE_NULL){
			MTMR_PF[MTMR_TMR0_CTC]();
		}
		/*Clear Counter*/
		Local_counter = 0;
	}
}

u8 MTMR_TIMER1_INIT(void){
	u8 LocalStateError =STD_TYPES_OK;
	/*Choose mode .. Fast PWM fow now */
	CLEAR_BIT(MTMR_U8_TCCR1A_REG , 0);
	CLEAR_BIT(MTMR_U8_TCCR1A_REG , 1);
	CLEAR_BIT(MTMR_U8_TCCR1B_REG , 3);
	CLEAR_BIT(MTMR_U8_TCCR1B_REG , 4);
///*SET PIN 0C1A TO NonInverting (clear on compare match)*/
//SET_BIT(MTMR_U8_TCCR1A_REG , 7);
//CLEAR_BIT(MTMR_U8_TCCR1A_REG , 6);
///*Set top value of timer(ICR1 register) to 50HZ == 20ms*/
//MTMR_U16_ICR1_REG = 19999;
///*Set initial value of OCR1A*/
//MTMR_U16_OCR1A_REG =999;
	/*Set preScaler(8.. for now)*/
	MTMR_U8_TCCR1B_REG |= 0b00000010;
	return LocalStateError;
}
u8 MTMR_TMR1CompareMatchValue(u16 Copy_u16CompareMatchValue){
	MTMR_U16_OCR1A_REG = Copy_u16CompareMatchValue;
}

u16 MTMR_TIMER1_GetValue(void){
	return MTMR_U16_TCNT1_REG;
}
