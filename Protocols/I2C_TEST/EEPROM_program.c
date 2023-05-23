#include "BIT_MATH.h"
#include "STDTYPE.h"
#include "MDIO_Interface.h"
#include "MTWI_Config.h"
#include "MTWI_Interface.h"
#include "MTWI_Private.h"
#include "EEPROM.h"

u8 EEPROM_INIT(){}
u8 HEEPROM_WriteByte(u32 address , u8 data){
	u8 LOcalErrorState = STD_TYPES_NOK;
	u8 Block_address = address / 256;
	u8 byte_address = address % 256;
	LOcalErrorState = MTWI_SendStartCondtion();
	LOcalErrorState = MTWI_SendSlaveAddress_With_Write((0b0101010 | Block_address));
	LOcalErrorState = MTWI_SendDataByte(byte_address);
	LOcalErrorState = MTWI_SendDataByte(data);
	MTWI_SendStopCodition();
}
u8 HEEPRPM_ReadByte(u32 address , u8 * data){
	u8 LOcalErrorState = STD_TYPES_NOK;
	u8 Block_address = address / 256;
	u8 byte_address = address % 256;
	LOcalErrorState = MTWI_SendStartCondtion();
	LOcalErrorState= MTWI_SendSlaveAddress_With_Write((0b0101010 | Block_address));
	LOcalErrorState = MTWI_SendDataByte(byte_address);
	LOcalErrorState = MTWI_SendRepeatedStartCodition();
	LOcalErrorState = MTWI_SendSlaveAddress_With_Read((0b0101010 | Block_address));
	LOcalErrorState = MTWI_SendDataByte(byte_address);
	LOcalErrorState = MTWI_ReadDataByte(data);
	MTWI_SendStopCodition();
	return LOcalErrorState;
}
