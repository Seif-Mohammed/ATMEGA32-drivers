#ifndef MADC_Interface_h
#define MADC_Interface_h

/*Macros for channelNumber*/
#define MADC_U8_Channel0	0
#define MADC_U8_Channel1	1
#define MADC_U8_Channel2	2
#define MADC_U8_Channel3	3
#define MADC_U8_Channel4	4
#define MADC_U8_Channel5	5
#define MADC_U8_Channel6	6
#define MADC_U8_Channel7	7
void MADC_voidINIT(void);
u8 MADC_U8GetDigitalValueSynch(u8 Copy_u8ChannedNumber , u16 * Copy_pu16_DigitalValue);

u8 MADC_U8GetDigitalValueAsynch(u8 Copy_u8ChannedNumber , void(*Copy_pNotification)(u16));


#endif
