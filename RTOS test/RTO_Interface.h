/*
 * RTO_Interface.h
 *
 *  Created on: Dec 9, 2022
 *      Author: seifm
 */

#ifndef RTO_INTERFACE_H_
#define RTO_INTERFACE_H_

u8 RTO_u8CreateTask(u8 Copy_u8Priority , u16 Copy_u16Periodicity , u16 Copy_u16FirstDelay , void(*Copy_pf)(void));
void RTO_voidStartScheduler();


#endif /* RTO_INTERFACE_H_ */
