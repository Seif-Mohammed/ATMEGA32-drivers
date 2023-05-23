#include "BIT_MATH.h"
#include "STDTYPE.h"
#include "MDIO_Interface.h"
#include "MTWI_Config.h"
#include "MTWI_Interface.h"
#include "MTWI_Private.h"


void MTWI_Init(u8 Copy_u8CurrentSlaveAddress){
	MTWI_TWAR_Reg = Copy_u8CurrentSlaveAddress << 1;
	/*Select clc =>200KHz*/
	MTWI_TWBR_Reg = 32;
	/*Enable ACK*/
	SET_BIT(MTWI_TWCR_Reg , 6);
	/*Enable I2C perphral*/
	SET_BIT(MTWI_TWCR_Reg , 2);
}
u8 MTWI_SendStartCondtion(void){
	u8 LocalErrorState = STD_TYPES_OK;
	/*Send Start Condtion*/
	SET_BIT(MTWI_TWCR_Reg , 5);    //STILL WAITING FOR FLAG TO BE CLEARED TO START NEW JOB
	/*Flag Clear*/
	SET_BIT(MTWI_TWCR_Reg , 7);
	/*wait for the flag*/
	while(GET_BIT(MTWI_TWCR_Reg , 7) == 0);
	/*Check Status code to make sure start codition done*/
	if((MTWI_TWSR_Reg & 0XF8) == 0X08){
		LocalErrorState = STD_TYPES_OK;
		/*Clear start codition bit*/
		CLEAR_BIT(MTWI_TWCR_Reg , 5);
	}
	return LocalErrorState;
}
u8 MTWI_SendRepeatedStartCodition(){
	u8 LocalErrorState = STD_TYPES_OK;
	/*Send Start Condtion*/
	SET_BIT(MTWI_TWCR_Reg , 5);    //STILL WAITING FOR FLAG TO BE CLEARED TO START NEW JOB
	/*Flag Clear*/
	SET_BIT(MTWI_TWCR_Reg , 7);
	/*wait for the flag*/
	while(GET_BIT(MTWI_TWCR_Reg , 7) == 0);
	/*Check Status code to make sure start codition done*/
	if((MTWI_TWSR_Reg & 0XF8) == 0X10){
		LocalErrorState = STD_TYPES_OK;
		/*Clear start codition bit*/
		CLEAR_BIT(MTWI_TWCR_Reg , 5);
	}
	return LocalErrorState;
}
u8 MTWI_SendSlaveAddress_With_Write(u8 Copy_u8SlaveAddress){
	u8 LocalErrorState = STD_TYPES_NOK;
	MTWI_TWDR_Reg = Copy_u8SlaveAddress <<1;
	/*Select write operation*/
	CLEAR_BIT(MTWI_TWDR_Reg , 0);
	/*clear flag to start job*/
	SET_BIT(MTWI_TWCR_Reg , 7);
	/*wait for the flag*/
	while(GET_BIT(MTWI_TWCR_Reg , 7) == 0);
	/*Check Status code to make sure start codition done*/
	if((MTWI_TWSR_Reg & 0XF8) == 0X18){
		LocalErrorState = STD_TYPES_OK;
	}
	return LocalErrorState;
}
u8 MTWI_SendSlaveAddress_With_Read(u8 Copy_u8SlaveAddress){
	u8 LocalErrorState = STD_TYPES_OK;
	MTWI_TWDR_Reg = Copy_u8SlaveAddress <<1;
	/*Select Read operation*/
	SET_BIT(MTWI_TWDR_Reg , 0);
	/*clear flag to start job*/
	SET_BIT(MTWI_TWCR_Reg , 7);
	/*wait for the flag*/
	while(GET_BIT(MTWI_TWCR_Reg , 7) == 0);
	/*Check Status code to make sure start codition done*/
	if((MTWI_TWSR_Reg & 0XF8) == 0X40){
		LocalErrorState = STD_TYPES_OK;
	}
	return LocalErrorState;
}
u8 MTWI_SendDataByte(u8 Copy_DataByte){
	u8 LocalErrorState = STD_TYPES_OK;
	MTWI_TWDR_Reg = Copy_DataByte;
	/*clear flag to start job*/
	SET_BIT(MTWI_TWCR_Reg , 7);
	/*wait for the flag*/
	while(GET_BIT(MTWI_TWCR_Reg , 7) == 0);
	/*Check Status code to make sure start codition done*/
	if((MTWI_TWSR_Reg & 0XF8) == 0X28){
		LocalErrorState = STD_TYPES_OK;
		}
	return LocalErrorState;
}
u8 MTWI_ReadDataByte(u8 * Copy_RecievedDataByte){
	u8 LocalErrorState = STD_TYPES_OK;
	if(Copy_RecievedDataByte != STD_TYPE_NULL){
		/*clear flag to start job*/
		SET_BIT(MTWI_TWCR_Reg , 7);
		/*wait for the flag*/
		while(GET_BIT(MTWI_TWCR_Reg , 7) == 0);
		/*Check Status code to make sure start codition done*/
		if((MTWI_TWSR_Reg & 0XF8) == 0X50){
			LocalErrorState = STD_TYPES_OK;
			/*Read Data*/
			*Copy_RecievedDataByte = MTWI_TWDR_Reg;
		}
	}else{
		LocalErrorState = STD_TYPES_NOK;
	}
	return LocalErrorState;
}
void MTWI_SendStopCodition(){
	/*Send Stop Codition*/
	SET_BIT(MTWI_TWCR_Reg , 4);
	/*clear flag to start job*/
	SET_BIT(MTWI_TWCR_Reg , 7);
}
