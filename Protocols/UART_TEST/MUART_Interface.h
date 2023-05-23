/*
 * MUART_Interface.h
 *
 *  Created on: Nov 5, 2022
 *      Author: seifm
 */

#ifndef MUART_INTERFACE_H_
#define MUART_INTERFACE_H_

typedef struct{
	u8 Data_size;
	u8 parityBitCofiguration;
	u8 Stop_Bit;
	u32 BaudRate;
}MUART_Configuration;

u8 MUART_voidInit(void);
u8 MUART_voidSendByte(u8 Copy_u8TxByte);
u8 MUART_voidRecieveByte(void);

#endif /* MUART_INTERFACE_H_ */
