#ifndef MADC_Private_h
#define MADC_Private_h

#define MADC_NOTbusy 	0
#define MADC_busy 		1

#define  MADC_AREF_pin		0b00000000
#define  MADC_AVCC			0b01000000
#define  MADC_InternalVref	0b11000000


#define MADC_U8_ADMUX_REG		*((volatile u8*)0x27)
#define MADC_U8_ADCSRA_REG		*((volatile u8*)0x26)
#define MADC_U8_SFIOR_REG		*((volatile u8*)0x50)
#define MADC_U8_ADC_REG			*((volatile u16*)0x24)
#define MADC_U8_ADCL_REG		*((volatile u8*)0x24)
#define MADC_U8_ADCH_REG		*((volatile u8*)0x25)

#endif
