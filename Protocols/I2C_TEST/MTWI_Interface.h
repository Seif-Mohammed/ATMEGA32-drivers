#ifndef MTWI_INTERFACE_H_
#define MTWI_INTERFACE_H_

void MTWI_Init(u8 Copy_u8CurrentSlaveAddress);
u8 MTWI_SendStartCondtion(void);
u8 MTWI_SendRepeatedStartCodition();
u8 MTWI_SendSlaveAddress_With_Write(u8 Copy_u8SlaveAddress);
u8 MTWI_SendSlaveAddress_With_Read(u8 Copy_u8SlaveAddress);
u8 MTWI_SendDataByte(u8 Copy_DataByte);
u8 MTWI_ReadDataByte(u8 * Copy_RecievedDataByte);
void MTWI_SendStopCodition();


#endif /* MTWI_INTERFACE_H_ */
