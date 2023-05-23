#ifndef MTMR_INTERFACE_H_
#define MTMR_INTERFACE_H_



#define MTMR_TMR0_OVF		0
#define MTMR_TMR0_CTC		1


u8 MTMR_TMR1CompareMatchValue(u16 Copy_u16CompareMatchValue);
u8 MTMR_U8TMR0_SetCallBack(u8 CopyInterruptNo , void(*Copy_pf)(void));
u8 MTMR_TMR0CompareMatchValue(u8 Copy_u8CompareMatchValue);
u8 MTMR_TIMER0_INIT(void);
u8 MTMR_TIMER1_INIT(void);
u16 MTMR_TIMER1_GetValue(void);

#endif /* MTMR_INTERFACE_H_ */
