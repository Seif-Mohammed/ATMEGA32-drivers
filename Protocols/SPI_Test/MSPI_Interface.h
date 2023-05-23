/*
 * MSPI_Interface.h
 *
 *  Created on: Nov 11, 2022
 *      Author: seifm
 */

#ifndef MSPI_INTERFACE_H_
#define MSPI_INTERFACE_H_

u8 MSPI_U8_MASTERInit();
u8 MSPI_U8_SlaveInit();
u8 MSPI_U8_TransRecieve(u8 CopyData); //full duplex

#endif /* MSPI_INTERFACE_H_ */
