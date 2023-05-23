#include "STDTYPE.h"
#include "BIT_MATH.h"
#include "MTMR_Interface.h"
#include "RTO_Config.h"
#include "RTO_Interface.h"
#include "RTO_Private.h"
#define MEXTI_U8_SREG_REG		*((volatile u8*)0X5F)

typedef struct{
	u16 Periodicity;
	u16 FirstDelay;
	void(*pf)(void);
}RT0_TCB;

static RT0_TCB RTO_TCBs[RTO_MaxTasksNo];



u8 RTO_u8CreateTask(u8 Copy_u8Priority , u16 Copy_u16Periodicity , u16 Copy_u16FirstDelay , void(*Copy_pf)(void)){
	u8 LocalErrorState = STD_TYPES_NOK;
	if(Copy_u8Priority < RTO_MaxTasksNo){
		LocalErrorState = STD_TYPES_OK;
		RTO_TCBs[Copy_u8Priority].FirstDelay = Copy_u16FirstDelay;
		RTO_TCBs[Copy_u8Priority].Periodicity = Copy_u16Periodicity;
		RTO_TCBs[Copy_u8Priority].pf = Copy_pf;
	}
	return LocalErrorState;
}

void RTO_voidStartScheduler(){
	/*Set callback function*/
	MTMR_U8TMR0_SetCallBack(MTMR_TMR0_OVF , &RTO_void_Scheduler_);
	SET_BIT(MEXTI_U8_SREG_REG,7);
	MTMR_TIMER0_INIT();
}
void RTO_void_Scheduler_(){
	for(u8 counter=0 ; counter<RTO_MaxTasksNo ; counter++){
		if(RTO_TCBs[counter].FirstDelay == 0){
			RTO_TCBs[counter].pf();
			RTO_TCBs[counter].FirstDelay = RTO_TCBs[counter].Periodicity-1;
		}
		else{
			RTO_TCBs[counter].FirstDelay--;
		}
	}
}
