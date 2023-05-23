#include "STDTYPE.h"
#include "BIT_MATH.h"
#include "MDIO_Interface.h"

#include "MTMR_Config.h"
#include "MTMR_Interface.h"
#include "MTMR_Private.h"

static void(*MTMR_PF[2])(void) = {STD_TYPE_NULL , STD_TYPE_NULL};

u8 MTMR_TIMER0_INIT(void){
	/*Select timer mode*/
	MTMR_U8_TCCR0_REG |= MTMR_U8_TimerMode;
	/*Set OC0 PIN => Noninverting mode */
//	SET_BIT(MTMR_U8_TCCR0_REG , 5);
//	CLEAR_BIT(MTMR_U8_TCCR0_REG , 4);
	/*1ms isr calculations
	 * no of ovfs = 1000/256=3.90625
	 *  = 0.90625 * 256 = 232 tick needed in last timer ovfs*/
	/*set preload value */
	MTMR_U8_TCNT0_REG = 24;
	/*Enable OVFs*/
	SET_BIT(MTMR_U8_TIMSK_REG , 0);
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
	if(Local_counter ==4){
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
	SET_BIT(MTMR_U8_TCCR1A_REG , 1);
	SET_BIT(MTMR_U8_TCCR1B_REG , 3);
	SET_BIT(MTMR_U8_TCCR1B_REG , 4);
	/*SET PIN 0C1A TO NonInverting (clear on compare match)*/
	SET_BIT(MTMR_U8_TCCR1A_REG , 7);
	CLEAR_BIT(MTMR_U8_TCCR1A_REG , 6);
	/*Set top value of timer(ICR1 register) to 50HZ == 20ms*/
	MTMR_U16_ICR1_REG = 19999;
	/*Set initial value of OCR1A*/
	MTMR_U16_OCR1A_REG =999;
	/*Set preScaler(8.. for now)*/
	MTMR_U8_TCCR1B_REG |= 0b00000010;
	return LocalStateError;
}
u8 MTMR_TMR1CompareMatchValue(u16 Copy_u16CompareMatchValue){
	MTMR_U16_OCR1A_REG = Copy_u16CompareMatchValue;
}

u8 MTMR_U8HW_ICU_INIT(void){
	u8 LocalStateError =STD_TYPES_OK;
	/*Choose mode .. normal mode */
	CLEAR_BIT(MTMR_U8_TCCR1A_REG , 0);
	CLEAR_BIT(MTMR_U8_TCCR1A_REG , 1);
	CLEAR_BIT(MTMR_U8_TCCR1B_REG , 3);
	CLEAR_BIT(MTMR_U8_TCCR1B_REG , 4);
	/*select triggering source to be raising edge*/
	SET_BIT(MTMR_U8_TCCR1B_REG , 6);
	/*At each raising edge enable interrupt*/
	SET_BIT(MTMR_U8_TIMSK_REG , 5);
	/*Set preScaler(8.. TO MAKE TICK TIME = 1 MICROSECOND)*/
	MTMR_U8_TCCR0_REG |= 0b00000010;

}
static volatile u16 Ton , Toff;
u8 MTMR_U16getTon_and_Toff(u16 * CopyTon , u16 * CopyToff){
	 *CopyTon = Ton;
	 *CopyToff = Toff;
}
void __vector_6(void) __attribute__((signal));
void __vector_6(void){
	static u8 flag =1;
	static u16 previuosTimerRead;
	u16 current_timer_read;
	current_timer_read = MTMR_U16_ICR1_REG;
	/*READ TIMER VALUE*/
	if(flag == 1){
		/*change ICU edge detector to be falling edge*/
		CLEAR_BIT(MTMR_U8_TCCR1B_REG , 6);
		/*Calculate Toff period*/
		Toff = (current_timer_read - previuosTimerRead ) ;
		flag = 0 ;
	}else{
		/*Calculate Ton period*/
		Ton = (current_timer_read - previuosTimerRead ) ;
		SET_BIT(MTMR_U8_TCCR1B_REG , 6);
		flag = 1 ;
	}
	previuosTimerRead = current_timer_read;

}
