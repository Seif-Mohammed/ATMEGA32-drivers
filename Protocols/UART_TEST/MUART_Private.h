#ifndef MUART_Private_H_
#define MUART_Private_H_

#define MUART__U8_UDR_REG		*((volatile u8*)0x2C)
#define MUART__U8_UCSRA_REG		*((volatile u8*)0x2B)
#define MUART__U8_UCSRB_REG		*((volatile u8*)0x2A)
#define MUART__U8_UCSRC_REG		*((volatile u8*)0x40)
#define MUART__U8_UBRRH_REG		*((volatile u8*)0x40)
#define MUART__U8_UBRRL_REG		*((volatile u8*)0x29)

#endif
