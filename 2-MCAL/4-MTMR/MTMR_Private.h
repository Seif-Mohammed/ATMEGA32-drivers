#ifndef MTMR_PRIVATE_H_
#define MTMR_PRIVATE_H_

#define MTMR_U8_TCCR0_REG		*((volatile u8*)0x53)
#define MTMR_U8_TCNT0_REG		*((volatile u8*)0x52)
#define MTMR_U8_OCR0_REG		*((volatile u8*)0x5C)
#define MTMR_U8_TIMSK_REG		*((volatile u8*)0x59)
#define MTMR_U8_TIFR_REG		*((volatile u8*)0x58)
#define MTMR_U8_TCCR1A_REG		*((volatile u8*)0x4F)
#define MTMR_U8_TCCR1B_REG		*((volatile u8*)0x4E)
#define MTMR_U16_TCNT1_REG		*((volatile u16*)0x4C)
#define MTMR_U16_OCR1A_REG		*((volatile u16*)0x4A)
#define MTMR_U16_OCR1B_REG		*((volatile u16*)0x48)
#define MTMR_U16_ICR1_REG		*((volatile u16*)0x46)




#define  MTMR_U8_TMR0_NormalMode	  		0b00000000
#define  MTMR_U8_TMR0_CTCMode				0b00001000
#define  MTMR_U8_TMR0_FastPWM				0b01001000
#define  MTMR_U8_TMR0_PhaseCorrectPWM		0b01000000
#endif /* MTMR_PRIVATE_H_ */
